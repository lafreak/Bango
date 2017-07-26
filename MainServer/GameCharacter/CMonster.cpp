#include "CMonster.h"

#include "Monster/CMonsterReal.h"
#include "Monster/CMonsterMaguni.h"

#include "../Map/CMap.h"

#include "CPlayer.h"

MonsterMap CMonster::g_mMonster;
std::mutex CMonster::g_mxMonster;

CMonster::CMonster(CMonsterInfo *pMacro, int nX, int nY)
{
	m_pMacro = pMacro;
	m_nX = nX;
	m_nY = nY;

	m_nCurHP = GetMaxHP();

	m_pTarget = NULL;

	//m_byAIState = AIS_IDLE;

	//m_dwWalkTime = GetTickCount() + (rand() % (MONSTER_WALK_FREQUENCY * 1000));

	//m_dwLastWalkStep = 0;
	//m_dwLastChaseStep = 0;
	//m_dwLastAttackTime = 0;

	SetTimer(std::bind(&CMonster::ScanSight, this), MONSTER_WALK_FREQUENCY * 1000);

	m_byKind = CK_MONSTER;
}

CMonster::~CMonster()
{
	CMap::Remove(this);
	//CMonster::Remove(this); // Not required, since TickAll does it

	while (m_Access.IsBusy()) {
		printf("CMonster::~CMonster: Monster is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

CMonster* CMonster::CreateMonster(WORD wIndex, int nX, int nY)
{
	CMonsterInfo* pMacro = (CMonsterInfo*) CMacroDB::FindMacro(CMacro::MT_MONSTER, wIndex);
	if (!pMacro) {
		printf(KRED "Wrong monster index: %d\n" KNRM, wIndex);
		return NULL;
	}

	CMonster* pMonster=NULL;

	switch (pMacro->m_byRace)
	{
		case 0:
			switch (pMacro->m_byAI)
			{
				case 1:
				case 2:
					// Beheadable
					pMonster = new CMonsterMaguni(pMacro, nX, nY);
					break;
			}
			break;
		case 1:
			switch (pMacro->m_byAI)
			{
				case 1:
				case 2:
					// Non beheadable
					pMonster = new CMonsterReal(pMacro, nX, nY);
					break;
			}
			break;
	}

	if (!pMonster)
	{
		printf(KRED "Unknown monster Race[%d] or AI[%d].\n" KNRM, pMacro->m_byRace, pMacro->m_byAI);
		pMonster = new CMonsterReal(pMacro, nX, nY);
	}

	return pMonster;
}

CMonster* CMonster::Summon(WORD wIndex, int nX, int nY)
{
	CMonster *pMonster = CreateMonster(wIndex, nX, nY);
	if (!pMonster)
		return NULL;

	CMap::Add(pMonster);
	CMonster::Add(pMonster);

	Packet createPacket = pMonster->GenerateCreatePacket(true);
	pMonster->SendPacketInSight(createPacket);

	printf("MaxHP: %d Attack %d~%d Lv: %d\n", 
		pMonster->GetMaxHP(), 
		pMonster->GetMinAttack(), 
		pMonster->GetMaxAttack(), 
		pMonster->GetLevel());

	return pMonster;
}

Packet CMonster::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_CREATEMONSTER;

	char *end = CSocket::WritePacket(packet.data, "wdddwddIIsbdsIIb", 
		GetIndex(),
		GetID(),
		GetX(),
		GetY(),
		GetDir(),
		GetCurHP(),//100, //curhp
		GetMaxHP(),//100, //maxhp
		GetGState(),
		GetMState(),
		"\0",
		GetRace() | (bHero ? 0x80 : 0),
		0, // gid
		"\0",
		GetGStateEx(),
		GetMStateEx(),
		GetLevel() //level
		); 

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CMonster::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_REMOVEMONSTER;

	char *end = CSocket::WritePacket(packet.data, "d", m_nID);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CMonster::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = (byType & 0x10) ? S2C_MOVEMONSTER_END : S2C_MOVEMONSTER_ON;

	char *end = CSocket::WritePacket(packet.data, "dbbb", m_nID, byX, byY, byType & 1);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

WORD CMonster::GetHit() const
{
	return GetAgi() / 8 + 15 * GetStr() / 54 + m_pMacro->m_wHit;
}

WORD CMonster::GetDodge() const
{
	return GetAgi() / 3 + m_pMacro->m_wDodge;
}

DWORD CMonster::GetMaxHP() const
{
	return ((GetLevel() >= 96 ? 195 :
		(GetLevel() >= 91 ? 141.8147 :
		(GetLevel() >= 86 ? 111.426 :
			(GetLevel() >= 81 ? 91.758 :
			(GetLevel() >= 76 ? 78 :
				(GetLevel() >= 72 ? 67.8162 :
					52)))))) * GetLevel() / 3) + 115 + 2 * GetHth() * GetHth() / 14/*?*/ + m_pMacro->m_dwHP;
}

WORD CMonster::GetMaxMP() const
{
	return ((GetLevel() >= 96 ? 20 :
		(GetLevel() >= 91 ? 18 :
		(GetLevel() >= 86 ? 16 :
			(GetLevel() >= 81 ? 14 :
			(GetLevel() >= 76 ? 12 :
				(GetLevel() >= 72 ? 10 :
					8)))))) * GetLevel()) + 140 + GetWis() + 2 * GetWis() * GetWis() / 14/*?*/ + m_pMacro->m_dwMP;
}

WORD CMonster::GetMinAttack() const
{
	return 1 + ((11 * GetStr() - 80) / 30) + ((GetAgi() - 5) / 11) + (7 * GetLevel() / 10) + m_pMacro->m_wMinAttack;
}

WORD CMonster::GetMaxAttack() const
{
	return ((8 * GetStr() - 25) / 15) + (18 * GetAgi() / 77) + GetLevel() + m_pMacro->m_wMaxAttack;
}

WORD CMonster::GetMinMagic() const
{
	return (7 * GetInt() - 20) / 12 + GetWis() / 7 + m_pMacro->m_wMinMagic;
}

WORD CMonster::GetMaxMagic() const
{
	return 7 * GetInt() / 12 + 14 * GetWis() / 45 + m_pMacro->m_wMaxMagic;
}

WORD CMonster::GetResist(BYTE byResist) const
{
	switch (byResist)
	{
	case RT_FIRE:
		return GetInt() / 9 + m_pMacro->m_wResistFire;
	case RT_ICE:
		return GetInt() / 9 + m_pMacro->m_wResistIce;
	case RT_LITNING:
		return GetInt() / 9 + m_pMacro->m_wResistLitning;
	case RT_PALSY:
		return GetHth() / 9 + m_pMacro->m_wResistPalsy;
	case RT_CURSE:
		return GetWis() / 9 + m_pMacro->m_wResistCurse;
	}
}

void CMonster::Add(CMonster *pMonster)
{
	g_mxMonster.lock();

	if (g_mMonster.find(pMonster->GetID()) == g_mMonster.end())
		g_mMonster[pMonster->GetID()] = pMonster;
	else
		printf(KRED "CMonster::Add: Same monster ingame.\n" KNRM);

	g_mxMonster.unlock();
}

void CMonster::Remove(CMonster *pMonster)
{
	g_mxMonster.lock();

	MonsterMap::iterator it = g_mMonster.find(pMonster->GetID());
	if (it != g_mMonster.end())
		g_mMonster.erase(it);

	g_mxMonster.unlock();
}

void CMonster::TickAll()
{
	g_mxMonster.lock();

	for (auto& m : g_mMonster)
	{
		m.second->m_Access.Grant();
		m.second->Tick();
		m.second->m_Access.Release();
	}

	g_mxMonster.unlock();
}

void CMonster::AIAll(DWORD dwNow)
{
	g_mxMonster.lock();

	for (auto it = g_mMonster.cbegin(); it != g_mMonster.cend(); )
	{
		CMonster *pMonster = (*it).second;

		if (pMonster->IsGState(CGS_KO))
		{
			delete pMonster;
			g_mMonster.erase(it++);
		}
		else
		{
			pMonster->m_Access.Grant();
			pMonster->AI(dwNow);
			pMonster->m_Access.Release();
			++it;
		}
	}

	g_mxMonster.unlock();

	/*
	g_mxMonster.lock();

	for (auto& a: g_mMonster)
	{
		a.second->m_Access.Grant();
		a.second->AIEx();
		a.second->m_Access.Release();
	}

	g_mxMonster.unlock();
	*/
}

void CMonster::Tick()
{
}

CMonster* CMonster::FindMonster(int nID)
{
	CMonster *pMonster=NULL;

	g_mxMonster.lock();

	if (g_mMonster.find(nID) != g_mMonster.end()) {
		pMonster = g_mMonster[nID];
		pMonster->m_Access.Grant();
	}

	g_mxMonster.unlock();

	return pMonster;
}

CMonster* CMonster::FindMonsterByIndex(WORD wIndex)
{
	CMonster *pMonster=NULL;

	g_mxMonster.lock();

	for (auto& a: g_mMonster) {
		if (a.second->GetIndex() == wIndex) {
			pMonster = a.second;
			pMonster->m_Access.Grant();
			break;
		}
	}

	g_mxMonster.unlock();

	return pMonster;
}

void CMonster::DestroyAll()
{
	g_mxMonster.lock();

	for (auto& a : g_mMonster)
		delete a.second;

	g_mMonster.clear();

	g_mxMonster.unlock();
}

CPlayer* CMonster::GetClosestNormalPlayer()
{
	return CMap::GetClosestNormalPlayer(this, GetCloseSight());
}

void CMonster::SetTarget(CPlayer * pPlayer)
{
	if (m_pTarget)
		m_pTarget->m_Access.Release();

	m_pTarget = pPlayer;

	if (pPlayer)
		SetTimer(std::bind(&CMonster::OnChase, this), 0);//?
	else
		SetTimer(std::bind(&CMonster::OnWalk, this), 0);//>
}

/*
void CMonster::AI()
{
	DWORD dwNow = GetTickCount();

	switch (m_byAIState)
	{
		case AIS_WALK:
		{
			if (dwNow < m_dwLastWalkStep)
				break;

			Lock();

			m_dwLastWalkStep = dwNow + GetWalkSpeed();

			Walk();

			Unlock();

			break;
		}

		case AIS_CHASE:
		{
			if (dwNow < m_dwLastChaseStep)
				break;

			Lock();
			m_pTarget->Lock();

			m_dwLastChaseStep = dwNow + GetRunSpeed();

			int nDistance = GetDistance(m_pTarget) - GetRange();

			if (nDistance > GetFarSight())
			{
				m_pTarget->Unlock();
				SetTarget(NULL);
				Unlock();
				break;
			}
			else if (nDistance > 1)
			{
				Chase();
				if (nDistance <= 32)
				{
					m_dwLastAttackTime = m_dwLastChaseStep;
					SetAIS(AIS_FORCEATTACK);
				}
			}
			else
			{
				m_dwLastAttackTime = m_dwLastChaseStep;
				SetAIS(AIS_FORCEATTACK);
			}

			m_pTarget->Unlock();
			Unlock();

			break;
		}

		case AIS_FORCEATTACK:
		{
			if (dwNow < m_dwLastAttackTime)
				break;

			Lock();

			auto pTarget = GetTarget();

			pTarget->Lock();

			m_dwLastAttackTime = dwNow + GetAttackSpeed();

			Attack(pTarget);

			if (GetTarget())
			{
				int nDistance = GetDistance(pTarget) - GetRange();

				if (nDistance > 1)
				{
					m_dwLastChaseStep = m_dwLastAttackTime;
					SetAIS(AIS_CHASE);
				}
				else
				{
					SetAIS(AIS_ATTACK);
				}
			}

			pTarget->Unlock();
			Unlock();

			break;
		}

		case AIS_ATTACK:
		{
			if (dwNow < m_dwLastAttackTime)
				break;

			Lock();

			auto pTarget = GetTarget();

			pTarget->Lock();

			m_dwLastAttackTime = dwNow + GetAttackSpeed();

			int nDistance = GetDistance(m_pTarget) - GetRange();

			if (nDistance > 1)
			{
				m_dwLastChaseStep = GetRunSpeed();
				SetAIS(AIS_CHASE);
				pTarget->Unlock();
				Unlock();
				break;
			}

			Attack(pTarget);

			pTarget->Unlock();
			Unlock();

			break;
		}
	}
}
*/

void CMonster::Move(char byX, char byY, BYTE byType)
{
	MapInfo mapInfoCur = CMap::GetMapInfo(m_nX, m_nY);
	MapInfo mapInfoDest = CMap::GetMapInfo(m_nX + byX, m_nY + byY);

	if (!mapInfoCur.equalTile(mapInfoDest)) 
	{
		CMap::Remove(mapInfoCur, this);
		CMap::Add(mapInfoDest, this);
	}

	m_nX += byX;
	m_nY += byY;

	SetDirection(byX, byY);

	Packet createPacket = 	GenerateCreatePacket();
	Packet petPacket =		GeneratePetPacket();
	Packet deletePacket = 	GenerateDeletePacket();
	Packet movePacket =   	GenerateMovePacket(byType, byX, byY);

	for (int i = mapInfoDest.wTileX-1; i <= mapInfoDest.wTileX+1; i++) {
		for (int j = mapInfoDest.wTileY-1; j <= mapInfoDest.wTileY+1; j++) {
			auto pTile = CMap::GetTile(i, j);
			if (pTile)
				pTile->SendMoveAction(this, byX, byY, createPacket, petPacket, deletePacket, movePacket);
		}
	}
}

void CMonster::Attack(CPlayer *pTarget)
{
	if (!CanAttack(pTarget))
	{
		SetTarget(NULL);
		return;
	}

	SetDirection(pTarget);

	if (pTarget->CheckBlock(this))
	{
		// TODO: Bugfix: Block message does not appear, avoid instead.
		SetTimer(std::bind(&CMonster::OnAttack, this), GetAttackSpeed());
		WriteInSight(S2C_ATTACK, "ddddb", GetID(), pTarget->GetID(), 0, 0, 4);
		return;
	}

	DWORD dwDamage = GetAttack();
	DWORD dwExplosiveBlow = 0;
	BYTE byType = 0;

	if (CheckHit(pTarget))
	{
		pTarget->Damage(this, dwDamage, byType);
	}
	else
	{
		byType = ATF_BLOCK; //? To make Avoid/Evade appear
		dwDamage = 0;
	}

	if (pTarget->IsNormal())
		SetTimer(std::bind(&CMonster::OnAttack, this), GetAttackSpeed());
	else
		SetTimer(std::bind(&CMonster::OnWalk, this), GetAttackSpeed());

	WriteInSight(S2C_ATTACK, "ddddb", GetID(), pTarget->GetID(), dwDamage, dwExplosiveBlow, byType);
}

bool CMonster::Chase()
{
	int nDistance = GetDistance(m_pTarget) - GetRange();

	int nStep = nDistance > MAX_MONSTER_RUN_STEP ? 64 : nDistance;
	BYTE byType = nDistance > MAX_MONSTER_RUN_STEP ? 0 : 1;

	float fAngle = atan2(m_pTarget->GetY() - GetY(), m_pTarget->GetX() - GetX());
	char dx = nStep * cos(fAngle);
	char dy = nStep * sin(fAngle);

	//
	if (CMap::CheckZone(GetX() + dx, GetY() + dy, ZT_SAFEZONE))
		return false;

	if (byType)
	{
		Move(dx, dy, MT_RUN | MTEX_MOVEEND);
	}
	else
	{
		Move(dx, dy, MT_RUN);
	}

	return true;
}

void CMonster::Damage(CCharacter * pAttacker, DWORD & dwDamage, BYTE & byType)
{
	byType = ATF_HIT;

	if (GetTarget() == NULL) 
	{
		pAttacker->m_Access.Grant();
		SetTarget((CPlayer *)pAttacker);
	}

	dwDamage = GetFinalDamage(pAttacker, dwDamage);
	dwDamage = pAttacker->GetFatalDamage(dwDamage, byType);

	if (dwDamage > GetCurHP())
		dwDamage = GetCurHP();

	if (dwDamage <= 0)
	{
		byType = 0;
		return;
	}

	m_nCurHP -= dwDamage;

	if (GetCurHP() > 0)
	{
		//?
	}
	else
	{
		Die();
	}
}

void CMonster::ScanSight()
{
	auto pTarget = GetClosestNormalPlayer();

	if (pTarget)
	{
		SetTarget(pTarget);
	}
	else
	{
		OnWalk();
	}
}

void CMonster::OnWalk()
{
	WORD wAngle = rand() % 360;
	char dx = MAX_MONSTER_WALK_STEP * cos(wAngle * M_PI / 180.0);
	char dy = MAX_MONSTER_WALK_STEP * sin(wAngle * M_PI / 180.0);

	if (CMap::CheckZone(GetX() + dx, GetY() + dy, ZT_SAFEZONE))
	{
		SetTimer(std::bind(&CMonster::OnWalk, this), GetWalkSpeed());
		return;
	}

	if ((rand() % MONSTER_WALK_TIME) == 0)
	{
		Move(dx, dy, MT_WALK | MTEX_MOVEEND);
		SetTimer(std::bind(&CMonster::ScanSight, this), MONSTER_WALK_FREQUENCY * 1000);
	}
	else
	{
		Move(dx, dy, MT_WALK);
		SetTimer(std::bind(&CMonster::OnWalk, this), GetWalkSpeed());
	}
}

void CMonster::OnChase()
{
	m_pTarget->Lock();

	int nDistance = GetDistance(m_pTarget) - GetRange();

	if (nDistance > GetFarSight())
	{
		m_pTarget->Unlock();
		SetTarget(NULL);
		return;
	}
	else if (nDistance > 1)
	{
		if (!Chase())
		{
			m_pTarget->Unlock();
			SetTarget(NULL);
			return;
		}
		else if (nDistance <= 32)
		{
			SetTimer(std::bind(&CMonster::OnForceAttack, this), GetRunSpeed());
		}
		else
		{
			SetTimer(std::bind(&CMonster::OnChase, this), GetRunSpeed());
		}
	}
	else
	{
		SetTimer(std::bind(&CMonster::OnForceAttack, this), GetRunSpeed());
	}

	m_pTarget->Unlock();
}

void CMonster::OnForceAttack()
{
	auto pTarget = GetTarget();

	pTarget->Lock();

	Attack(pTarget);

	if (GetTarget())
	{
		int nDistance = GetDistance(pTarget) - GetRange();

		if (nDistance > 1)
			SetTimer(std::bind(&CMonster::OnChase, this), GetAttackSpeed());
	}

	pTarget->Unlock();
}

void CMonster::OnAttack()
{
	auto pTarget = GetTarget();

	pTarget->Lock();

	int nDistance = GetDistance(m_pTarget) - GetRange();

	if (nDistance > 1)
	{
		SetTimer(std::bind(&CMonster::OnChase, this), GetRunSpeed());
		pTarget->Unlock();
		return;
	}

	Attack(pTarget);

	pTarget->Unlock();
}

void CMonster::OnRemove()
{
	AddGState(CGS_KO);
	WriteInSight(S2C_ACTION, "db", GetID(), AT_DIE);
	// TODO: Check if this packet deallocates monster memory in client. (If monster count gets decreased)
}
