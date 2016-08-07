#include <Socket/CSocket.h>

#include "Socket/CDBSocket.h"

#include "CPlayer.h"

WORD CPlayer::g_wDebugItems[4][8] = {
	1632, 1479, 1480, 1481, 1633, 799, 0, 0,
	1640, 1489, 1490, 1491, 1641, 801, 0, 0,
	1636, 1484, 1485, 1486, 1637, 800, 0, 0,
	1764, 1766, 1767, 1768, 1769, 1441, 0, 0
};

CPlayer::CPlayer(SOCKET pSocket, D2S_LOADPLAYER_DESC desc): CCharacter()
{
	m_pSocket = pSocket;

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

	// temp defaults
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
	send(m_pSocket, (char*)&packet, packet.wSize, 0);

	return true;
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

			SendCreateHero();

			break;
		}

		case C2S_GAMEEXIT:
		{
			Write(S2C_ANS_GAMEEXIT, "b", 1);
			break;	
		}

		// debug
		case C2S_CHATTING:
		{
			char* szMsg=NULL;

			CSocket::ReadPacket(packet.data, "s", &szMsg);



			int pkt = atoi(szMsg);



			BYTE byMode=0;
			int nID=m_nID;
			int nIndex=3416;


			Write(198, "bdd", byMode, nID, pkt);
			printf("%d sent.\n", pkt);
			break;
		}
	}
}

void CPlayer::SendProperty()
{
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
}

void CPlayer::SendCreateHero()
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
	int nUn2=3412;
	int nUn3=32768;
	BYTE byUn4=0;
	//270498 268285
	printf("nID %d\n szName %s\n", m_nID, m_szName.c_str());

  //Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbdbddb", 
	Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbddb", 
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
		/*
		nUn2, 
		byUn3, 
		nUn4, 
		nUn5, 
		byUn6);
		*/
		nUn2,
		nUn3,
		byUn4);


  //Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbdbddb", 
	Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbddb", 
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
		/*
		nUn2, 
		byUn3, 
		nUn4, 
		nUn5, 
		byUn6);
		*/
		nUn2,
		nUn3,
		byUn4);

	printf("S2C_CREATEPLAYER sent.\n");
}