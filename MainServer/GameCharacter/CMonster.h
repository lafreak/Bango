#ifndef _CMONSTER_
#define _CMONSTER_

#include "CCharacter.h"

#include "../Macro/CMacroDB.h"

#define MONSTER_WALK_FREQUENCY 20
#define MONSTER_WALK_TIME 4

class CPlayer;

class CMonster: public CCharacter
{
	WORD m_wIndex;
	CMonsterInfo *m_pMacro;

	CPlayer* m_pTarget;

	BYTE m_byAIState;

	DWORD m_dwWalkTime;

	DWORD m_dwLastWalkStep;
	DWORD m_dwLastChaseStep;

	static std::map<int, CMonster*> g_mMonster;
	static std::mutex g_mxMonster;
	
public:
	CMonster(CMonsterInfo *pMacro, int nX, int nY);
	~CMonster();
	
	static CMonster* CreateMonster(WORD wIndex, int nX, int nY);

	static CMonster* Summon(WORD wIndex, int nX, int nY);

	static void Add(CMonster *pMonster);
	static void Remove(CMonster *pMonster);
	static void TickAll();
	static void AIAll();

	// Remember to call m_Access.Release() after usage
	static CMonster* FindMonster(int nID);
	static CMonster* FindMonsterByIndex(WORD wIndex);

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GeneratePetPacket();
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ = 0);

	WORD GetIndex() { return m_pMacro->m_wIndex; }
	BYTE GetRace() { return m_pMacro->m_byRace; }
	BYTE GetLevel() { return m_pMacro->m_byLevel; }
	WORD GetRange() { return m_pMacro->m_wRange; }
	WORD GetWalkSpeed() { return m_pMacro->m_wWalkSpeed; }
	WORD GetRunSpeed() { return m_pMacro->m_wRunSpeed; }
	WORD GetCloseSight() { return m_pMacro->m_wCloseSight; }

	void SetAIS(BYTE byState) { m_byAIState = byState; }
	void SetTarget(CPlayer *pPlayer) { m_pTarget = pPlayer; }

	void Tick();
	void AI();
	void Move(char byX, char byY, BYTE byType);

	void SendPacket(Packet& packet) {};

	// Remember to call m_Access.Release() after usage
	CPlayer* GetClosestPlayer();

	enum MOVE_TYPE
	{
		MT_WALK,
		MT_RUN,
	};

	enum MOVE_TYPEEX
	{
		MTEX_MOVEEND = 2,
	};

	enum AI_STATE
	{
		AIS_IDLE,
		AIS_WALK,
		AIS_CHASE,
	};
};

typedef std::map<int, CMonster*> MonsterMap;
typedef std::list<CMonster*> MonsterList;

#endif