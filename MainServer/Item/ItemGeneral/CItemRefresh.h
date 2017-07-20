#ifndef _CITEMREFRESH_
#define _CITEMREFRESH_

#include <vector>
#include "../CItemGeneral.h"


class CItemRefresh: public CItemGeneral
{
public:
	CItemRefresh(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItemGeneral(desc, pMacro) {}

	bool Use(CPlayer *pPlayer) override;
};

#endif
