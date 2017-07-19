#ifndef _CITEMGENERAL_
#define _CITEMGENERAL_

#include <vector>
#include "CItem.h"

enum TELEPORT
{
	//fucking koreans dont know 6?
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

class CItemGeneral: public CItem
{
public:
	CItemGeneral(ITEMINFO_DESC& desc, CItemInfo* pMacro): CItem(desc, pMacro) {}

	static CoordsMap g_mTeleScrolls;
	void Teleport(CPlayer* pPlayer);
	bool Use(CPlayer *pPlayer);
};

#endif