#include "CItemOrnament.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemOrnament::CItemOrnament(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	switch (m_pMacro->m_bySubClass)
	{
		case ISC_RING:
			m_byWearType = WS_RING;
			break;

		case ISC_NECKLACE:
			m_byWearType = WS_NECKLACE;
			break;

		case ISC_TRINKET:
			m_byWearType = WS_TRINKET;
			break;

		case ISC_RESISTNECKLACE2:
			m_byWearType = WS_RESISTNECKLACE2;
			break;

		default:
			printf(KRED "CItemOrnament::CItemOrnament: Unknown SubClass.\n" KNRM);
			m_byWearType = GEAR_NUM-1;
			break;
	}
}

void CItemOrnament::PutOn(CPlayer *pPlayer)
{
	if (!CanUse(pPlayer))
		return;

	if (pPlayer->IsWState(m_byWearType)) {
		CItem* pItem = pPlayer->FindItemByIID(pPlayer->GetGear(m_byWearType));
		if (pItem) {
			pPlayer->PutOffItem(pItem);
			pItem->m_Access.Release();
		}
		return;
	}

	if (IsState(ITEM_PUTON))
		return;

	pPlayer->Lock();
	pPlayer->OnPutOnGear(this);
	pPlayer->Unlock();

	Lock();
	AddState(ITEM_PUTON);
	Unlock();

	pPlayer->WriteInSight(S2C_PUTONITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTONITEM, "d", GetIID());
}

void CItemOrnament::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(m_byWearType)) {
		printf(KRED "CItemOrnament::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemOrnament::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
		return;
	}

	pPlayer->Lock();
	pPlayer->OnPutOffGear(this);
	pPlayer->Unlock();

	Lock();
	SubState(ITEM_PUTON);
	Unlock();

	pPlayer->WriteInSight(S2C_PUTOFFITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTOFFITEM, "d", GetIID());
}