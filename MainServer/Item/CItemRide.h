#ifndef _CITEMRIDE_
#define _CITEMRIDE_

#include "CItem.h"

class CItemRide: public CItem
{
	BYTE m_byWearType;

public:
	CItemRide(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	BYTE GetRideType() const { return m_pMacro->m_nBuffValue; }

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);

	bool Use(CPlayer *pPlayer) override;
};

#endif