#include "CItemPet.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemPet::CItemPet(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	m_byWearType = WS_PET;
}

void CItemPet::PutOn(CPlayer *pPlayer)
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
	pPlayer->WriteInSight(S2C_ATTACH_PET, "dwdb", pPlayer->GetID(), GetIndex(), GetIID(), GetPetType());
	CDBSocket::Write(S2D_PUTONITEM, "d", GetIID());
}

void CItemPet::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(m_byWearType)) {
		printf(KRED "CItemPet::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemPet::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
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
