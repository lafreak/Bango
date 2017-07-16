#ifndef _CMONSTERMAGUNI_
#define _CMONSTERMAGUNI_

#include "../CMonster.h"

class CMonsterMaguni: public CMonster
{
	DWORD m_dwDeadTime;

public:
	CMonsterMaguni(CMonsterInfo *pMacro, int nX, int nY) : CMonster(pMacro, nX, nY) { }

	void Die() override;
	void Tick() override;
};

#endif
