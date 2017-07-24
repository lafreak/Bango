#ifndef _CMONSTER_
#define _CMONSTER_

#include "CCharacter.h"
#include <ITimer.h>

#include "../Macro/CMacroDB.h"

#define MONSTER_WALK_FREQUENCY 5//20
#define MONSTER_WALK_TIME 4

class CPlayer;

class CMonster: public CCharacter, public ITimer
{
	WORD m_wIndex;
	CMonsterInfo *m_pMacro;

	CPlayer* m_pTarget;

	//BYTE m_byAIState;

	//DWORD m_dwWalkTime;

	//DWORD m_dwLastWalkStep;
	//DWORD m_dwLastChaseStep;
	//DWORD m_dwLastAttackTime;

	static std::map<int, CMonster*> g_mMonster;
	static std::mutex g_mxMonster;

public:
	CMonster(CMonsterInfo *pMacro, int nX, int nY);
	~CMonster();
	
	static CMonster* CreateMonster(WORD wIndex, int nX, int nY);

	static CMonster* Summon(WORD wIndex, int nX, int nY);

	// Remember to call m_Access.Release() after usage
	static CMonster* FindMonster(int nID);
	static CMonster* FindMonsterByIndex(WORD wIndex);

	static void DestroyAll();

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ = 0);

	WORD GetStr() const override { return m_pMacro->m_wStr + m_wStrAdd; }
	WORD GetHth() const override { return m_pMacro->m_wHth + m_wHthAdd; }
	WORD GetInt() const override { return m_pMacro->m_wInt + m_wIntAdd; }
	WORD GetWis() const override { return m_pMacro->m_wWis + m_wWisAdd; }
	WORD GetAgi() const override { return m_pMacro->m_wDex + m_wDexAdd; }

	WORD GetHit() const override; //unsure
	WORD GetDodge() const override; //unsure
	WORD GetDefense(BYTE byType) const override { return m_pMacro->m_wDefense[byType]; }
	BYTE GetAbsorb() const override { return m_pMacro->m_wAbsorb; }
	DWORD GetMaxHP() const override; //unsure
	WORD GetMaxMP() const override; //unsure
	WORD GetMinAttack() const override; //unsure
	WORD GetMaxAttack() const override; //unsure
	WORD GetMinMagic() const override; //unsure
	WORD GetMaxMagic() const override; //unsure
	WORD GetResist(BYTE byResist) const override; //unsure

	WORD GetIndex() const { return m_pMacro->m_wIndex; }
	BYTE GetRace() const { return m_pMacro->m_byRace; }
	BYTE GetLevel() const override { return m_pMacro->m_byLevel; }
	WORD GetRange() const { return m_pMacro->m_wRange; }
	WORD GetWalkSpeed() const { return m_pMacro->m_wWalkSpeed; }
	WORD GetRunSpeed() const { return m_pMacro->m_wRunSpeed; }
	WORD GetAttackSpeed() const { return m_pMacro->m_wAttackSpeed; }
	WORD GetCloseSight() const { return m_pMacro->m_wCloseSight; }
	WORD GetFarSight() const { return m_pMacro->m_wFarSight; }
	WORD GetSize() const override { return m_pMacro->m_wSize; }

	//BYTE GetAIS() const { return m_byAIState; }
	//void SetAIS(BYTE byState) { m_byAIState = byState; }
	// Sets new target, starts chasing him and Releases access of last target if was any.
	void SetTarget(CPlayer *pPlayer);
	CPlayer* GetTarget() const { return m_pTarget; }

	static void Add(CMonster *pMonster);
	static void Remove(CMonster *pMonster);
	static void TickAll();
	static void AIAll(DWORD dwNow);

	virtual void Tick();
	virtual void AI(DWORD dwNow) { Lock(); ExecuteTimer(dwNow); Unlock(); }
	void Move(char byX, char byY, BYTE byType);
	void Attack(CPlayer *pTarget);
	void Chase();
	void Walk();
	void Damage(CCharacter *pAttacker, DWORD& dwDamage, BYTE& byType) override;
	
	// Timer
	void ScanSight();
	void OnWalk();
	void OnChase();
	void OnForceAttack();
	void OnAttack();
	void OnRemove();

	// Gets closest normal CPlayer and Grants his access. (Inix CMonster::ScanSight)
	CPlayer* GetClosestNormalPlayer();

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
		AIS_FORCEATTACK,
		AIS_ATTACK,
		AIS_DEAD,
		AIS_KNEE,
	};
};

typedef std::map<int, CMonster*> MonsterMap;
typedef std::list<CMonster*> MonsterList;

#endif
