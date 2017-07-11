#include "CAccount.h"
#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

/*
WORD CAccount::g_wDebugItems[4][8] = {
	1632, 1479, 1480, 1481, 1633, 799, 0, 0,
	1640, 1489, 1490, 1491, 1641, 801, 0, 0,
	1483, 1484, 1485, 1486, 1487, 800, 0, 0,
	1764, 1766, 1767, 1768, 1769, 1441, 0, 0
};
*/
WORD CAccount::g_wDebugItems[4][8] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

CAccount::~CAccount()
{
	while (m_Access.IsBusy()) {
		printf("CAccount::~CAccount: Account is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

void CAccount::SendPlayerInfo(Connection_T con)
{
	PreparedStatement_T ps = Connection_prepareStatement(con,
		"SELECT * FROM player WHERE idaccount=? AND deleted=0 ORDER BY level DESC");
	PreparedStatement_T pcnt = Connection_prepareStatement(con,
		"SELECT COUNT(*) FROM player WHERE idaccount=? AND deleted=0 ORDER BY level DESC");

	PreparedStatement_setInt(ps, 1, GetAID());
	PreparedStatement_setInt(pcnt, 1, GetAID());

	ResultSet_T r = PreparedStatement_executeQuery(ps);
	ResultSet_T rcnt = PreparedStatement_executeQuery(pcnt);

	ResultSet_next(rcnt);

	BYTE byCount = ResultSet_getInt(rcnt, 1);

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));
	char* pBegin = (char*)&buffer;
	char* p = pBegin;
	
	p = CSocket::WritePacket(p, "b", byCount);

	while (ResultSet_next(r)) {
		PreparedStatement_T i = Connection_prepareStatement(con,
			"SELECT `index` FROM item WHERE idplayer=? AND (info & 1) LIMIT 8");
		PreparedStatement_T icnt = Connection_prepareStatement(con,
			"SELECT COUNT(*) FROM item WHERE idplayer=? AND (info & 1) LIMIT 8");

		PreparedStatement_setInt(i, 1, ResultSet_getIntByName(r, "idplayer"));
		PreparedStatement_setInt(icnt, 1, ResultSet_getIntByName(r, "idplayer"));

		ResultSet_T items = PreparedStatement_executeQuery(i);
		ResultSet_T itemcount = PreparedStatement_executeQuery(icnt);

		ResultSet_next(itemcount);

		BYTE byWearAmount=ResultSet_getInt(itemcount, 1);

		int nGID=0;
		BYTE byClass = ResultSet_getIntByName(r, "class");
		p = CSocket::WritePacket(p, "dsbbbdwwwwwbbb", ResultSet_getIntByName(r, "idplayer"),
			ResultSet_getStringByName(r, "name"),
			byClass, ResultSet_getIntByName(r, "job"), ResultSet_getIntByName(r, "level"), nGID,
			ResultSet_getIntByName(r, "strength"), ResultSet_getIntByName(r, "health"), ResultSet_getIntByName(r, "inteligence"),
			ResultSet_getIntByName(r, "wisdom"), ResultSet_getIntByName(r, "dexterity"), ResultSet_getIntByName(r, "face"), 
			ResultSet_getIntByName(r, "hair"), byWearAmount);

		while (ResultSet_next(items))
			p = CSocket::WritePacket(p, "w", ResultSet_getInt(items, 1));
	}

	CMainSocket::Write(D2S_PLAYER_INFO, "dm", m_nClientID, pBegin, p - pBegin);

	printf("D2S_PLAYER_INFO sent.\n");
}