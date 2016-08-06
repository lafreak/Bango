#include "CMainSocket.h"

#include "../Database/CDatabase.h"

SOCKET CMainSocket::g_pDBSocket = INVALID_SOCKET;
SOCKET CMainSocket::g_pMainSocket = INVALID_SOCKET;

bool CMainSocket::Start(WORD wPort)
{
	CMainSocket::g_pDBSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CMainSocket::g_pDBSocket <= INVALID_SOCKET) {
		printf("Error creating socket.\n");
		return false;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(wPort);

    if (bind(CMainSocket::g_pDBSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= SOCKET_ERROR) {
    	printf("Bind failed.\n");
    	return false;
    }

    if (listen(CMainSocket::g_pDBSocket, 5) <= SOCKET_ERROR) {
    	printf("Error listening on socket.\n");
    	return false;
    }

	return true;
}

bool CMainSocket::Close()
{
	return true;
}

void CMainSocket::Accept()
{
	if (CMainSocket::g_pDBSocket == INVALID_SOCKET)
		return;

	while (true) {
		CMainSocket::g_pMainSocket = INVALID_SOCKET;

		while (CMainSocket::g_pMainSocket == INVALID_SOCKET)
			CMainSocket::g_pMainSocket = accept(CMainSocket::g_pDBSocket, NULL, NULL);

		printf("MainServer connected.\n");

		while (true)
		{
			Packet *packet = new Packet;
			memset(packet, 0, sizeof(Packet));
			//Sleep?

			int nLen = recv(CMainSocket::g_pMainSocket, packet, MAX_PACKET_LENGTH + (packet->data-(char*)packet), 0);
			if (nLen <= 0 || packet->wSize <=0) {
				CServer::EmptyAccount();
				printf("MainServer disconnected.\n");
				break;
			}

			if (nLen > MAX_PACKET_LENGTH || packet->wSize > MAX_PACKET_LENGTH) continue;

			pthread_t t;
			pthread_create(&t, NULL, &CMainSocket::Process, (PVOID)packet);

			DebugRawPacket(packet);
		}
	}
}

PVOID CMainSocket::Process(PVOID param)
{
	Packet* packet = (Packet*)param;

	switch (packet->byType)
	{
		case S2D_LOGIN:
		{
			printf("S2D_LOGIN.\n");

			int nClientID=0;
			char* szLogin=NULL;
			char* szPassword=NULL;

			CSocket::ReadPacket(packet->data, "dss", &nClientID, &szLogin, &szPassword);

			printf("ClientID: %d, Login: %s, Password: %s\n", nClientID, szLogin, szPassword);

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"SELECT "
				"EXISTS(SELECT 1 FROM account WHERE login=?) as bIsLogin, "
				"EXISTS(SELECT 1 FROM account WHERE login=? AND password=?) as bIsPW, "
				"EXISTS(SELECT 1 FROM account WHERE login=? AND password=? AND secondary IS NULL) as bIsCreate2nd ,"
				"(SELECT idaccount FROM account WHERE login=? AND password=?) as nAccountID"));
			pPStmt->setString(1, szLogin);
			pPStmt->setString(2, szLogin);
			pPStmt->setString(3, szPassword);
			pPStmt->setString(4, szLogin);
			pPStmt->setString(5, szPassword);
			pPStmt->setString(6, szLogin);
			pPStmt->setString(7, szPassword);
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			int nAccountID = rs->getInt("nAccountID");

			if (!rs->getBoolean("bIsLogin")) {
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGID, nClientID);
				break;
			}

			if (!rs->getBoolean("bIsPW")) {
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGPWD, nClientID);
				break;
			}

			auto pAccount = CServer::FindAccountByAID(nAccountID);
			if (pAccount) {
				CMainSocket::Write(D2S_LOGIN, "bdd", LA_SAMEUSER, nClientID, pAccount->GetSocket());
				CServer::Remove(pAccount);
				break;
			}

			CServer::Add(new CAccount(nClientID, nAccountID, std::string(szLogin), std::string(szPassword)));

			if (rs->getBoolean("bIsCreate2nd")) {
				CMainSocket::Write(D2S_LOGIN, "bd", LA_CREATE_SECONDARY, nClientID);
				break;
			}

			CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);

			break;
		}

		case S2D_CREATE_SECONDARY:
		{
			printf("S2D_CREATE_SECONDARY.\n");

			int nClientID=0;
			char *szPassword=NULL;
			char *szSecondaryPW=NULL;

			CSocket::ReadPacket(packet->data, "dss", &nClientID, &szPassword, &szSecondaryPW);

			printf("ClientID: %d, Password: %s, Secondary Password: %s\n", nClientID, szPassword, szSecondaryPW);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE idaccount=? AND password=?"));
			pPStmt->setString(1, szSecondaryPW);
			pPStmt->setInt(2, pAccount->GetAID());
			pPStmt->setString(3, szPassword);

			if (pPStmt->executeUpdate() > 0)
				CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);
			else
				CMainSocket::Write(D2S_SEC_LOGIN, "bd", MSL_WRONG_PWD, nClientID);

			break;
		}

		case S2D_CHANGE_SECONDARY:
		{
			printf("S2D_CHANGE_SECONDARY.\n");

			int nClientID=0;
			char *szOldPassword=NULL;
			char *szNewPassword=NULL;

			CSocket::ReadPacket(packet->data, "dss", &nClientID, &szOldPassword, &szNewPassword);
			
			printf("ClientID: %d, OldPassword: %s, NewPassword: %s\n", nClientID, szOldPassword, szNewPassword);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE idaccount=? AND secondary=?"));
			pPStmt->setString(1, szNewPassword);
			pPStmt->setInt(2, pAccount->GetAID());
			pPStmt->setString(3, szOldPassword);

			if (pPStmt->executeUpdate() > 0)
				CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);
			else
				CMainSocket::Write(D2S_SEC_LOGIN, "bd", MSL_WRONG_PWD, nClientID);

			break;
		}

		case S2D_SECONDARY_LOGIN:
		{
			printf("S2D_SECONDARY_LOGIN.\n");

			int nClientID=0;
			char *szPassword=NULL;

			CSocket::ReadPacket(packet->data, "ds", &nClientID, &szPassword);
			
			printf("ClientID: %d, SecondaryPW: %s\n", nClientID, szPassword);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"SELECT "
				"EXISTS(SELECT 1 FROM account WHERE idaccount=? AND secondary=?) as bIsOK"));
			pPStmt->setInt(1, pAccount->GetAID());
			pPStmt->setString(2, szPassword);
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			if (!rs->getBoolean("bIsOK")) {
				CMainSocket::Write(D2S_SEC_LOGIN, "bd", MSL_WRONG_PWD, nClientID);
				break;
			}

			pAccount->SendPlayerInfo();
