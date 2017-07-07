#include "CItemWeapon.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemWeapon::CItemWeapon(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	switch (m_pMacro->m_bySubClass)
	{
		case ISC_SWORD:
		case ISC_WAND:
		case ISC_BOW:
		case ISC_DAGGER:
			m_byWearType = WS_WEAPON;
			break;

		case ISC_SWORD2HAND:
			m_byWearType = WS_2HANDWEAPON;
			break;

		default:
			printf(KRED "CItemWeapon::CItemWeapon: Unknown SubClass.\n" KNRM);
			m_byWearType = GEAR_NUM-1;
			break;
	}
}

void CItemWeapon::PutOn(CPlayer *pPlayer)
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

	if (m_byWearType == WS_2HANDWEAPON && pPlayer->IsWState(WS_SHIELD))
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
	pPlayer->OnPutOffGear(this);
	pPlayer->Unlock();

	Lock();
	SubState(ITEM_PUTON);
	Unlock();

	pPlayer->WriteInSight(S2C_PUTOFFITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTOFFITEM, "d", GetIID());
}