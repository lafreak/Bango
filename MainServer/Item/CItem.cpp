#include "CItem.h"
#include "CItemGeneral.h"
#include "CItemWeapon.h"
#include "CItemDefense.h"
#include "CItemYinyang.h"
#include "CItemPet.h"

#include "../GameCharacter/CPlayer.h"

int CItem::g_nMaxIID;
std::mutex CItem::g_mxMaxIID;

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
		default:
			printf(KRED "Unknown item class (%d).\n" KNRM, pMacro->m_byClass);
			pItem = new CItemGeneral(desc, pMacro);
			break;
	}

	return pItem;
}