#include "CItemYinyang.h"

#include "../GameCharacter/CPlayer.h"

#include "../Socket/CDBSocket.h"

CItemYinyang::CItemYinyang(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro)
{
	switch (m_pMacro->m_bySubClass)
	{
		case ISC_YINYANGMIRROR:
			m_byWearType = WS_MIRROR;
			break;

		case ISC_TAEGEUK:
			m_byWearType = WS_TAEGEUK;
			break;

		case ISC_TRIGRAM1:
			m_byWearType = WS_TRIGRAM1;
			break;

		case ISC_TRIGRAM2:
			m_byWearType = WS_TRIGRAM2;
			break;

		case ISC_TRIGRAM3:
			m_byWearType = WS_TRIGRAM3;
			break;

		case ISC_TRIGRAM4:
			m_byWearType = WS_TRIGRAM4;
			break;

		case ISC_TRIGRAM5:
			m_byWearType = WS_TRIGRAM5;
			break; 

		case ISC_TRIGRAM6:
			m_byWearType = WS_TRIGRAM6;
			break;

		case ISC_TRIGRAM7:
			m_byWearType = WS_TRIGRAM7;
			break;

		case ISC_TRIGRAM8:
			m_byWearType = WS_TRIGRAM8;
			break;

		default:
			printf(KRED "CItemYinyang::CItemYinyang: Unknown SubClass.\n" KNRM);
			m_byWearType = GEAR_NUM-1;
			break;
	}
}

void CItemYinyang::PutOn(CPlayer *pPlayer)
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

	if (pPlayer->GetTrigramLevel() && pPlayer->GetTrigramLevel() != GetLevel()) {
		printf(KRED "CItemYinyang::PutOn: Trigram level incorrect.\n" KNRM);
		return;
	}

	if (!pPlayer->IsAllTrigramState()) 
	{
		printf("Is not all trigram.\n");
		if (GetSubClass() == ISC_YINYANGMIRROR || GetSubClass() == ISC_TAEGEUK) {
			printf(KRED "Can't put on - not all trigrams are on.\n" KNRM);
			return;
		}
	}

	pPlayer->Lock();
	pPlayer->OnPutOnGear(this);
	pPlayer->Unlock();

	printf("Trigram level: %d\n", pPlayer->GetTrigramLevel());

	Lock();
	AddState(ITEM_PUTON);
	Unlock();

	pPlayer->Write(S2C_PUTONITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTONITEM, "d", GetIID());
}

void CItemYinyang::PutOff(CPlayer *pPlayer)
{
	if (!pPlayer->IsWState(m_byWearType)) {
		printf(KRED "CItemYinyang::PutOff: Trying to put off item while having no item put on.\n" KNRM);
		return;
	}

	if (!IsState(ITEM_PUTON)) {
		printf(KRED "CItemYinyang::PutOff: Trying to put off item with no state ITEM_PUTON.\n" KNRM);
		return;
	}

	if (GetSubClass() >= ISC_TRIGRAM1 && GetSubClass() <= ISC_TRIGRAM8) 
	{
		if (pPlayer->IsWState(WS_MIRROR) || pPlayer->IsWState(WS_TAEGEUK)) {
			printf(KRED "Cannot put off trigram, because mirror or taegeuk is on.\n" KNRM);
			return;
		}
	}

	pPlayer->Lock();
	pPlayer->OnPutOffGear(this);
	pPlayer->Unlock();

	printf("%s Trigram level: %d\n", __PRETTY_FUNCTION__, pPlayer->GetTrigramLevel());

	Lock();
	SubState(ITEM_PUTON);
	Unlock();

	pPlayer->Write(S2C_PUTOFFITEM, "ddw", pPlayer->GetID(), GetIID(), GetIndex());
	CDBSocket::Write(S2D_PUTOFFITEM, "d", GetIID());
}