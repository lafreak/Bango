#ifndef _CCHARACTER_
#define _CCHARACTER_

#include <string>
#include <mutex>
#include <math.h>
#include <list>
#include <map>
#include <unistd.h>

#include <access.h>

#include <cstdarg>
#include <string.h>

#include <Protocol/Packet.h>
#include <Socket/CSocket.h>

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
	BYTE m_byClass;

	//WORD m_wMaxHP, 
		 //m_wMaxMP, 
	//WORD m_wHit, 
		 //m_wDodge, 
	WORD m_wDefense;
	BYTE m_byAbsorb;
	//WORD m_wMinAttack, 
	//	 m_wMaxAttack, 
	//WORD m_wMinMagic, 
	//WORD m_wMaxMagic;
	//BYTE m_byFire, 
	//	 m_byIce, 
	//	 m_byLightning, 
	//	 m_byCurse, 
	//	 m_byPalsy;

	WORD m_wDir;

	__int64 m_n64GState,
	 		m_n64MState,
	 		m_n64GStateEx,
	 		m_n64MStateEx;

	 BYTE m_byKind;
public:

	static int g_nID;
	static std::mutex g_mxID;
	static int NewID();

	CCharacter();

	Access m_Access;

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	int  GetID() const { return m_nID; }
	BYTE GetKind() const { return m_byKind; }
	BYTE GetClass() const { return m_byClass; }
	WORD GetStr() const { return m_wStr; }
	WORD GetHth() const { return m_wHth; }
	WORD GetInt() const { return m_wInt; }
	WORD GetWis() const { return m_wWis; }
	WORD GetAgi() const { return m_wDex; }
	WORD GetCurHP() const { return m_wCurHP; }
	WORD GetCurMP() const { return m_wCurMP; }
	WORD GetMaxHP() const;// { return m_wMaxHP; }
	WORD GetMaxMP() const;// { return m_wMaxMP; }
	int  GetX() const { return m_nX; }
	int  GetY() const { return m_nY; }
	int  GetZ() const { return m_nZ; }
	WORD GetDir() const { return m_wDir; }
	BYTE GetLevel() const { return m_byLevel; }
	WORD GetHit() const;// { return m_wHit; }
	WORD GetDodge() const;// { return m_wDodge; }
	WORD GetDefense() const { return m_wDefense; }
	BYTE GetAbsorb() const { return m_byAbsorb; }
	WORD GetMinAttack() const;// { return m_wMinAttack; }
	WORD GetMaxAttack() const;// { return m_wMaxAttack; }
	WORD GetMinMagic() const;// { return m_wMinMagic; }
	WORD GetMaxMagic() const;// { return m_wMaxMagic; }
	WORD GetResist(BYTE byResist) const;

	__int64 GetGState() const { return m_n64GState; }
	__int64 GetMState() const { return m_n64MState; }
	__int64 GetGStateEx() const { return m_n64GStateEx; }
	__int64 GetMStateEx() const { return m_n64MStateEx; }

	void AddGState(__int64 n64GState);
	void AddMState(__int64 n64MState);
	void AddGStateEx(__int64 n64GStateEx);
	void AddMStateEx(__int64 n64MStateEx);
	void SubGState(__int64 n64GState);
	void SubMState(__int64 n64MState);
	void SubGStateEx(__int64 n64GStateEx);
	void SubMStateEx(__int64 n64MStateEx);
	bool IsGState(__int64 n64GState);
	bool IsMState(__int64 n64MState);
	bool IsGStateEx(__int64 n64GStateEx);
	bool IsMStateEx(__int64 n64MStateEx);

	virtual Packet GenerateCreatePacket(bool bHero=false) = 0;
	virtual Packet GeneratePetPacket() = 0;
	virtual Packet GenerateDeletePacket() = 0;
	virtual Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ = 0) = 0;

	virtual void SendPacket(Packet& packet) = 0;

	virtual void Tick() = 0;

	bool WriteInSight(BYTE byType, ...);

	void SendPacketInSight(Packet& packet);

	void SetDirection(int nX, int nY);

	BYTE GetMoveAction(CCharacter *pCharacter, char byX, char byY);
	int  GetDistance(CCharacter *pCharacter);
};

typedef std::map<int, CCharacter*> CharacterMap;
typedef std::list<CCharacter*> CharacterList;


#endif