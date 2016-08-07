#ifndef _CCHARACTER_
#define _CCHARACTER_

#include <string>
#include <mutex>

#include <cstdarg>
#include <string.h>

#include <Protocol/Packet.h>


#include <Protocol/MainProtocol.h>


#include <minwindef.h>
#include <common.h>

class CCharacter
{
	std::mutex m_mxThis;

protected:
	int m_nID;

	WORD m_wStr, 
		 m_wHth, 
		 m_wInt,
		 m_wWis, 
		 m_wDex;

	WORD m_wCurHP, 
		 m_wCurMP;

	int m_nX, 
		m_nY, 
		m_nZ;

	BYTE m_byLevel;

	WORD m_wMaxHP, 
		 m_wMaxMP, 
		 m_wHit, 
		 m_wDodge, 
		 m_wDefense;
	BYTE m_byAbsorb;
	WORD m_wMinAttack, 
		 m_wMaxAttack, 
		 m_wMinMagic, 
		 m_wMaxMagic;
	BYTE m_byFire, 
		 m_byIce, 
		 m_byLightning, 
		 m_byCurse, 
		 m_byPalsy;

	WORD m_wDir;

	__int64 m_n64GState,
	 		m_n64MState,
	 		m_n64GStateEx,
	 		m_n64MStateEx;
public:

	static int g_nID;

	CCharacter();

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	int  GetID() const { return m_nID; }
	WORD GetStr() const { return m_wStr; }
	WORD GetHth() const { return m_wHth; }
	WORD GetInt() const { return m_wInt; }
	WORD GetWis() const { return m_wWis; }
	WORD GetAgi() const { return m_wDex; }
	WORD GetCurHP() const { return m_wCurHP; }
	WORD GetCurMP() const { return m_wCurMP; }
	WORD GetMaxHP() const { return m_wMaxHP; }
	WORD GetMaxMP() const { return m_wMaxMP; }
	int  GetX() const { return m_nX; }
	int  GetY() const { return m_nY; }
	int  GetZ() const { return m_nZ; }
	BYTE GetLevel() const { return m_byLevel; }
	WORD GetHit() const { return m_wHit; }
	WORD GetDodge() const { return m_wDodge; }
	WORD GetDefense() const { return m_wDefense; }
	BYTE GetAborb() const { return m_byAbsorb; }
	WORD GetMinAttack() const { return m_wMinAttack; }
	WORD GetMaxAttack() const { return m_wMaxAttack; }
	WORD GetMinMagic() const { return m_wMinMagic; }
	WORD GetMaxMagic() const { return m_wMaxMagic; }
	BYTE GetFire() const { return m_byFire; }
	BYTE GetIce() const { return m_byIce; }
	BYTE GetLightning() const { return m_byLightning; }
	BYTE GetCurse() const { return m_byCurse; }
	BYTE GetPalsy() const { return m_byPalsy; }
};

#endif