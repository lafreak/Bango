#include "CItem.h"
#include "CItemGeneral.h"
#include "CItemWeapon.h"
#include "CItemDefense.h"
#include "CItemYinyang.h"
#include "CItemPet.h"
#include "CItemOrnament.h"
#include "CItemTransform.h"

#include "../Map/CMap.h"

#include "../GameCharacter/CPlayer.h"

int CItem::g_nMaxIID;
std::mutex CItem::g_mxMaxIID;

ItemMap CItem::g_mItem;
std::mutex CItem::g_mxItem;

CItem::CItem(ITEMINFO_DESC& desc, CItemInfo *pMacro)
{
	m_desc = desc;
	m_pMacro = pMacro;
}

CItem::~CItem()
{
	while (m_Access.IsBusy()) {
		printf("CItem::~CItem: Item is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

int CItem::NewIID()
{
	g_mxMaxIID.lock();
	g_nMaxIID++;
	g_mxMaxIID.unlock();

	return g_nMaxIID;
}

void CItem::Add(CItem *pItem)
{
	g_mxItem.lock();

	if (pItem->g_mItem.find(pItem->GetIID()) == g_mItem.end())
		g_mItem[pItem->GetIID()] = pItem;

	else 
		printf(KRED "CItem::Add: Same Item alrdy in ItemMap.\n" KNRM);

	g_mxItem.unlock();

}

void CItem::Remove(CItem *pItem)
{
	g_mxItem.lock();

	ItemMap::iterator it = g_mItem.find(pItem->GetIID());
	
	if (it != g_mItem.end())
		g_mItem.erase(it);

	g_mxItem.unlock();
}

CItem* CItem::FindItemByIID(int nIID)
{
	CItem *pItem = NULL;

	g_mxItem.lock();

	if (g_mItem.find(nIID) != g_mItem.end()) {
        pItem = g_mItem[nIID];
        pItem->m_Access.Grant();
	}

	g_mxItem.unlock();

	return pItem;
}

void CItem::Tick()
{

	DWORD m_timer = this->GetTimer(); 

	Lock();

	int id = this->GetIID();
	
	if (GetTickCount() - m_timer > 30000 && m_nGState == IGS_DROPPED)
	//if (GetTickCount() - m_timer > 15000 && m_nGState == 1)
	{
		printf("Current state before S2C_Removeitem %d\n", this->GetState());
		CPlayer::WriteAll(S2C_REMOVEITEM, "d", id);
		
		CMap::RemoveItem(this);
		SetGState(IGS_GENERAL);
	}

	Unlock();
}

bool CItem::CanUse(CPlayer *pPlayer)
{
	DWORD dwTimeNow = GetTickCount();

	if (pPlayer->GetLevel() < m_pMacro->m_byReqLevel) {
		printf(KRED "CItem::CanUse: Level is too low.\n" KNRM);
		return false;
	}

	if (m_pMacro->m_byReqClass != 0xFF && m_pMacro->m_byReqClass != pPlayer->GetClass()) {
		printf(KRED "CItem::CanUse: Wrong class.\n" KNRM);
		return false;
	}

	//if (dwTimeNow < m_dwLastUsage + m_pMacro->m_nCooltime) {
	//	printf(KRED "CItem::CanUse: Cooldown hack.\n" KNRM);
	//	return false;
	//}

	return true;
}

bool CItem::CanTrash(CPlayer *pPlayer)
{
	if (IsState(ITEM_PUTON))
		return false;

	return true;
}

CItem* CItem::CreateItem(CItem* dropItem, int amount, int x, int y)
{
	ITEMINFO_DESC m_desc = dropItem->GetDesc();

    m_desc.nIID = CItem::NewIID();
    m_desc.nNum = amount;

    CItem* pItem = CItem::CreateItem(m_desc);
  
    pItem->SetX(x);
    pItem->SetY(y);

    if (pItem)
    CItem::Add(pItem);

    return pItem;
}

Packet CItem::GenerateCreatePacket()
{
	Packet packet;

	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_CREATEITEM;

	char* end = CSocket::WritePacket(packet.data, "wddddd",
	 this->GetIndex(), 
	 this->GetIID(), 
	 this->GetX(), 
	 this->GetY(), 
	 -1);

	packet.wSize = end - ((char*)&packet);

	printf("packet has been created index: [%d] posX: [%d] posY: [%d]", this->GetIndex(), this->GetX(), this->GetY());

	return packet;
}

Packet CItem::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_REMOVEITEM;

	char *end = CSocket::WritePacket(packet.data, "d", this->GetIID());

	packet.wSize = end - ((char*)&packet);

	return packet;
}

CItem* CItem::CreateItem(ITEMINFO_DESC& desc)
{
	CItemInfo* pMacro = (CItemInfo*) CMacroDB::FindMacro(CMacro::MT_ITEM, desc.wIndex);
	if (!pMacro) {
		printf(KRED "Wrong item index: %d\n" KNRM, desc.wIndex);
		return NULL;
	}

	CItem *pItem=NULL;

	switch (pMacro->m_byClass)
	{
		case IC_GENERAL:
			pItem = new CItemGeneral(desc, pMacro);
			break;
		case IC_WEAPON:
			pItem = new CItemWeapon(desc, pMacro);
			break;
		case IC_DEFENSE:
			pItem = new CItemDefense(desc, pMacro);
			break;
		case IC_YINYANG:
			pItem = new CItemYinyang(desc, pMacro);
			break;
		case IC_PET:
			pItem = new CItemPet(desc, pMacro);
			break;
		case IC_ORNAMENT:
			pItem = new CItemOrnament(desc, pMacro);
			break;
		case IC_TRANSFORM:
			pItem = new CItemTransform(desc, pMacro);
			break;
		default:
			printf(KRED "Unknown item class (%d).\n" KNRM, pMacro->m_byClass);
			pItem = new CItemGeneral(desc, pMacro);
			break;
	}

	return pItem;
}