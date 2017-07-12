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

	WORD m_wStr,
		m_wHth,
		m_wInt,
		m_wWis,
		m_wDex;

	DWORD m_dwHP,
		m_dwMP;

	WORD m_wDefense,
		m_wHit,
		m_wDodge,
		m_wAbsorb;

	WORD m_wResistFire,
		m_wResistIce,
		m_wResistLitning,
		m_wResistCurse,
		m_wResistPalsy;

	WORD m_wMinAttack,
		m_wMaxAttack,
		m_wMinMagic,
		m_wMaxMagic;

	WORD m_wSize;

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
		m_wAttackSpeed(0),
		m_wDefense(0),
		m_wHit(0),
		m_wDodge(0),
		m_wAbsorb(0),
		m_wResistFire(0),
		m_wResistIce(0),
		m_wResistLitning(0),
		m_wResistCurse(0),
		m_wResistPalsy(0),
		m_dwHP(0),
		m_dwMP(0),
		m_wMinAttack(0),
		m_wMaxAttack(0),
		m_wMinMagic(0),
		m_wMaxMagic(0),
		m_wStr(0),
		m_wHth(0),
		m_wInt(0),
		m_wWis(0),
		m_wDex(0),
		m_wSize(0)
	{
	}
};

#endif
