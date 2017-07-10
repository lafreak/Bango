#ifndef _CMONSTERINFO_
#define _CMONSTERINFO_

#include "CMacro.h"

struct CMonsterInfo: public CMacro
{
	WORD m_wIndex;
	BYTE m_byRace;
	BYTE m_byLevel;
	BYTE m_byAI;
	WORD m_wRange;
	WORD m_wCloseSight;
	WORD m_wFarSight;
	__int64 m_n64Exp;
	WORD m_wWalkSpeed;
	WORD m_wRunSpeed;
	WORD m_wAttackSpeed;

	CMonsterInfo()
	 :
		m_wIndex(0),
		m_byRace(0),
		m_byLevel(0),
		m_byAI(0),
		m_wRange(0),
		m_wCloseSight(0),
		m_wFarSight(0),
		m_n64Exp(0),
		m_wWalkSpeed(0),
		m_wRunSpeed(0),
		m_wAttackSpeed(0)
	{
	}
};

#endif
