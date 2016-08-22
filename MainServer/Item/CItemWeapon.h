#ifndef _CITEMWEAPON_
#define _CITEMWEAPON_

#include "CItem.h"

class CItemWeapon: public CItem
{
public:
	CItemWeapon(ITEMINFO_DESC& desc): CItem(desc) {}

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif