#ifndef _CITEMPET_
#define _CITEMPET_

#include "CItem.h"

class CItemPet: public CItem
{
	BYTE m_byWearType;

public:
	CItemPet(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	BYTE GetPetType() { return (GetIndex() >= 2004 && GetIndex() <= 2007) ? 1 : 0; }

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif