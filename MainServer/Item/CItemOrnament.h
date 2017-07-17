#ifndef _CITEMORNAMENT_
#define _CITEMORNAMENT_

#include "CItem.h"

class CItemOrnament: public CItem
{
public:
	CItemOrnament(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif
