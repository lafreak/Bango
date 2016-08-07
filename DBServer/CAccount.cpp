#include "CAccount.h"
#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

WORD CAccount::g_wDebugItems[4][8] = {
	1632, 1479, 1480, 1481, 1633, 799, 0, 0,
	1640, 1489, 1490, 1491, 1641, 801, 0, 0,
	1483, 1484, 1485, 1486, 1487, 800, 0, 0,
	1764, 1766, 1767, 1768, 1769, 1441, 0, 0
};

void CAccount::SendPlayerInfo()
{
	pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
		"SELECT * FROM player WHERE idaccount=? AND deleted=0 ORDER BY level DESC"));
	pPStmt->setInt(1, GetAID());
	rs_ptr rs(pPStmt->executeQuery());

	BYTE byCount = rs->rowsCount();

	PACKETBUFFER buffer;
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