#include "CItemDefense.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemDefense::CItemDefense(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	switch (m_pMacro->m_bySubClass)
	{
		case ISC_SHIELD:
			m_byWearType = WS_SHIELD;
			break;

		case ISC_HELMET:
			m_byWearType = WS_HELMET;
			break;

		case ISC_UPPERARMOR:
			m_byWearType = WS_UPPERARMOR;
			break;

		case ISC_LOWERARMOR:
			m_byWearType = WS_LOWERARMOR;
			break;

		case ISC_GAUNTLET:
			m_byWearType = WS_GAUNTLET;
			break;

		case ISC_BOOTS:
			m_byWearType = WS_BOOTS;
			break;

		default:
			printf(KRED "CItemDefense::CItemDefense: Unknown SubClass.\n" KNRM);
			m_byWearType = WS_SHIELD;
			break;
	}
}

void CItemDefense::PutOn(CPlayer *pPlayer)
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

	if (m_byWearType == WS_SHIELD && pPlayer->IsWState(WS_2HANDWEAPON))
		return;

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

void CItemDefense::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(m_byWearType)) {
		printf(KRED "CItemDefense::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemDefense::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
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
