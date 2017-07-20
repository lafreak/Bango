#ifndef _CITEMTELEPORT_
#define _CITEMTELEPORT_

#include <vector>
#include "../CItemGeneral.h"

enum TELEPORT
{
	NARO,
	CARGO,
	GEUM,
	PUB,
	TEMP,
	PRIEST,
	CHEONJI = 7,
	HONDEL
};

typedef std::map<int, std::vector<int>>CoordsMap;

class CItemTeleport: public CItemGeneral
{
public:
	CItemTeleport(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItemGeneral(desc, pMacro) {}

	static CoordsMap g_mTeleportCoords;

	bool Use(CPlayer *pPlayer) override;
};

#endif
