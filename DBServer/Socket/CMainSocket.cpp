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
				"EXISTS(SELECT 1 FROM account WHERE login=? AND password=? AND secondary IS NULL) as bIsCreate2nd"));
			pPStmt->setString(1, szLogin);
			pPStmt->setString(2, szLogin);
			pPStmt->setString(3, szPassword);
			pPStmt->setString(4, szLogin);
			pPStmt->setString(5, szPassword);
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			if (!rs->getBoolean("bIsLogin")) {
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGID, nClientID);
				break;
			}

			if (!rs->getBoolean("bIsPW")) {
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGPWD, nClientID);
				break;
			}

			if (!rs->getBoolean("bIsCreate2nd")) {
				//CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);
				CMainSocket::Write(D2S_ACCEPT_CRED, "dssb", nClientID, szLogin, szPassword, LA_OK);
				break;
			}

			//CMainSocket::Write(D2S_LOGIN, "bd", LA_CREATE_SECONDARY, nClientID);
			CMainSocket::Write(D2S_ACCEPT_CRED, "dssb", nClientID, szLogin, szPassword, LA_CREATE_SECONDARY);

			break;
		}

		case S2D_CREATE_SECONDARY:
		{
			printf("S2D_CREATE_SECONDARY.\n");

			int nClientID=0;
			char *szLogin=NULL;
			char *szPassword=NULL;
			char *szSecondaryPW=NULL;

			CSocket::ReadPacket(packet->data, "dsss", &nClientID, &szLogin, &szPassword, &szSecondaryPW);

			printf("ClientID: %d, Login: %s, Password: %s, Secondary Password: %s\n", nClientID, szLogin, szPassword, szSecondaryPW);

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE login=? AND password=?"));
			pPStmt->setString(1, szSecondaryPW);
			pPStmt->setString(2, szLogin);
			pPStmt->setString(3, szPassword);

			if (pPStmt->executeUpdate() > 0)
				CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);
			else
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGPWD, nClientID);

			break;
		}

		case S2D_CHANGE_SECONDARY:
		{
			printf("S2D_CHANGE_SECONDARY.\n");

			int nClientID=0;
			char *szLogin=NULL;
			char *szOldPassword=NULL;
			char *szNewPassword=NULL;

			CSocket::ReadPacket(packet->data, "dsss", &nClientID, &szLogin, &szOldPassword, &szNewPassword);
			
			printf("ClientID: %d, Login: %s, OldPassword: %s, NewPassword: %s\n", nClientID, szLogin, szOldPassword, szNewPassword);

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"UPDATE account SET secondary=? WHERE login=? AND secondary=?"));
			pPStmt->setString(1, szNewPassword);
			pPStmt->setString(2, szLogin);
			pPStmt->setString(3, szOldPassword);

			if (pPStmt->executeUpdate() > 0)
				CMainSocket::Write(D2S_LOGIN, "bd", LA_OK, nClientID);
			else
				CMainSocket::Write(D2S_LOGIN, "bd", LA_WRONGPWD, nClientID);

			break;
		}

		case S2D_SECONDARY_LOGIN:
		{
			printf("S2D_SECONDARY_LOGIN.\n");

			int nClientID=0;
			char *szLogin=NULL;
			char *szPassword=NULL;

			CSocket::ReadPacket(packet->data, "dss", &nClientID, &szLogin, &szPassword);
			
			printf("ClientID: %d, Login: %s, SecondaryPW: %s\n", nClientID, szLogin, szPassword);

			pstmt_ptr pPStmt(CDatabase::g_pConnection->prepareStatement(
				"SELECT "
				"EXISTS(SELECT 1 FROM account WHERE login=? AND secondary=?) as bIsOK"));
			pPStmt->setString(1, szLogin);
			pPStmt->setString(2, szPassword);
			rs_ptr rs(pPStmt->executeQuery());
			rs->next();

			if (!rs->getBoolean("bIsOK")) {
				CMainSocket::Write(D2S_SEC_LOGIN, "bd", MSL_WRONG_PWD, nClientID);
				break;
			}

			//CMainSocket::Write(D2S_PLAYER_INFO, "dssb", nClientID, szLogin, szPassword, LA_CREATE_SECONDARY);

			break;
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
	send(CMainSocket::g_pMainSocket, (char*)&packet, packet.wSize, 0);

	return true;
}

void CMainSocket::DebugRawPacket(Packet *packet)
{
	printf("Incoming S2D packet: [%d]\n", (unsigned char)packet->byType);
	for (int i = 0; i < packet->wSize; i++)
		printf("%d ", ((char*)packet)[i]);
	printf("\n");
}

