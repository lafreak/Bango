#include "CAccount.h"
#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

void CAccount::SendPlayerInfo()
{
	pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
		"SELECT * FROM player WHERE idaccount=? AND deleted=0"));
	pPStmt->setInt(1, GetAID());
	rs_ptr rs(pPStmt->executeQuery());

	BYTE byCount = rs->rowsCount();

	PACKETBUFFER buffer;
	char* pBegin = (char*)&buffer;
	char* p = pBegin;
	
	p = CSocket::WritePacket(p, "b", byCount);

	while (rs->next()) {
		BYTE byWearAmount=0;
		int nGID=0;
		p = CSocket::WritePacket(p, "dsbbbdwwwwwbbb", rs->getInt("idplayer"),
			rs->getString("name").c_str(),
			rs->getInt("class"), rs->getInt("job"), rs->getInt("level"), nGID,
			rs->getInt("strength"), rs->getInt("health"), rs->getInt("inteligence"),
			rs->getInt("wisdom"), rs->getInt("dexterity"), rs->getInt("face"), rs->getInt("hair"), byWearAmount);
	}

	CMainSocket::Write(D2S_PLAYER_INFO, "dm", GetSocket(), pBegin, p - pBegin);

	printf("D2S_PLAYER_INFO sent.\n");
}