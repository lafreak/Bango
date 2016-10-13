#include "CMonster.h"

#include "Monster/CMonsterReal.h"

#include "../Map/CMap.h"

#include "CPlayer.h"

MonsterMap CMonster::g_mMonster;
std::mutex CMonster::g_mxMonster;

CMonster::CMonster(CMonsterInfo *pMacro, int nX, int nY)
{
	m_pMacro = pMacro;
	m_nX = nX;
	m_nY = nY;

	m_pTarget = NULL;

	m_byAIState = AIS_IDLE;

	m_dwWalkTime = GetTickCount() + (rand() % (MONSTER_WALK_FREQUENCY * 1000));

	m_dwLastWalkStep = 0;
	m_dwLastChaseStep = 0;
}

CMonster::~CMonster()
{
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
		default:
			printf(KRED "Unknown monster race (%d).\n" KNRM, pMacro->m_byRace);
			pMonster = new CMonsterReal(pMacro, nX, nY);
			break;
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
		100, //curhp
		100, //maxhp
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

Packet CMonster::GeneratePetPacket()
{
	Packet packet;
	packet.wSize=0;

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

	for (auto& a: g_mMonster)
	{
		a.second->m_Access.Grant();
		a.second->Tick();
		a.second->m_Access.Release();
	}

	g_mxMonster.unlock();
}

void CMonster::AIAll()
{
	g_mxMonster.lock();

	for (auto& a: g_mMonster)
	{
		a.second->m_Access.Grant();
		a.second->AI();
		a.second->m_Access.Release();
	}

	g_mxMonster.unlock();
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

CPlayer* CMonster::GetClosestPlayer()
{
	return CMap::GetClosestPlayer(this, GetCloseSight());
}

void CMonster::Tick()
{
	DWORD dwNow = GetTickCount();

	if (m_byAIState == AIS_IDLE && dwNow >= m_dwWalkTime) 
	{
		Lock();

		auto pTarget = GetClosestPlayer();

		if (pTarget) 
		{
			printf("Found taget.\n");
			m_pTarget = pTarget;
			m_byAIState = AIS_CHASE;
			pTarget->m_Access.Release();
			printf("Time for chase!.\n");
		}
		else
		{
			printf("Walk time.\n");
			m_dwWalkTime = dwNow + MONSTER_WALK_FREQUENCY * 1000;
			m_byAIState = AIS_WALK;
		}

		Unlock();
	}
}

void CMonster::AI()
{
	DWORD dwNow = GetTickCount();

	switch (m_byAIState)
	{
		case AIS_WALK:
		{
			if (dwNow < m_dwLastWalkStep)
				break;

			WORD wAngle = rand() % 360;
			char dx = 32 * cos(wAngle * M_PI / 180.0);
			char dy = 32 * sin(wAngle * M_PI / 180.0);

			Lock();

			if ((rand() % MONSTER_WALK_TIME) == 0)
			{
				Move(dx, dy, MT_WALK | MTEX_MOVEEND);
				m_byAIState = AIS_IDLE;
			}
			else
			{
				Move(dx, dy, MT_WALK);
			}

			m_dwLastWalkStep = dwNow + GetWalkSpeed();

			Unlock();

			break;
		}

		case AIS_CHASE:
		{
			if (dwNow < m_dwLastChaseStep)
				break;

			printf("Step.\n");

			int nDistance = GetDistance(m_pTarget) - GetRange();

			if (nDistance <= 1)
				break; // Attack

			int nStep = nDistance > 64 ? 64 : nDistance;
			BYTE byType = nDistance > 64 ? 0 : 1;

			float fAngle = atan2(m_pTarget->GetY() - GetY(), m_pTarget->GetX() - GetX());
			char dx = nStep * cos(fAngle);
			char dy = nStep * sin(fAngle);

			Lock();

			if (byType)
			{
				Move(dx, dy, MT_RUN | MTEX_MOVEEND);
			}
			else
			{
				Move(dx, dy, MT_RUN);
			}

			m_dwLastChaseStep = dwNow + GetRunSpeed();

			Unlock();

			break;
		}
	}
}

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