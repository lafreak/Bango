#include "CClientSocket.h"
#include "CDBSocket.h"

SOCKET CClientSocket::g_pSocket = INVALID_SOCKET;

bool CClientSocket::Start(WORD wPort)
{
	CClientSocket::g_pSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CClientSocket::g_pSocket <= INVALID_SOCKET) {
		printf("Error creating socket.\n");
		return false;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(wPort);

    if (bind(CClientSocket::g_pSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= SOCKET_ERROR) {
    	printf("Bind failed.\n");
			CClientSocket::Close();
    	return false;
    }

    if (listen(CClientSocket::g_pSocket, 5) <= SOCKET_ERROR) {
    	printf("Error listening on socket.\n");
    	return false;
    }

	return true;
}

bool CClientSocket::Close()
{
	close(CClientSocket::g_pSocket);
	//shutdown(CClientSocket::g_pSocket, SHUT_RDWR);
	return true;
}

void CClientSocket::Accept()
{
	if (CClientSocket::g_pSocket == INVALID_SOCKET)
		return;

	while (true) {
		intptr_t client = INVALID_SOCKET;

		while (client == INVALID_SOCKET)
			client = accept(CClientSocket::g_pSocket, NULL, NULL);

		pthread_t t;
		pthread_create(&t, NULL, &CClientSocket::Await, (PVOID)client);
	}
}

PVOID CClientSocket::Await(PVOID param)
{
	CClient *pClient = new CClient((intptr_t)param);

	printf("Client[%d] connected.\n", pClient->GetSocket());

	CServer::Add(pClient);

	while (true)
	{
		Packet packet;
		memset(&packet, 0, sizeof(Packet));
		//Sleep?

		int nLen = recv(pClient->GetSocket(), &packet, MAX_PACKET_LENGTH + (packet.data-(char*)&packet), 0);
		if (nLen <= 0 || packet.wSize <=0) {
			printf("Client[%d] disconnected.\n", pClient->GetSocket());
			CDBSocket::Write(S2D_DISCONNECT, "d", pClient->GetSocket());
			CServer::Remove(pClient);
			break;
		}

		if (nLen > MAX_PACKET_LENGTH || packet.wSize > MAX_PACKET_LENGTH) continue;

		DebugRawPacket(packet);

		Process(pClient, packet);
	}

	return NULL;
}

void CClientSocket::Process(CClient * pClient, Packet packet)
{
	switch (packet.byType)
	{
		case C2S_CONNECT:
		{
			DWORD dwSeedL[4] = {0,};
			int nAppTime=0;
			BYTE byUnknown=0;

			CSocket::ReadPacket(packet.data, "dddddb", &nAppTime, &dwSeedL[0], &dwSeedL[1], &dwSeedL[2], &dwSeedL[3], &byUnknown);
			printf("nAppTime: %i\ndwSeedL: %lu %lu %lu %lu\nbyUnknown: %u\n", nAppTime, dwSeedL[0], dwSeedL[1], dwSeedL[2], dwSeedL[3], byUnknown);

			DWORD dwProtocolVersion=0;
			BYTE byCode=0;
			int nTimeStamp=0;
			int nTimeStart=0;
			DWORD dwSystem=0;
			DWORD dwEvent=0;
			BYTE byServerID=0;
			BYTE byAge=0;
			BYTE byCountry=0;

			pClient->Write(S2C_CODE, "dbdddIbbb", dwProtocolVersion, byCode, nTimeStamp, nTimeStart, dwSystem, dwEvent, byServerID, byAge, byCountry);
			printf("S2C_CODE sent.\n");
			break;
		}

		case C2S_ANS_CODE:
		{
			BYTE byUnknown=0;
			DWORD dwProtocolVersion=0;

			CSocket::ReadPacket(packet.data, "bd", &byUnknown, &dwProtocolVersion);
			printf("byUnknown: %u\ndwProtocolVersion: %lu\n", byUnknown, dwProtocolVersion);
			break;
		}

		case C2S_LOGIN:
		{
			char* szLogin=NULL;
			char* szPassword=NULL;
			char* szMac=NULL;

			CSocket::ReadPacket(packet.data, "sss", &szLogin, &szPassword, &szMac);
			printf("Login: %s\nPassword: %s\nMac: %s\n", szLogin, szPassword, szMac);

			CDBSocket::Write(S2D_LOGIN, "dss", pClient->GetSocket(), szLogin, szPassword);
			printf("S2D_LOGIN sent.\n");
			break;
		}

		case C2S_SECOND_LOGIN:
		{
			BYTE byType=0;

			char *p = CSocket::ReadPacket(packet.data, "b", &byType);

			switch (byType)
			{
				case SL_CREATE_PASSWORD:
				{
					char *szPassword=NULL;
					char *szSecondaryPW=NULL;
					CSocket::ReadPacket(p, "ss", &szPassword, &szSecondaryPW);

					if (strlen(szSecondaryPW) != 8) {
						pClient->Write(S2C_CLOSE, "b", CC_KICK);
						break;
					}

					bool bQuit=false;
					for (char i = 0; i < 8; i++) {
						if (szSecondaryPW[i] < '0' || szSecondaryPW[i] > '9') {
							pClient->Write(S2C_CLOSE, "b", CC_KICK);
							bQuit=true; break;
						}
					}

					if (bQuit) break;

					printf("OnCreate PW: %s\nSecondary: %s\n", szPassword, szSecondaryPW);

					CDBSocket::Write(S2D_CREATE_SECONDARY, "dss", pClient->GetSocket(), szPassword, szSecondaryPW);
					break;
				}

				case SL_CHANGE_PASSWORD:
				{
					char *szOldPassword=NULL;
					char *szNewPassword=NULL;

					CSocket::ReadPacket(p, "ss", &szOldPassword, &szNewPassword);

					if (strlen(szOldPassword) != 8 || strlen(szNewPassword) != 8) {
						pClient->Write(S2C_CLOSE, "b", CC_KICK);
						break;
					}

					bool bQuit=false;
					for (char i = 0; i < 8; i++) {
						if (szOldPassword[i] < '0' || szOldPassword[i] > '9' || szNewPassword[i] < '0' || szNewPassword[i] > '9') {
							pClient->Write(S2C_CLOSE, "b", CC_KICK);
							bQuit=true; break;
						}
					}

					if (bQuit) break;

					printf("Old password: %s\nNew password: %s\n", szOldPassword, szNewPassword);

					CDBSocket::Write(S2D_CHANGE_SECONDARY, "dss", pClient->GetSocket(), szOldPassword, szNewPassword);
					break;
				}

				case SL_LOGIN: // Login
				{
					char *szPassword=NULL;
					CSocket::ReadPacket(p, "s", &szPassword);

					printf("Secondary password: %s\n", szPassword);

					if (strlen(szPassword) != 8) {
						pClient->Write(S2C_CLOSE, "b", CC_KICK);
						break;
					}

					bool bQuit=false;
					for (char i = 0; i < 8; i++) {
						if (szPassword[i] < '0' || szPassword[i] > '9') {
							pClient->Write(S2C_CLOSE, "b", CC_KICK);
							bQuit=true; break;
						}
					}

					if (bQuit) break;

					CDBSocket::Write(S2D_SECONDARY_LOGIN, "ds", pClient->GetSocket(), szPassword);

					break;

/*
					BYTE byAuth=0;
					int nExpTime=0;
					BYTE byUnknwon=0;

					BYTE byCount=1;

					int nPID = 16;
					const char* pName = "lafreak";
					BYTE byJob=1;
					BYTE byClass=1;
					BYTE byLevel=100;
					int  nGID=0;
					WORD wStr=105;
					WORD wHth=106;
					WORD wInt=107;
					WORD wWis=108;
					WORD wDex=109;
					BYTE byFace=0;
					BYTE byHair=0;

					BYTE byWearItemCount=6;
					WORD wGloves=1134;
					WORD wBoots=1135;
					WORD wHelm=1136;
					WORD wShorts=1137;
					WORD wChest=1138;
					WORD wStick=668;


								p = ReadPacket( p, "bbd b dsbbdwwwwwbb b www...."


					pClient->Write(S2C_PLAYERINFO, "bbdbdsbbbdwwwwwbbbwwwwww", byAuth, byUnknwon, nExpTime, byCount,
						nPID, pName, byJob, byClass, byLevel, nGID, wStr, wHth, wInt, wWis, wDex, byFace, byHair, byWearItemCount,
						wGloves, wBoots, wHelm, wShorts, wChest, wStick);
					printf("S2C_PLAYERINFO sent.\n");
*/
					break;
				}
			}
			break;
		}

	case C2S_LOADPLAYER:
		{
			int nPID=0;
			int nGID=0;
			int nShow_honorGrade=0;

			CSocket::ReadPacket(packet.data, "ddd", &nPID, &nGID, &nShow_honorGrade);
			printf("Load PID: %d, GID: %d, Show_honorGrade: %d\n", nPID, nGID, nShow_honorGrade);


			//"bsbwwwwwwwwwwwwwbIwwwwwwbbbbbd"
			//"bsbwwwwwwwwwwwwwbIwwwwwwbbbbbd"
			BYTE byGrade=1;
			const char *pGuildName = "bestGuild";
			BYTE byGRole=1;
			WORD wContribute=13;
			WORD wStr=14;
			WORD wHth=15;
			WORD wInt=16;
			WORD wWis=17;
			WORD wDex=18;
			WORD wCurHP=19;
			WORD wMaxHP=20;
			WORD wCurMP=21;
			WORD wMaxMP=22;
			WORD wHit=23;
			WORD wDodge=24;
			WORD wDefense=25;
			BYTE byAbsorb=26;
			__int64 n64Exp=27;
			WORD wMinAttack=28;
			WORD wMaxAttack=29;
			WORD wMinMagic=30;
			WORD wMaxMagic=31;
			WORD wPUPoint=32;
			WORD wSUPoint=33;
			BYTE byFire=34;
			BYTE byIce=35;
			BYTE byLightning=36;
			BYTE byCurse=37;
			BYTE byPalsy=38;
			int nAnger=39;

			pClient->Write(S2C_PROPERTY, "bsbwwwwwwwwwwwwwbIwwwwwwbbbbbd", byGrade, pGuildName, byGRole, wContribute, wStr, wHth, wInt, wWis, wDex,
				wCurHP, wMaxHP, wCurMP, wMaxMP, wHit, wDodge, wDefense, byAbsorb, n64Exp, wMinAttack, wMaxAttack, wMinMagic, wMaxMagic, wPUPoint, wSUPoint, byFire, byIce,
				byLightning, byCurse, byPalsy, nAnger);
			printf("S2C_PROPERTY sent.\n");

			WORD wTime=0;
			int x=232687;
			int y=294749;
			// 232687 294749 45300

			pClient->Write(S2C_ANS_LOAD, "wdd", wTime, x, y);
			printf("S2C_ANS_LOAD sent.\n");

			break;
		}

	case C2S_START:
		{
			BYTE byUnknown=0;
			int nHeight=0;

			CSocket::ReadPacket(packet.data, "bd", &byUnknown, &nHeight);
			printf("byUnknown: %d, nHeight: %d\n", byUnknown, nHeight);

			int nID=300;
			const char *szName = "lafreak";
			BYTE byJob=0; byJob |= 0x80;
			int nX=232687;
			int nY=294749;
			int nZ=45300;
			WORD wDir=0;
			__int64 n64GState=0;
			WORD pWear[8] = {0,};
			pWear[0] = 1631;
			pWear[1] = 1479;
			pWear[2] = 1480;
			pWear[3] = 1481;
			pWear[4] = 1633;
			pWear[5] = 799;
			BYTE byFace=1;
			BYTE byHair=1;
			__int64 n64MState=0;
			const char *szGuildClass = "guild";
			const char *szGuildName = "name";
			int nGuildID=0;
			BYTE byFlag=0;
			int nFlagItem=0;
			int nHonorGrade=0;
			int nHonorOption=0;
			__int64 n64GStateEx=0;
			__int64 n64MStateEx=0;
			BYTE byUnknownV=0;

			BYTE byUn1=0;
			int nUn2=0;
			BYTE byUn3=0;
			int nUn4=0;
			int nUn5=0;
			BYTE byUn6=0;

			pClient->Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbdbddb", nID, szName, byJob, nX, nY, nZ, wDir, n64GState,
				pWear[0], pWear[1], pWear[2], pWear[3], pWear[4], pWear[5], pWear[6], pWear[7],
				byFace, byHair, n64MState, szGuildClass, szGuildName, nGuildID, byFlag, nFlagItem, nHonorGrade, nHonorOption, n64GStateEx, n64MStateEx, byUnknownV,
				byUn1, nUn2, byUn3, nUn4, nUn5, byUn6);

			byJob=0;

			pClient->Write(S2C_CREATEPLAYER, "dsbdddwIwwwwwwwwbbIssdbdddIIbbdbddb", nID, szName, byJob, nX, nY, nZ, wDir, n64GState,
				pWear[0], pWear[1], pWear[2], pWear[3], pWear[4], pWear[5], pWear[6], pWear[7],
				byFace, byHair, n64MState, szGuildClass, szGuildName, nGuildID, byFlag, nFlagItem, nHonorGrade, nHonorOption, n64GStateEx, n64MStateEx, byUnknownV,
				byUn1, nUn2, byUn3, nUn4, nUn5, byUn6);
			printf("S2C_CREATEPLAYER sent.\n");

			break;
		}

	case 48:
		{

		}
	}
}

bool CClientSocket::Write(SOCKET client, BYTE byType, ...)
{
	if (client == INVALID_SOCKET)
		return false;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	send(client, (char*)&packet, packet.wSize, 0);

	return true;
}

void CClientSocket::DebugRawPacket(Packet packet)
{
	printf("Incoming C2S packet: [%d]\n", (unsigned char)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%d ", ((char*)&packet)[i]);
	printf("\n");
}
