#include "CMainSocket.h"

#include "../Database/CDatabase.h"

SOCKET CMainSocket::g_pDBSocket = INVALID_SOCKET;
SOCKET CMainSocket::g_pMainSocket = INVALID_SOCKET;

bool CMainSocket::Start(WORD wPort)
{
	CMainSocket::g_pDBSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CMainSocket::g_pDBSocket <= INVALID_SOCKET) {
		printf(KRED "Error creating socket.\n" KNRM);
		return false;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(wPort);

    if (bind(CMainSocket::g_pDBSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= SOCKET_ERROR) {
    	printf(KRED "Bind failed.\n" KNRM);
    	return false;
    }

    if (listen(CMainSocket::g_pDBSocket, 5) <= SOCKET_ERROR) {
    	printf(KRED "Error listening on socket.\n" KNRM);
    	return false;
    }

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = CMainSocket::Close;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

	return true;
}

void CMainSocket::Close(int)
{
	CDatabase::Close();
	close(CMainSocket::g_pDBSocket);
	exit(1);
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
	CDatabase::Lock();

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
				"(SELECT idaccount FROM account WHERE login=? AND password=?) as nAccountID, "
				"(SELECT secondary FROM account WHERE login=? AND password=?) as szSecondary"));
			pPStmt->setString(1, szLogin);
			pPStmt->setString(2, szLogin);
			pPStmt->setString(3, szPassword);
			pPStmt->setString(4, szLogin);
			pPStmt->setString(5, szPassword);
			pPStmt->setString(6, szLogin);
			pPStmt->setString(7, szPassword);
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			if (!rs->getBoolean("bIsLogin")) {
				CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_WRONGID);
				break;
			}

			if (!rs->getBoolean("bIsPW")) {
				CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_WRONGPWD);
				break;
			}

			int nAccountID = rs->getInt("nAccountID");
			std::string szSecondary = rs->getString("szSecondary");

			auto pAccount = CServer::FindAccountByAID(nAccountID);
			if (pAccount) {
				CMainSocket::Write(D2S_LOGIN, "dbd", nClientID, LA_SAMEUSER, pAccount->GetCID());
				CServer::Remove(pAccount);
				break;
			}

			CServer::Add(new CAccount(nClientID, nAccountID, std::string(szLogin), std::string(szPassword), szSecondary));

			if (szSecondary.empty()) {
				CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_CREATE_SECONDARY);
				break;
			}

			CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_OK);

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

			if (pAccount->GetPassword() != std::string(szPassword)) {
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
				break;
			}

			pAccount->SetSecondary(std::string(szSecondaryPW));

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE idaccount=?"));
			pPStmt->setString(1, szSecondaryPW);
			pPStmt->setInt(2, pAccount->GetAID());

			pPStmt->executeUpdate();
			CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_OK);
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

			if (pAccount->GetSecondary() != std::string(szOldPassword)) {
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
				break;
			}

			pAccount->SetSecondary(std::string(szNewPassword));

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE idaccount=?"));
			pPStmt->setString(1, szNewPassword);
			pPStmt->setInt(2, pAccount->GetAID());

			pPStmt->executeUpdate();
			CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_OK);
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

			if (pAccount->GetSecondary() != std::string(szPassword)) {
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
				break;
			}

			pAccount->SendPlayerInfo();
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
			break;
		}

		case S2D_NEWPLAYER:
		{
			printf("S2D_NEWPLAYER.\n");

			int nClientID=0;

			char *p = CSocket::ReadPacket(packet->data, "d", &nClientID);
			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			char* szName=NULL;
			BYTE byJob=0;
			WORD wStats[5]={0,};
			BYTE byShape[2]={0,};

			CSocket::ReadPacket(p, "sbwwwwwbb", &szName, &byJob, &wStats[0], &wStats[1], &wStats[2], &wStats[3], &wStats[4], &byShape[0], &byShape[1]);

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"SELECT "
				"EXISTS(SELECT 1 FROM player WHERE name=?) as bIsDuplicate, "
				"(SELECT COUNT(*) FROM player WHERE idaccount=? AND deleted=0) as byCount"));
			pPStmt->setString(1, std::string(szName));
			pPStmt->setInt(2, pAccount->GetAID());
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			if (rs->getBoolean("bIsDuplicate")) {
				CMainSocket::Write(D2S_ANS_NEWPLAYER, "db", nClientID, NA_OCCUPIEDID);
				break;
			}

			if (rs->getInt("byCount") >= MAX_CHARACTER) {
				CMainSocket::Write(D2S_ANS_NEWPLAYER, "db", nClientID, NA_OVERPLAYERNUM);
				break;
			}

			pPStmt.reset(CDatabase::g_pConnection->prepareStatement(
				"INSERT INTO player (idaccount, name, class, strength, health, inteligence, wisdom, dexterity, curhp, curmp, face, hair) "
				" VALUES (?,?,?,?,?,?,?,?,?,?,?,?)"));
			pPStmt->setInt(1, pAccount->GetAID());
			pPStmt->setString(2, szName);
			pPStmt->setInt(3, byJob);
			pPStmt->setInt(4, g_baseproperty[byJob].prty[STAT_STR] + wStats[STAT_STR]);
			pPStmt->setInt(5, g_baseproperty[byJob].prty[STAT_HTH] + wStats[STAT_HTH]);
			pPStmt->setInt(6, g_baseproperty[byJob].prty[STAT_INT] + wStats[STAT_INT]);
			pPStmt->setInt(7, g_baseproperty[byJob].prty[STAT_WIS] + wStats[STAT_WIS]);
			pPStmt->setInt(8, g_baseproperty[byJob].prty[STAT_AGI] + wStats[STAT_AGI]);
			pPStmt->setInt(9, g_denoHP[byJob] *(g_baseproperty[byJob].prty[STAT_HTH] + wStats[STAT_HTH]));
			pPStmt->setInt(10, g_denoMP[byJob] *(g_baseproperty[byJob].prty[STAT_WIS] + wStats[STAT_WIS]));
			pPStmt->setInt(11, byShape[0]);
			pPStmt->setInt(12, byShape[1]);
			pPStmt->execute();

			pAccount->SendPlayerInfo();
			break;
		}

		case S2D_LOADPLAYER:
		{
			printf("S2D_LOADPLAYER.\n");
			int nPID=0;
			int nClientID=0;

			CSocket::ReadPacket(packet->data, "dd", &nClientID, &nPID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"SELECT * FROM player WHERE idplayer=? AND idaccount=? AND deleted=0"));
			pPStmt->setInt(1, nPID);
			pPStmt->setInt(2, pAccount->GetAID());
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			BYTE byMessage=0;

			if (rs->rowsCount() <= 0) {
				byMessage=1;
				CMainSocket::Write(D2S_LOADPLAYER, "db", nClientID, byMessage);
				break;
			}

			CMainSocket::Write(D2S_LOADPLAYER, "dbddsbbbwwwwwwwIwwwddddbb", nClientID, byMessage,
				rs->getInt("idaccount"), 
				rs->getInt("idplayer"), 
				rs->getString("name").c_str(),
				rs->getInt("class"), 
				rs->getInt("job"), 
				rs->getInt("level"),
				rs->getInt("strength"), 
				rs->getInt("health"), 
				rs->getInt("inteligence"), 
				rs->getInt("wisdom"), 
				rs->getInt("dexterity"),
				rs->getInt("curhp"), 
				rs->getInt("curmp"), 
				rs->getUInt64("exp"), 
				rs->getInt("pupoint"), 
				rs->getInt("supoint"), 
				rs->getInt("contribute"), 
				rs->getInt("anger"),
				rs->getInt("x"), 
				rs->getInt("y"), 
				rs->getInt("z"),
				rs->getInt("face"),
				rs->getInt("hair"));

			break;
		}

		case S2D_SELECT_CHARACTER:
		{
			printf("S2D_SELECT_CHARACTER.\n");

			int nClientID=0;

			char *p = CSocket::ReadPacket(packet->data, "d", &nClientID);
			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (pAccount)
				pAccount->SendPlayerInfo();

			break;
		}
	}

	CDatabase::Unlock();
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

