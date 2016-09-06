#ifndef _CMONSTER_
#define _CMONSTER_

#include "CCharacter.h"

#include "../Macro/CMacroDB.h"

class CMonster: public CCharacter
{
	WORD m_wIndex;
	CMonsterInfo *m_pMacro;
	
public:
	CMonster(CMonsterInfo *pMacro, int nX, int nY);
	~CMonster();
	
	static CMonster* CreateMonster(WORD wIndex, int nX, int nY);

	static CMonster* Summon(WORD wIndex, int nX, int nY);

	static std::map<int, CMonster*> g_mMonster;
	static std::mutex g_mxMonster;

	static void Add(CMonster *pMonster);
	static void Remove(CMonster *pMonster);

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

	void Tick();
	void Move(char byX, char byY, BYTE byType);

	void SendPacket(Packet& packet) {};

	enum MOVE_TYPE
	{
		MT_WALK,
		MT_RUN,
	};

	enum MOVE_TYPEEX
	{
		MTEX_MOVEEND = 2,
	};
};

typedef std::map<int, CMonster*> MonsterMap;
typedef std::list<CMonster*> MonsterList;

#endif