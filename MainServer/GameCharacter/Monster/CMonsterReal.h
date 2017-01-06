#ifndef _CMONSTERREAL_
#define _CMONSTERREAL_

#include "../CMonster.h"

class CMonsterReal: public CMonster
{
public:
	CMonsterReal(CMonsterInfo *pMacro, int nX, int nY, MONSTER_DESC &desc): CMonster(pMacro, nX, nY, desc) {}

};

#endif

