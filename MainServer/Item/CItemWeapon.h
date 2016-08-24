#ifndef _CITEMWEAPON_
#define _CITEMWEAPON_

#include "CItem.h"

class CItemWeapon: public CItem
{
	BYTE m_byWearType;

public:
	CItemWeapon(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif