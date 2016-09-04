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

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GeneratePetPacket();
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	WORD GetIndex() { return m_pMacro->m_wIndex; }
	BYTE GetRace() { return m_pMacro->m_byRace; }

	void SendPacket(Packet& packet) {};
};

typedef std::map<int, CMonster*> MonsterMap;
typedef std::list<CMonster*> MonsterList;

#endif