/*
			// PLAYER_INFO
			pPStmt.reset(CDatabase::g_pConnection->prepareStatement(
				"SELECT * FROM player WHERE idaccount=? AND deleted=0"));
			pPStmt->setInt(1, pAccount->GetAID());
			rs.reset(pPStmt->executeQuery());

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

			CMainSocket::Write(D2S_PLAYER_INFO, "dm", nClientID, pBegin, p - pBegin);

			printf("D2S_PLAYER_INFO sent.\n");
			*/
			break;
		}

		case S2D_DISCONNECT:
		{
			printf("S2D_DISCONNECT.\n");

			int nClientID=0;

			CSocket::ReadPacket(packet->data, "d", &nClientID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (pAccount)
				CServer::Remove(pAccount);

			break;
		}

		case S2D_DELPLAYER:
		{
			printf("S2D_DISCONNECT.\n");

			int nClientID=0;
			int nPID=0;

			CSocket::ReadPacket(packet->data, "dd", &nClientID, &nPID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE player SET deleted=1 WHERE idaccount=? AND idplayer=?"));
			pPStmt->setInt(1, pAccount->GetAID());
			pPStmt->setInt(2, nPID);

			if (pPStmt->executeUpdate() < 0)
				break;

			pAccount->SendPlayerInfo();
		}
	}

	delete packet;
	return NULL;
}

bool CMainSocket::Write(BYTE byType, ...)
{
	if (CMainSocket::g_pMainSocket == INVALID_SOCKET)
		return false;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;

	return WritePacket(packet);
}

bool CMainSocket::WritePacket(Packet packet)
{
	if (CMainSocket::g_pMainSocket == INVALID_SOCKET)
		return false;

	send(CMainSocket::g_pMainSocket, (char*)&packet, packet.wSize, 0);

	return true;
}

void CMainSocket::DebugRawPacket(Packet *packet)
{
	printf("Incoming S2D packet: [%u]\n", (BYTE)packet->byType);
	for (int i = 0; i < packet->wSize; i++)
		printf("%u ", (BYTE)((char*)packet)[i]);
	printf("\n");
}

