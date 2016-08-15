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

CPlayer::CPlayer(int nCID, D2S_LOADPLAYER_DESC& desc): CCharacter()
{
	m_nCID = nCID;

	m_nAID = desc.nAID;
	m_nPID = desc.nPID;
	m_szName = std::string(desc.szName);
	m_byClass = desc.byClass;
	m_byJob = desc.byJob;
	m_byLevel = desc.byLevel;
	m_wStr = desc.wStats[P_STR];
	m_wHth = desc.wStats[P_HTH];
	m_wInt = desc.wStats[P_INT];
	m_wWis = desc.wStats[P_WIS];
	m_wDex = desc.wStats[P_DEX];
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

WORD CPlayer::GetReqPU(BYTE *byStats)
{
	WORD wReqPU=0;

	if (m_byClass == PC_KNIGHT)
		wReqPU += FIND_NEED_PU_EX(m_wStr, byStats[P_STR]);
	else
		wReqPU += FIND_NEED_PU(m_wStr, byStats[P_STR]);

	if (m_byClass == PC_MAGE)
		wReqPU += FIND_NEED_PU_EX(m_wInt, byStats[P_INT]);
	else
		wReqPU += FIND_NEED_PU(m_wInt, byStats[P_INT]);

	if (m_byClass == PC_ARCHER || m_byClass == PC_THIEF)
		wReqPU += FIND_NEED_PU_EX(m_wDex, byStats[P_DEX]);
	else
		wReqPU += FIND_NEED_PU(m_wDex, byStats[P_DEX]);

	wReqPU += FIND_NEED_PU(m_wHth, byStats[P_HTH]);
	wReqPU += FIND_NEED_PU(m_wWis, byStats[P_WIS]);

	return wReqPU;
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

void CPlayer::SendPacketInSight(Packet& packet)
{
	CMap::SendPacket(this, packet);
}

Packet CPlayer::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	BYTE byUnknownV=0;
	int nUn2=0;
	int nUn3=0;
	BYTE byUn4=0; // level?

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

Packet CPlayer::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType == 0 ? S2C_MOVEPLAYER_ON : S2C_MOVEPLAYER_END;

	char *end = CSocket::WritePacket(packet.data, "dbbb", m_nID, byX, byY, byZ);

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
		case C2S_MOVE_END:
		{
			char byX=0;
			char byY=0;
			char byZ=0;
			CSocket::ReadPacket(packet.data, "bbb", &byX, &byY, &byZ);

			Lock();
			if (CanMove())
				OnMove(byX, byY, byZ, packet.byType == C2S_MOVE_ON ? 0 : 1);
			Unlock();
			break;
		}

		case C2S_CHATTING:
		{
			char* szMsg=NULL;
			CSocket::ReadPacket(packet.data, "s", &szMsg);

			ProcessMsg(szMsg);
			
			break;
		}

		case C2S_REST:
		{
			BYTE byType=0;
			CSocket::ReadPacket(packet.data, "b", &byType);

			Rest(byType);

			break;
		}

		case C2S_UPDATEPROPERTY:
		{
			BYTE byStats[5]={0,};
			CSocket::ReadPacket(packet.data, "bbbbb", &byStats[P_STR], &byStats[P_HTH], &byStats[P_INT], &byStats[P_WIS], &byStats[P_DEX]);

			WORD wTotalReqPU = GetReqPU(byStats);

			printf("wTotalReqPU: %d PUPoint: %d\n", wTotalReqPU, m_wPUPoint);

			if (wTotalReqPU > m_wPUPoint || wTotalReqPU <= 0)
				break;

			Lock();

			UpdateProperty(P_STR, byStats[P_STR]);
			UpdateProperty(P_HTH, byStats[P_HTH]);
			UpdateProperty(P_INT, byStats[P_INT]);
			UpdateProperty(P_WIS, byStats[P_WIS]);
			UpdateProperty(P_DEX, byStats[P_DEX]);

			m_wPUPoint -= wTotalReqPU;

			Unlock();

			CPlayer::Write(S2C_UPDATEPROPERTY, "bw", P_PUPOINT, m_wPUPoint);
			CDBSocket::Write(S2D_UPDATEPROPERTY, "dwwwwww", m_nPID, m_wStr, m_wHth, m_wInt, m_wWis, m_wDex, m_wPUPoint);

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
	m_wDefense = 90;
	m_byAbsorb = 5;

	m_szGuildClass = "gclass";
	m_nGID = 0;
	m_byFlag = 0;
	m_nFlagItem = 0;
	m_nHonorGrade = 0;
	m_nHonorOption = 0;

	m_wDir = 0;

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
			GetMaxHP(),
			m_wCurMP, 
			GetMaxMP(),
			GetHit(),
			GetDodge(),
			m_wDefense, 
			m_byAbsorb,
			m_n64Exp, 
			GetMinAttack(),
			GetMaxAttack(),
			GetMinMagic(),
			GetMaxMagic(),
			m_wPUPoint, 
			m_wSUPoint, 
			GetResist(RT_FIRE),
			GetResist(RT_ICE),
			GetResist(RT_LITNING),
			GetResist(RT_CURSE), 
			GetResist(RT_PALSY),
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
	Packet createPacket 	= GenerateCreatePacket();
	Packet createHeroPacket = GenerateCreatePacket(true);

	SendPacket(createHeroPacket);

	ObjectList list;
	CMap::GetObjectListAround(this, MAX_PLAYER_SIGHT, list);

	for (ObjectList::iterator it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->GetKind() != CK_PLAYER)
		{
			(*it)->m_Access.Release();
			continue;
		}

		Packet createPacketEx = ((CPlayer*)(*it))->GenerateCreatePacket();

		SendPacket(createPacketEx);

		(*it)->m_Access.Release();
	}

	SendPacketInSight(createPacket);
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

bool CPlayer::CanMove()
{
	if (IsGState(CGS_REST | CGS_KO | CGS_FISH))
	{
		printf("Can't move.\n");

		Write(S2C_MOVEBEFORE, "ddddw", m_nID, m_nX, m_nY, m_nZ, m_wDir);
		return false;
	}

	// CGS_INVISIBLE/CGS_ONPORTAL

	return true;
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

	SetDirection(byX, byY);

	Packet createPacket = GenerateCreatePacket();
	Packet deletePacket = GenerateDeletePacket();
	Packet movePacket =   GenerateMovePacket(byType, byX, byY, byZ);

	for (int i = mapInfoDest.wTileX-1; i <= mapInfoDest.wTileX+1; i++) {
		for (int j = mapInfoDest.wTileY-1; j <= mapInfoDest.wTileY+1; j++) {
			auto pTile = CMap::GetTile(i, j);
			if (pTile)
				pTile->SendMoveAction(this, byX, byY, createPacket, deletePacket, movePacket);
		}
	}
}

void CPlayer::Rest(BYTE byType)
{
	if (byType)
	{
		if (IsGState(CGS_REST))
			return;

		Lock();
		AddGState(CGS_REST);
		Unlock();
		WriteInSight(S2C_ACTION, "dbb", m_nID, AT_REST, byType);
	}
	else
	{
		if (!IsGState(CGS_REST))
			return;

		Lock();
		SubGState(CGS_REST);
		Unlock();
		WriteInSight(S2C_ACTION, "dbb", m_nID, AT_REST, byType);
	}
}

void CPlayer::ProcessMsg(char* szMsg)
{
	if (strlen(szMsg) <= 0) return;

	switch (szMsg[0])
	{
		case '/':
			ChatCommand(szMsg);
			break;

		default:
			WriteInSight(S2C_CHATTING, "ss", m_szName.c_str(), szMsg);
			break;
	}
}

void CPlayer::ChatCommand(char* szCommand)
{
	char *token = std::strtok(szCommand, " ");

	if (!strcmp(token, "/ride")) {
		token = std::strtok(NULL, " ");

		if (token) {
			int nIndex = atoi(token);

			WriteInSight(S2C_RIDING, "bdd", 0, m_nID, nIndex);
		}
	}

	if (!strcmp(token, "/npc")) {
		token = std::strtok(NULL, " ");

		int PACKET=0;
		int nShape=78;

		if (token) {
			PACKET = atoi(token);
			token = std::strtok(NULL, " ");

			if (token)
				nShape = atoi(token);
		}

		WriteInSight(PACKET, "dwbdddwId", 900, 1, nShape, m_nX, m_nY, m_nZ, m_wDir, (__int64)0, (int)0);
	}
}

void CPlayer::UpdateProperty(BYTE byProperty, __int64 n64Amount)
{
	if (!n64Amount) return;

	switch (byProperty)
	{
		case P_STR:
		{
			if ((-n64Amount) > m_wStr)
				n64Amount = -m_wStr;

			m_wStr += n64Amount;

			CPlayer::Write(S2C_UPDATEPROPERTY, "bwwww", P_STR, m_wStr, GetHit(), GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_HTH:
		{
			if ((-n64Amount) > m_wHth)
				n64Amount = -m_wHth;

			m_wHth += n64Amount;

			WORD wMaxHP = GetMaxHP();
			if (m_wCurHP > wMaxHP)
				m_wCurHP = wMaxHP;

			CPlayer::Write(S2C_UPDATEPROPERTY, "bwwww", P_HTH, m_wHth, m_wCurHP, wMaxHP, GetResist(RT_PALSY));
			break;
		}

		case P_INT:
		{
			if ((-n64Amount) > m_wInt)
				n64Amount = -m_wInt;

			m_wInt += n64Amount;

			CPlayer::Write(S2C_UPDATEPROPERTY, "bwwwwww", P_INT, m_wInt, GetMinMagic(), GetMaxMagic(), GetResist(RT_FIRE), GetResist(RT_ICE), GetResist(RT_LITNING));
			break;
		}

		case P_WIS:
		{
			if ((-n64Amount) > m_wWis)
				n64Amount = -m_wWis;

			m_wWis += n64Amount;

			WORD wMaxMP = GetMaxMP();
			if (m_wCurMP > wMaxMP)
				m_wCurMP = wMaxMP;

			CPlayer::Write(S2C_UPDATEPROPERTY, "bwwwwww", P_WIS, m_wWis, m_wCurMP, wMaxMP, GetMinMagic(), GetMaxMagic(), GetResist(RT_CURSE));
			break;
		}

		case P_DEX:
		{
			if ((-n64Amount) > m_wDex)
				n64Amount = -m_wDex;

			m_wDex += n64Amount;

			CPlayer::Write(S2C_UPDATEPROPERTY, "bwwwwww", P_DEX, m_wDex, GetHit(), GetDodge(), GetDodge(), GetMinAttack(), GetMaxAttack());
			break;
		}
	}
}