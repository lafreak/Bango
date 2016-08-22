#include "CItemWeapon.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

void CItemWeapon::PutOn(CPlayer *pPlayer)
{
	if (!CanUse(pPlayer))
		return;

	if (pPlayer->IsWState(WS_WEAPON)) {
		CItem* pItem = pPlayer->FindItemByIID(pPlayer->GetGear(WS_WEAPON));
		if (pItem) {
			pPlayer->PutOffItem(pItem);
			pItem->m_Access.Release();
		}
		return;
	}

	if (IsState(ITEM_PUTON))
		return;

	pPlayer->Lock();
	pPlayer->SetGear(this);
	pPlayer->SetGearIndex(WS_WEAPON, GetIndex());
	pPlayer->Unlock();

	Lock();
	AddState(ITEM_PUTON);
	Unlock();

	pPlayer->WriteInSight(S2C_PUTONITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTONITEM, "d", GetIID());
}

void CItemWeapon::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(WS_WEAPON)) {
		printf(KRED "CItemWeapon::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemWeapon::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
		return;
	}

	pPlayer->Lock();
	pPlayer->SubWState(WS_WEAPON);
	pPlayer->SetGearIndex(WS_WEAPON, 0);
	pPlayer->Unlock();

	Lock();
	SubState(ITEM_PUTON);
	Unlock();

	pPlayer->WriteInSight(S2C_PUTOFFITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTOFFITEM, "d", GetIID());
}