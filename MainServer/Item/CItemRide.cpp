#include "CItemRide.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemRide::CItemRide(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	m_byWearType = WS_RIDE;
}

void CItemRide::PutOn(CPlayer *pPlayer)
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

	pPlayer->Write(S2C_PUTONITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	//pPlayer->WriteInSight(S2C_RIDING, "bdd", 0, pPlayer->GetID(), GetRideType());
	CDBSocket::Write(S2D_PUTONITEM, "d", GetIID());
}

void CItemRide::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(WS_WEAPON)) {
		printf(KRED "CItemRide::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemRide::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
		return;
	}

	pPlayer->Lock();
	pPlayer->OnPutOffGear(this);
	pPlayer->Unlock();

	Lock();
	SubState(ITEM_PUTON);
	Unlock();

	pPlayer->Write(S2C_PUTOFFITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTOFFITEM, "d", GetIID());
}