#ifndef _CITEMINFO_
#define _CITEMINFO_

#include "CMacro.h"

struct CItemInfo: public CMacro
{
	WORD m_wIndex;
	BYTE m_byClass;
	BYTE m_bySubClass;
	BYTE m_byLevel;
	bool m_bWear;
	BYTE m_byReqClass;
	BYTE m_byReqLevel;
	int m_nRange;
	int m_nBuy;
	int m_nSell;
	BYTE m_byEndurance;
	bool m_bPlural;
	bool m_bUse;
	int m_nCooltime;
	BYTE m_byEffect;
	int m_nRefresh[2];
	int m_nBuffId;
	int m_nBuffTime;
	int m_nBuffValue;
	WORD m_wAttackSpeed;
	WORD m_wRange;

	WORD m_wDefense,
		m_wHit,
		m_wDodge,
		m_wAbsorb;

	WORD m_wResistFire,
		m_wResistIce,
		m_wResistLitning,
		m_wResistCurse,
		m_wResistPalsy;

	DWORD m_dwHP,
		m_dwMP;

	WORD m_wMinAttack,
		m_wMaxAttack,
		m_wMinMagic,
		m_wMaxMagic;

	WORD m_wStr,
		m_wHth,
		m_wInt,
		m_wWis,
		m_wDex;

	enum REFRESH
	{
		R_HP,
		R_MP
	};

	CItemInfo()
	 :
		m_wIndex(0),
		m_byClass(0),
		m_bySubClass(0),
	 	m_byLevel(0),
	 	m_bWear(0),
		m_byReqClass(0),
		m_byReqLevel(0),
		m_nRange(0),
		m_nBuy(0),
		m_nSell(0),
		m_byEndurance(0),
		m_bPlural(false),
		m_bUse(false),
		m_nCooltime(0),
		m_byEffect(0),
		m_nBuffId(0),
		m_nBuffTime(0),
		m_nBuffValue(0),
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
		m_wAttackSpeed(0),
		m_wRange(0)
	{
		m_nRefresh[0] = m_nRefresh[1] = 0;
	}
};

#endif
