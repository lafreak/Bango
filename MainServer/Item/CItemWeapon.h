#ifndef _CITEMWEAPON_
#define _CITEMWEAPON_

#include "CItem.h"

class CItemWeapon: public CItem
{
public:
	CItemWeapon(ITEMINFO_DESC& desc, CItemInfo* pMacro);

	WORD GetAttackSpeed() const { return m_pMacro->m_wAttackSpeed; }
	WORD GetRange() const { return m_pMacro->m_wRange; }

	void PutOn(CPlayer *pPlayer);
	void PutOff(CPlayer *pPlayer);
};

#endif
