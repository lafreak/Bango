#ifndef _CITEMDEFENSE_
#define _CITEMDEFENSE_

#include "CItem.h"

class CItemDefense: public CItem
{
	BYTE m_byWearType;

public:
	CItemDefense(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif