#include "CAccount.h"
#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

WORD CAccount::g_wDebugItems[4][8] = {
	1632, 1479, 1480, 1481, 1633, 799, 0, 0,
	1640, 1489, 1490, 1491, 1641, 801, 0, 0,
	1483, 1484, 1485, 1486, 1487, 800, 0, 0,
	1764, 1766, 1767, 1768, 1769, 1441, 0, 0
};

CAccount::~CAccount()
{
	while (m_Access.IsBusy()) {
		printf("CAccount::~CAccount: Account is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

void CAccount::SendPlayerInfo()
{
	pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
		"SELECT * FROM player WHERE idaccount=? AND deleted=0 ORDER BY level DESC"));
	pPStmt->setInt(1, GetAID());
	rs_ptr rs(pPStmt->executeQuery());

	BYTE byCount = rs->rowsCount();

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));
	char* pBegin = (char*)&buffer;
	char* p = pBegin;
	
	p = CSocket::WritePacket(p, "b", byCount);

	while (rs->next()) {
		BYTE byWearAmount=6;
		int nGID=0;
		BYTE byClass = rs->getInt("class");
		p = CSocket::WritePacket(p, "dsbbbdwwwwwbbbwwwwww", rs->getInt("idplayer"),
			rs->getString("name").c_str(),
			byClass, rs->getInt("job"), rs->getInt("level"), nGID,
			rs->getInt("strength"), rs->getInt("health"), rs->getInt("inteligence"),
			rs->getInt("wisdom"), rs->getInt("dexterity"), rs->getInt("face"), rs->getInt("hair"), byWearAmount,
			g_wDebugItems[byClass][0], g_wDebugItems[byClass][1], g_wDebugItems[byClass][2],
			g_wDebugItems[byClass][3], g_wDebugItems[byClass][4], g_wDebugItems[byClass][5]);
	}

	CMainSocket::Write(D2S_PLAYER_INFO, "dm", m_nClientID, pBegin, p - pBegin);

	printf("D2S_PLAYER_INFO sent.\n");
}

void CAccount::SendItemInfo(int nPID)
{
	pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
		"SELECT * FROM item WHERE idplayer=?"));
	pPStmt->setInt(1, nPID);
	rs_ptr rs(pPStmt->executeQuery());

	printf("About to send %li item rows.\n", rs->rowsCount());

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));
	char* pBegin = (char*)&buffer;
	char* p = pBegin;

	p = CSocket::WritePacket(p, "b", rs->rowsCount());

	BYTE byLimit = MAX_INVENTORYEX;
	while (rs->next())
	{
		if (byLimit-- <= 0) {
			printf(KRED "Player inventory exceeded.\n" KNRM);
			break;
		}

		// 52 BYTE
		p = CSocket::WritePacket(p, "dwddbbbbbbbbbbwwwwbbbbbbbbbbwdd",
			rs->getInt("iditem"),
			rs->getInt("index"),
			rs->getInt("num"),
			rs->getInt("info"),
			rs->getInt("prefix"),
			rs->getInt("curend"),
			rs->getInt("maxend"),
			rs->getInt("xattack"),
			rs->getInt("xmagic"),
			rs->getInt("xdefense"),
			rs->getInt("xhit"),
			rs->getInt("xdodge"),
			rs->getInt("explosiveblow"),
			rs->getInt("fusion"),
			rs->getInt("fmeele"),
			rs->getInt("fmagic"),
			rs->getInt("fdefense"),
			rs->getInt("fabsorb"),
			rs->getInt("fevasion"),
			rs->getInt("fhit"),
			rs->getInt("fhp"),
			rs->getInt("fmp"),
			rs->getInt("fstr"),
			rs->getInt("fhth"),
			rs->getInt("fint"),
			rs->getInt("fwis"),
			rs->getInt("fdex"),
			rs->getInt("shot"),
			rs->getInt("perforation"),
			rs->getInt("gongleft"),
			rs->getInt("gongright"));
	}

	// 52 * 72 + 3 + 4 + 1 = 3752 BYTE MAX
	CMainSocket::Write(D2S_LOADITEMS, "dm", m_nClientID, pBegin, p - pBegin);

	printf("D2S_LOADITEMS sent.\n");
}