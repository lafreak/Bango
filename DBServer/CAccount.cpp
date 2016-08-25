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

void CAccount::SendPlayerInfo()
{
	Connection_T con = ConnectionPool_getConnection(CDatabase::g_pConnectionPool);
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

void CAccount::SendItemInfo(int nPID)
{
	Connection_T con = ConnectionPool_getConnection(CDatabase::g_pConnectionPool);
	PreparedStatement_T ps = Connection_prepareStatement(con, 
		"SELECT * FROM item WHERE idplayer=?");
	PreparedStatement_T pscount = Connection_prepareStatement(con, 
		"SELECT COUNT(*) FROM item WHERE idplayer=?");

	PreparedStatement_setInt(ps, 1, nPID);
	PreparedStatement_setInt(pscount, 1, nPID);

	ResultSet_T r = PreparedStatement_executeQuery(ps);
	ResultSet_T rcount = PreparedStatement_executeQuery(pscount);

	ResultSet_next(rcount);

	printf("About to send %d item rows.\n", ResultSet_getInt(rcount, 1));

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));
	char* pBegin = (char*)&buffer;
	char* p = pBegin;

	p = CSocket::WritePacket(p, "b", ResultSet_getInt(rcount, 1));

	BYTE byLimit = MAX_INVENTORYEX;
	while (ResultSet_next(r))
	{
		if (byLimit-- <= 0) {
			printf(KRED "Player inventory exceeded.\n" KNRM);
			break;
		}

		// 52 BYTE
		p = CSocket::WritePacket(p, "dwddbbbbbbbbbbwwwwbbbbbbbbbbwdd",
			ResultSet_getIntByName(r, "iditem"),
			ResultSet_getIntByName(r, "index"),
			ResultSet_getIntByName(r, "num"),
			ResultSet_getIntByName(r, "info"),
			ResultSet_getIntByName(r, "prefix"),
			ResultSet_getIntByName(r, "curend"),
			ResultSet_getIntByName(r, "maxend"),
			ResultSet_getIntByName(r, "xattack"),
			ResultSet_getIntByName(r, "xmagic"),
			ResultSet_getIntByName(r, "xdefense"),
			ResultSet_getIntByName(r, "xhit"),
			ResultSet_getIntByName(r, "xdodge"),
			ResultSet_getIntByName(r, "explosiveblow"),
			ResultSet_getIntByName(r, "fusion"),
			ResultSet_getIntByName(r, "fmeele"),
			ResultSet_getIntByName(r, "fmagic"),
			ResultSet_getIntByName(r, "fdefense"),
			ResultSet_getIntByName(r, "fabsorb"),
			ResultSet_getIntByName(r, "fevasion"),
			ResultSet_getIntByName(r, "fhit"),
			ResultSet_getIntByName(r, "fhp"),
			ResultSet_getIntByName(r, "fmp"),
			ResultSet_getIntByName(r, "fstr"),
			ResultSet_getIntByName(r, "fhth"),
			ResultSet_getIntByName(r, "fint"),
			ResultSet_getIntByName(r, "fwis"),
			ResultSet_getIntByName(r, "fdex"),
			ResultSet_getIntByName(r, "shot"),
			ResultSet_getIntByName(r, "perforation"),
			ResultSet_getIntByName(r, "gongleft"),
			ResultSet_getIntByName(r, "gongright"));
	}

	Connection_close(con);

	// 52 * 72 + 3 + 4 + 1 = 3752 BYTE MAX
	CMainSocket::Write(D2S_LOADITEMS, "dm", m_nClientID, pBegin, p - pBegin);

	printf("D2S_LOADITEMS sent.\n");
}