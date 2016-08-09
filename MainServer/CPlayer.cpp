#include <Socket/CSocket.h>

#include "Socket/CDBSocket.h"

#include "CPlayer.h"

#include "CServer.h"

WORD CPlayer::g_wDebugItems[4][8] = {
	1632, 1479, 1480, 1481, 1633, 799, 0, 0,
	1640, 1489, 1490, 1491, 1641, 801, 0, 0,
	1636, 1484, 1485, 1486, 1637, 800, 0, 0,
	1764, 1766, 1767, 1768, 1769, 1441, 0, 0
};

CPlayer::CPlayer(int nCID, D2S_LOADPLAYER_DESC desc): CCharacter()
{
	m_nCID = nCID;

	m_nAID = desc.nAID;
	m_nPID = desc.nPID;
	m_szName = std::string(desc.szName);
	m_byClass = desc.byClass;
	m_byJob = desc.byJob;
	m_byLevel = desc.byLevel;
	m_wStr = desc.wStats[STAT_STR];
	m_wHth = desc.wStats[STAT_HTH];
	m_wInt = desc.wStats[STAT_INT];
	m_wWis = desc.wStats[STAT_WIS];
	m_wDex = desc.wStats[STAT_AGI];
	m_wCurHP = desc.wCurHP;
	m_wCurMP = desc.wCurMP;
	m_n64Exp = desc.n64Exp;
	m_wPUPoint = desc.wPUPoint;
	m_wSUPoint = desc.wSUPoint;
	m_wContribute = desc.wContribute;
	m_nAnger = desc.nAnger;
	m_nX = desc.nX;
	m_nY = desc.nY;
	m_nZ = desc.nZ;
}

