#ifndef _CITEMGENERAL_
#define _CITEMGENERAL_

#include "CItem.h"

class CItemGeneral: public CItem
{
public:
	CItemGeneral(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro) {}

	bool Use(CPlayer *pPlayer);
};

#endif