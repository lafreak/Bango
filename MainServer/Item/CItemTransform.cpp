#include "CItemTransform.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemTransform::CItemTransform(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	// Grade
	m_desc.byMaxEnd = 1;

	// Egg Exp
	m_desc.nNum = 0;

	switch (m_pMacro->m_bySubClass)
	{
		case ISC_COCOON:
			m_byWearType = WS_TRANSFORM;
			break;

		default:
			printf(KRED "CItemTransform::CItemTransform: Unknown SubClass.\n" KNRM);
			m_byWearType = WS_TRANSFORM;
			break;
	}
}

void CItemTransform::PutOn(CPlayer *pPlayer)
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

void CItemTransform::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(WS_WEAPON)) {
		printf(KRED "CItemTransform::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemTransform::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
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