CPlayer::~CPlayer()
{
	CMap::Remove(CMap::GetMapInfo(m_nX, m_nY), m_nID);

	WriteInSight(S2C_REMOVEPLAYER, "d", m_nID);

	while (m_Access.IsBusy()) {
		printf("CPlayer::~CPlayer: Player is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

bool CPlayer::Write(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	send(m_nCID, (char*)&packet, packet.wSize, 0);

	return true;
}

bool CPlayer::WriteInSight(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	//send(m_nCID, (char*)&packet, packet.wSize, 0);
	CMap::SendPacket(this, packet);

	return true;
}

void CPlayer::SendPacket(Packet& packet)
{
	send(m_nCID, (char*)&packet, packet.wSize, 0);
}

Packet CPlayer::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	BYTE byUnknownV=0;
	BYTE byUn1=0;
	int nUn2=0;
	int nUn3=0;
	BYTE byUn4=0;

	BYTE byClass=m_byClass;

	if (bHero)
		byClass |= GAME_HERO;

	packet.byType = S2C_CREATEPLAYER;
	char *end = CSocket::WritePacket(packet.data, "dsbdddwIwwwwwwwwbbIssdbdddIIbddb", 
		m_nID, 
		m_szName.c_str(), 
		byClass, 
		m_nX, 
		m_nY, 
		m_nZ, 
		m_wDir, 
		m_n64GState,
		g_wDebugItems[m_byClass][0], 
		g_wDebugItems[m_byClass][1],
		g_wDebugItems[m_byClass][2], 
		g_wDebugItems[m_byClass][3], 
		g_wDebugItems[m_byClass][4], 
		g_wDebugItems[m_byClass][5], 
		g_wDebugItems[m_byClass][6], 
		g_wDebugItems[m_byClass][7], 
		m_byFace, 
		m_byHair, 
		m_n64MState, 
		m_szGuildClass.c_str(), 
		m_szGuildName.c_str(), 
		m_nGID, 
		m_byFlag, 
		m_nFlagItem, 
		m_nHonorGrade, 
		m_nHonorOption, 
		m_n64GStateEx, 
		m_n64MStateEx, 
		byUnknownV,
		byUn1,
		nUn2,
		nUn3,
		byUn4);
	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CPlayer::GenerateDeletePacket()
{
	Packet packet;

	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_REMOVEPLAYER;
	char *end = CSocket::WritePacket(packet.data, "d", m_nID);
	packet.wSize = end - ((char*)&packet);

	return packet;
}

void CPlayer::Process(Packet packet)
{
	switch (packet.byType)
	{
		case C2S_START:
		{
			BYTE byUnknown=0;
			int nHeight=0;

			CSocket::ReadPacket(packet.data, "bd", &byUnknown, &nHeight);
			printf("byUnknown: %d, nHeight: %d\n", byUnknown, nHeight);

			if (nHeight != m_nZ)
				printf(KRED "Client map height[%d] differs from player Z[%d].\n" KNRM, nHeight, m_nZ);

			GameStart();

			break;
		}

		case C2S_RESTART:
		{
			BYTE byMessage=0;
			CSocket::ReadPacket(packet.data, "b", &byMessage);

			if (byMessage)
				Write(S2C_ANS_RESTART, "b", 1);
			else
				GameRestart();

			break;
		}

		case C2S_GAMEEXIT:
		{
			Write(S2C_ANS_GAMEEXIT, "b", 1);
			break;
		}

		case C2S_MOVE_ON:
		{
			char byX=0;
			char byY=0;
			char byZ=0;
			CSocket::ReadPacket(packet.data, "bbb", &byX, &byY, &byZ);

			Lock();
			OnMove(byX, byY, byZ, 0);
			Unlock();
			break;
		}

		case C2S_MOVE_END:
		{
			char byX=0;
			char byY=0;
			char byZ=0;
			CSocket::ReadPacket(packet.data, "bbb", &byX, &byY, &byZ);

			Lock();
			OnMove(byX, byY, byZ, 1);
			Unlock();
			break;
		}

		case C2S_CHATTING:
		{
			char* szMsg=NULL;

			CSocket::ReadPacket(packet.data, "s", &szMsg);

			int nRideID = atoi(szMsg);
			BYTE byMode=0;

			WriteInSight(S2C_RIDING, "bdd", byMode, m_nID, nRideID);
			printf("S2C_RIDING sent.\n");

			break;
		}
	}
}

void CPlayer::OnLoadPlayer()
{
	Lock();

	m_byKind = CK_PLAYER;

	m_byGrade = 1;
	m_szGuildName = "gname";
	m_byGRole = 1;
	m_wMaxHP = 1000;
	m_wMaxMP = 800;
	m_wHit = 120; 
	m_wDodge = 105;
	m_wDefense = 90;
	m_byAbsorb = 5;
	m_wMinAttack = 650;
	m_wMaxAttack = 710; 
	m_wMinMagic = 425;
	m_wMaxMagic = 412;
	m_byFire = 1;
	m_byIce = 2; 
	m_byLightning = 3;
	m_byCurse = 4;
	m_byPalsy = 5;

	m_szGuildClass = "gclass";
	m_nGID = 0;
	m_byFlag = 0;
	m_nFlagItem = 0;
	m_nHonorGrade = 0;
	m_nHonorOption = 0;

	m_wDir = 0;
	m_n64GState = 0;
	m_n64MState = 0;
	m_n64GStateEx = 0;
	m_n64MStateEx = 0;

	Write(S2C_PROPERTY, "bsbwwwwwwwwwwwwwbIwwwwwwbbbbbd", 
			m_byGrade, 
			m_szGuildName.c_str(), 
			m_byGRole, 
			m_wContribute, 
			m_wStr, 
			m_wHth, 
			m_wInt, 
			m_wWis, 
			m_wDex,
			m_wCurHP, 
			m_wMaxHP, 
			m_wCurMP, 
			m_wMaxMP, 
			m_wHit, 
			m_wDodge, 
			m_wDefense, 
			m_byAbsorb,
			m_n64Exp, 
			m_wMinAttack, 
			m_wMaxAttack, 
			m_wMinMagic, 
			m_wMaxMagic, 
			m_wPUPoint, 
			m_wSUPoint, 
			m_byFire, 
			m_byIce,
			m_byLightning, 
			m_byCurse, 
			m_byPalsy, 
			m_nAnger);

	printf("S2C_PROPERTY sent.\n");

	WORD wTime=1200;

	CMap::Add(CMap::GetMapInfo(m_nX, m_nY), this);

	Write(S2C_ANS_LOAD, "wdd", wTime, m_nX, m_nY);

	printf("S2C_ANS_LOAD sent.\n");

	Unlock();
}

void CPlayer::GameStart()
{
	BYTE byUnknownV=0;

	BYTE byUn1=0; // num ?
	/*
	int nUn2=0;
	BYTE byUn3=0;
	int nUn4=0;
	int nUn5=0;
	BYTE byUn6=0;
	*/
	int nUn2=0;
	int nUn3=0;
	BYTE byUn4=0;

	Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbddb", 
		m_nID, 
		m_szName.c_str(), 
		m_byClass | GAME_HERO, 
		m_nX, 
		m_nY, 
		m_nZ, 
		m_wDir, 
		m_n64GState,
		
		g_wDebugItems[m_byClass][0], 
		g_wDebugItems[m_byClass][1],
		g_wDebugItems[m_byClass][2], 
		g_wDebugItems[m_byClass][3], 
		g_wDebugItems[m_byClass][4], 
		g_wDebugItems[m_byClass][5], 
		g_wDebugItems[m_byClass][6], 
		g_wDebugItems[m_byClass][7], 
		
		m_byFace, 
		m_byHair, 
		m_n64MState, 
		m_szGuildClass.c_str(), 
		m_szGuildName.c_str(), 
		m_nGID, 
		m_byFlag, 
		m_nFlagItem, 
		m_nHonorGrade, 
		m_nHonorOption, 
		m_n64GStateEx, 
		m_n64MStateEx, 
		byUnknownV,
		byUn1, 
		nUn2,
		nUn3,
		byUn4);
	

	ObjectList list;
	CMap::GetObjectListAround(this, MAX_PLAYER_SIGHT, list);

	for (ObjectList::iterator it = list.begin(); it != list.end(); it++) {
		if ((*it)->GetKind() != CK_PLAYER || (*it)->GetID() == m_nID) {
			(*it)->m_Access.Release();
			continue;
		}

		auto pPlayer = (CPlayer*)(*it);

		//printf("Sending info about %s to %s.\n", pPlayer->GetName().c_str(), m_szName.c_str());

		//Packet p = pPlayer->GenerateCreatePacket();
		//SendPacket(p);

		//for (int i = 0; i < 2; i++)
		//Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbddb", 
		Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbddb", 
			pPlayer->GetID(), 
			pPlayer->GetName().c_str(), 
			pPlayer->GetClass(), 
			pPlayer->GetX(), 
			pPlayer->GetY(), 
			pPlayer->GetZ(), 
			pPlayer->GetDir(), 
			pPlayer->GetGState(),
			
			g_wDebugItems[pPlayer->GetClass()][0], 
			g_wDebugItems[pPlayer->GetClass()][1],
			g_wDebugItems[pPlayer->GetClass()][2], 
			g_wDebugItems[pPlayer->GetClass()][3], 
			g_wDebugItems[pPlayer->GetClass()][4], 
			g_wDebugItems[pPlayer->GetClass()][5], 
			g_wDebugItems[pPlayer->GetClass()][6], 
			g_wDebugItems[pPlayer->GetClass()][7], 
			
			pPlayer->GetFace(), 
			pPlayer->GetHair(), 
			pPlayer->GetMState(), 
			pPlayer->GetGuildClass().c_str(), 
			pPlayer->GetGuildName().c_str(), 
			pPlayer->GetGID(), 
			pPlayer->GetFlag(), 
			pPlayer->GetFlagItem(), 
			pPlayer->GetHonorGrade(), 
			pPlayer->GetHonorOption(), 
			pPlayer->GetGStateEx(), 
			pPlayer->GetMStateEx(), 
			byUnknownV,
			byUn1, 
			nUn2,
			nUn3,
			byUn4);	
		

		pPlayer->m_Access.Release();
	}

	WriteInSight(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbddb", 
		m_nID, 
		m_szName.c_str(), 
		m_byClass, 
		m_nX, 
		m_nY, 
		m_nZ, 
		m_wDir, 
		m_n64GState,
		
		g_wDebugItems[m_byClass][0], 
		g_wDebugItems[m_byClass][1],
		g_wDebugItems[m_byClass][2], 
		g_wDebugItems[m_byClass][3], 
		g_wDebugItems[m_byClass][4], 
		g_wDebugItems[m_byClass][5], 
		g_wDebugItems[m_byClass][6], 
		g_wDebugItems[m_byClass][7], 
		
		m_byFace, 
		m_byHair, 
		m_n64MState, 
		m_szGuildClass.c_str(), 
		m_szGuildName.c_str(), 
		m_nGID, 
		m_byFlag, 
		m_nFlagItem, 
		m_nHonorGrade, 
		m_nHonorOption, 
		m_n64GStateEx, 
		m_n64MStateEx, 
		byUnknownV,
		byUn1, 
		nUn2,
		nUn3,
		byUn4);
}

void CPlayer::GameRestart()
{
	auto pClient = CServer::FindClient(m_nCID);
	if (!pClient) {
		printf(KRED "CPlayer::GameRestart: Player cannot find its client.\n" KNRM);
		return;
	}

	m_Access.Release();

	delete this;

	pClient->Lock();
	pClient->RemovePlayer();
	pClient->Unlock();

	CDBSocket::Write(S2D_SELECT_CHARACTER, "d", pClient->GetCID());
	
	pClient->m_Access.Release();
}

void CPlayer::OnMove(char byX, char byY, char byZ, char byType)
{
	MapInfo mapInfoCur = CMap::GetMapInfo(m_nX, m_nY);
	MapInfo mapInfoDest = CMap::GetMapInfo(m_nX + byX, m_nY + byY);

	if (!mapInfoCur.equalTile(mapInfoDest)) 
	{
		printf("Player tile changed.\n[%d %d]->[%d %d]\n",
			mapInfoCur.wTileX, mapInfoCur.wTileY,
			mapInfoDest.wTileX, mapInfoDest.wTileY);

		CMap::Remove(mapInfoCur, m_nID);
		CMap::Add(mapInfoDest, this);
	}

	m_nX += byX;
	m_nY += byY;
	m_nZ += byZ;

	char* end=NULL;

	Packet createPacket = GenerateCreatePacket();
	Packet deletePacket = GenerateDeletePacket();
	Packet movePacket;

	// Move
	memset(&movePacket, 0, sizeof(Packet));
	movePacket.byType = byType ? S2C_MOVEPLAYER_END : S2C_MOVEPLAYER_ON;
	end = CSocket::WritePacket(movePacket.data, "dbbb", m_nID, byX, byY, byZ);
	movePacket.wSize = end - ((char*)&movePacket);


	for (int i = mapInfoDest.wTileX-1; i <= mapInfoDest.wTileX+1; i++) {
		for (int j = mapInfoDest.wTileY-1; j <= mapInfoDest.wTileY+1; j++) {
			auto pTile = CMap::GetTile(i, j);
			if (pTile)
				pTile->SendMoveAction(this, byX, byY, createPacket, deletePacket, movePacket);
		}
	}
}