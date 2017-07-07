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
/*
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
			printf("recv: wSize [%d] nLen [%d]\n", packet->wSize, nLen);

			if (nLen <= 0 || packet->wSize <=0) {
				delete packet;
				CServer::EmptyAccount();
				printf("MainServer disconnected.\n");
				break;
			}

			if (nLen > MAX_PACKET_LENGTH || packet->wSize > MAX_PACKET_LENGTH) continue;

			pthread_t t;
			pthread_create(&t, NULL, &CMainSocket::Process, (PVOID)packet);

			DebugRawPacket(packet);

			static int l;
			if (packet->byType == S2D_SAVEALLPROPERTY) {
				l++;
				printf("SAVE ALL PROPERTY MAN: %d\n", l);
			}
		}
	}
}
*/

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
			PACKETBUFFER buffer;
			memset(&buffer, 0, sizeof(PACKETBUFFER));

			int nLen = recv(CMainSocket::g_pMainSocket, &buffer, sizeof(PACKETBUFFER), 0);

			if (nLen <= 0) {
				CServer::EmptyAccount();
				printf("MainServer disconnected.\n");
				break;
			}

			if (nLen > MAX_PACKET_LENGTH) continue;

			// Cut buffer into packets
			char *p = (char*)&buffer;
			while (nLen > 0 && nLen >= *(WORD*)p) 
			{
				/*
				Packet *packet = new Packet;
				memset(packet, 0, sizeof(Packet));
				memcpy(packet, p, *(WORD*)p);

				pthread_t t;
				pthread_create(&t, NULL, &CMainSocket::Process, (PVOID)packet);

				DebugRawPacket(packet);
				*/

				Packet packet;
				memset(&packet, 0, sizeof(Packet));
				memcpy(&packet, p, *(WORD*)p);

				//pthread_t t;
				//pthread_create(&t, NULL, &CMainSocket::Process, (PVOID)packet);

				Process(packet);

				DebugRawPacket(packet);

				nLen -= *(WORD*)p;
				p += *(WORD*)p;
			}

		}
	}
}

//PVOID CMainSocket::Process(PVOID param)
void CMainSocket::Process(Packet& packet)
{
	//Packet* packet = (Packet*)param;

	CDatabase::Lock();

	Connection_T con = ConnectionPool_getConnection(CDatabase::g_pConnectionPool);

	switch (packet.byType)
	{
		case S2D_LOGIN:
		{
			printf("S2D_LOGIN.\n");

			int nClientID=0;
			char* szLogin=NULL;
			char* szPassword=NULL;

			CSocket::ReadPacket(packet.data, "dss", &nClientID, &szLogin, &szPassword);

			printf("ClientID: %d, Login: %s, Password: %s\n", nClientID, szLogin, szPassword);

			PreparedStatement_T p = Connection_prepareStatement(con,
				"SELECT "
				"EXISTS(SELECT 1 FROM account WHERE login=?) as bIsLogin, "
				"EXISTS(SELECT 1 FROM account WHERE login=? AND password=?) as bIsPW, "
				"(SELECT idaccount FROM account WHERE login=? AND password=?) as nAccountID, "
				"(SELECT secondary FROM account WHERE login=? AND password=?) as szSecondary");

			PreparedStatement_setString(p, 1, szLogin);
			PreparedStatement_setString(p, 2, szLogin);
			PreparedStatement_setString(p, 3, szPassword);
			PreparedStatement_setString(p, 4, szLogin);
			PreparedStatement_setString(p, 5, szPassword);
			PreparedStatement_setString(p, 6, szLogin);
			PreparedStatement_setString(p, 7, szPassword);

			ResultSet_T r = PreparedStatement_executeQuery(p);
			ResultSet_next(r);

			if (ResultSet_getIntByName(r, "bIsLogin") == 0) {
				CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_WRONGID);
				break;
			}

			if (ResultSet_getIntByName(r, "bIsPW") == 0) {
				CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_WRONGPWD);
				break;
			}

			int nAccountID = ResultSet_getIntByName(r, "nAccountID");
			const char* secondary = ResultSet_getStringByName(r, "szSecondary");

			std::string szSecondary(secondary ? secondary : "");

			auto pAccount = CServer::FindAccountByAID(nAccountID);
			if (pAccount) {
				CMainSocket::Write(D2S_LOGIN, "dbd", nClientID, LA_SAMEUSER, pAccount->GetCID());
				pAccount->m_Access.Release();
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

			CSocket::ReadPacket(packet.data, "dss", &nClientID, &szPassword, &szSecondaryPW);

			printf("ClientID: %d, Password: %s, Secondary Password: %s\n", nClientID, szPassword, szSecondaryPW);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			if (pAccount->GetPassword() != std::string(szPassword)) {
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
				pAccount->m_Access.Release();
				break;
			}

			pAccount->Lock();
			pAccount->SetSecondary(std::string(szSecondaryPW));
			pAccount->Unlock();

			PreparedStatement_T p = Connection_prepareStatement(con,
				"UPDATE account SET secondary=? WHERE idaccount=?");

			PreparedStatement_setString(p, 1, szSecondaryPW);
			PreparedStatement_setInt(p, 2, pAccount->GetAID());

			PreparedStatement_execute(p);

			CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_OK);

			pAccount->m_Access.Release();
			break;
		}

		case S2D_CHANGE_SECONDARY:
		{
			printf("S2D_CHANGE_SECONDARY.\n");

			int nClientID=0;
			char *szOldPassword=NULL;
			char *szNewPassword=NULL;

			CSocket::ReadPacket(packet.data, "dss", &nClientID, &szOldPassword, &szNewPassword);
			
			printf("ClientID: %d, OldPassword: %s, NewPassword: %s\n", nClientID, szOldPassword, szNewPassword);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			if (pAccount->GetSecondary() != std::string(szOldPassword)) {
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
				pAccount->m_Access.Release();
				break;
			}

			pAccount->Lock();
			pAccount->SetSecondary(std::string(szNewPassword));
			pAccount->Unlock();

			PreparedStatement_T p = Connection_prepareStatement(con,
				"UPDATE account SET secondary=? WHERE idaccount=?");

			PreparedStatement_setString(p, 1, szNewPassword);
			PreparedStatement_setInt(p, 2, pAccount->GetAID());

			PreparedStatement_execute(p);

			CMainSocket::Write(D2S_LOGIN, "db", nClientID, LA_OK);

			pAccount->m_Access.Release();
			break;
		}

		case S2D_SECONDARY_LOGIN:
		{
			printf("S2D_SECONDARY_LOGIN.\n");

			int nClientID=0;
			char *szPassword=NULL;

			CSocket::ReadPacket(packet.data, "ds", &nClientID, &szPassword);
			
			printf("ClientID: %d, SecondaryPW: %s\n", nClientID, szPassword);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			if (pAccount->GetSecondary() != std::string(szPassword))
				CMainSocket::Write(D2S_SEC_LOGIN, "db", nClientID, MSL_WRONG_PWD);
			else
				pAccount->SendPlayerInfo(con);

			pAccount->m_Access.Release();
			break;
		}

		case S2D_DISCONNECT:
		{
			printf("S2D_DISCONNECT.\n");

			int nClientID=0;

			CSocket::ReadPacket(packet.data, "d", &nClientID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (pAccount) {
				pAccount->m_Access.Release();
				CServer::Remove(pAccount);
			}

			break;
		}

		case S2D_DELPLAYER:
		{
			printf("S2D_DISCONNECT.\n");

			int nClientID=0;
			int nPID=0;

			CSocket::ReadPacket(packet.data, "dd", &nClientID, &nPID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			PreparedStatement_T p = Connection_prepareStatement(con, 
				"UPDATE player SET deleted=1 WHERE idaccount=? AND idplayer=?");

			PreparedStatement_setInt(p, 1, pAccount->GetAID());
			PreparedStatement_setInt(p, 2, nPID);

			PreparedStatement_execute(p);

			//?
			//if (PreparedStatement_rowsChanged(p) > 0)
				pAccount->SendPlayerInfo(con);

			pAccount->m_Access.Release();
			break;
		}

		case S2D_NEWPLAYER:
		{
			printf("S2D_NEWPLAYER.\n");

			int nClientID=0;

			char *p = CSocket::ReadPacket(packet.data, "d", &nClientID);
			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			char* szName=NULL;
			BYTE byJob=0;
			WORD wStats[5]={0,};
			BYTE byShape[2]={0,};

			CSocket::ReadPacket(p, "sbwwwwwbb", &szName, &byJob, &wStats[0], &wStats[1], &wStats[2], &wStats[3], &wStats[4], &byShape[0], &byShape[1]);

			PreparedStatement_T ps = Connection_prepareStatement(con, 
				"SELECT "
				"EXISTS(SELECT 1 FROM player WHERE name=?) as bIsDuplicate, "
				"(SELECT COUNT(*) FROM player WHERE idaccount=? AND deleted=0) as byCount");

			PreparedStatement_setString(ps, 1, szName);
			PreparedStatement_setInt(ps, 2, pAccount->GetAID());

			ResultSet_T r = PreparedStatement_executeQuery(ps);
			ResultSet_next(r);

			if (ResultSet_getIntByName(r, "bIsDuplicate")) {
				CMainSocket::Write(D2S_ANS_NEWPLAYER, "db", nClientID, NA_OCCUPIEDID);
				pAccount->m_Access.Release();
				break;
			}

			if (ResultSet_getIntByName(r, "byCount") >= MAX_CHARACTER) {
				CMainSocket::Write(D2S_ANS_NEWPLAYER, "db", nClientID, NA_OVERPLAYERNUM);
				pAccount->m_Access.Release();
				break;
			}

			ps = Connection_prepareStatement(con, 
				"INSERT INTO player (idaccount, name, class, strength, health, inteligence, wisdom, dexterity, curhp, curmp, face, hair) "
				" VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");

			PreparedStatement_setInt(ps, 1, pAccount->GetAID());
			PreparedStatement_setString(ps, 2, szName);
			PreparedStatement_setInt(ps, 3, byJob);
			PreparedStatement_setInt(ps, 4, g_baseproperty[byJob].prty[P_STR] + wStats[P_STR]);
			PreparedStatement_setInt(ps, 5, g_baseproperty[byJob].prty[P_HTH] + wStats[P_HTH]);
			PreparedStatement_setInt(ps, 6, g_baseproperty[byJob].prty[P_INT] + wStats[P_INT]);
			PreparedStatement_setInt(ps, 7, g_baseproperty[byJob].prty[P_WIS] + wStats[P_WIS]);
			PreparedStatement_setInt(ps, 8, g_baseproperty[byJob].prty[P_DEX] + wStats[P_DEX]);
			PreparedStatement_setInt(ps, 9, g_denoHP[byJob] *(g_baseproperty[byJob].prty[P_HTH] + wStats[P_HTH]));
			PreparedStatement_setInt(ps, 10, g_denoMP[byJob] *(g_baseproperty[byJob].prty[P_WIS] + wStats[P_WIS]));
			PreparedStatement_setInt(ps, 11, byShape[0]);
			PreparedStatement_setInt(ps, 12, byShape[1]);

			PreparedStatement_execute(ps);

			pAccount->SendPlayerInfo(con);
			pAccount->m_Access.Release();
			break;
		}

		case S2D_LOADPLAYER:
		{
			printf("S2D_LOADPLAYER.\n");
			int nPID=0;
			int nClientID=0;

			CSocket::ReadPacket(packet.data, "dd", &nClientID, &nPID);

			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (!pAccount) break;

			PreparedStatement_T preparedPlayer = Connection_prepareStatement(con,
				"SELECT * FROM player WHERE idplayer=? AND idaccount=? AND deleted=0");

			PreparedStatement_setInt(preparedPlayer, 1, nPID);
			PreparedStatement_setInt(preparedPlayer, 2, pAccount->GetAID());

			ResultSet_T resultPlayer = PreparedStatement_executeQuery(preparedPlayer);

			BYTE byMessage=0;

			if (!ResultSet_next(resultPlayer)) {
				byMessage=1;
				CMainSocket::Write(D2S_LOADPLAYER, "db", nClientID, byMessage);
				pAccount->m_Access.Release();
				break;
			}

			PACKETBUFFER buffer;
			memset(&buffer, 0, sizeof(PACKETBUFFER));
			char* pBegin = (char*)&buffer;
			char* p = pBegin;

			p = CSocket::WritePacket(p, "dbddsbbbwwwwwdwIwwwddddbb", nClientID, byMessage,
				ResultSet_getIntByName(resultPlayer, "idaccount"), 
				nPID, 
				ResultSet_getStringByName(resultPlayer, "name"),
				ResultSet_getIntByName(resultPlayer, "class"), 
				ResultSet_getIntByName(resultPlayer, "job"), 
				ResultSet_getIntByName(resultPlayer, "level"),
				ResultSet_getIntByName(resultPlayer, "strength"), 
				ResultSet_getIntByName(resultPlayer, "health"), 
				ResultSet_getIntByName(resultPlayer, "inteligence"), 
				ResultSet_getIntByName(resultPlayer, "wisdom"), 
				ResultSet_getIntByName(resultPlayer, "dexterity"),
				ResultSet_getIntByName(resultPlayer, "curhp"), 
				ResultSet_getIntByName(resultPlayer, "curmp"), 
				ResultSet_getLLongByName(resultPlayer, "exp"), 
				ResultSet_getIntByName(resultPlayer, "pupoint"), 
				ResultSet_getIntByName(resultPlayer, "supoint"), 
				ResultSet_getIntByName(resultPlayer, "contribute"), 
				ResultSet_getIntByName(resultPlayer, "anger"),
				ResultSet_getIntByName(resultPlayer, "x"), 
				ResultSet_getIntByName(resultPlayer, "y"), 
				ResultSet_getIntByName(resultPlayer, "z"),
				ResultSet_getIntByName(resultPlayer, "face"),
				ResultSet_getIntByName(resultPlayer, "hair"));

			PreparedStatement_T preparedItemlist = Connection_prepareStatement(con, 
				"SELECT * FROM item WHERE idplayer=?");
			PreparedStatement_T preparedItemCount = Connection_prepareStatement(con, 
				"SELECT COUNT(*) FROM item WHERE idplayer=?");

			PreparedStatement_setInt(preparedItemlist, 1, nPID);
			PreparedStatement_setInt(preparedItemCount, 1, nPID);

			ResultSet_T resultItemlist = PreparedStatement_executeQuery(preparedItemlist);
			ResultSet_T resultItemCount = PreparedStatement_executeQuery(preparedItemCount);

			ResultSet_next(resultItemCount);

			BYTE byItemCount = ResultSet_getInt(resultItemCount, 1);
			printf("About to send %d item rows.\n", byItemCount);

			p = CSocket::WritePacket(p, "b", byItemCount > MAX_INVENTORYEX ? MAX_INVENTORYEX : byItemCount);

			BYTE byLimit = MAX_INVENTORYEX;
			while (ResultSet_next(resultItemlist))
			{
				if (byLimit-- <= 0) {
					printf(KRED "Player inventory exceeded.\n" KNRM);
					break;
				}

				// 52 BYTE
				p = CSocket::WritePacket(p, "dwddbbbbbbbbbbwwwwbbbbbbbbbbwdd",
					ResultSet_getIntByName(resultItemlist, "iditem"),
					ResultSet_getIntByName(resultItemlist, "index"),
					ResultSet_getIntByName(resultItemlist, "num"),
					ResultSet_getIntByName(resultItemlist, "info"),
					ResultSet_getIntByName(resultItemlist, "prefix"),
					ResultSet_getIntByName(resultItemlist, "curend"),
					ResultSet_getIntByName(resultItemlist, "maxend"),
					ResultSet_getIntByName(resultItemlist, "xattack"),
					ResultSet_getIntByName(resultItemlist, "xmagic"),
					ResultSet_getIntByName(resultItemlist, "xdefense"),
					ResultSet_getIntByName(resultItemlist, "xhit"),
					ResultSet_getIntByName(resultItemlist, "xdodge"),
					ResultSet_getIntByName(resultItemlist, "explosiveblow"),
					ResultSet_getIntByName(resultItemlist, "fusion"),
					ResultSet_getIntByName(resultItemlist, "fmeele"),
					ResultSet_getIntByName(resultItemlist, "fmagic"),
					ResultSet_getIntByName(resultItemlist, "fdefense"),
					ResultSet_getIntByName(resultItemlist, "fabsorb"),
					ResultSet_getIntByName(resultItemlist, "fevasion"),
					ResultSet_getIntByName(resultItemlist, "fhit"),
					ResultSet_getIntByName(resultItemlist, "fhp"),
					ResultSet_getIntByName(resultItemlist, "fmp"),
					ResultSet_getIntByName(resultItemlist, "fstr"),
					ResultSet_getIntByName(resultItemlist, "fhth"),
					ResultSet_getIntByName(resultItemlist, "fint"),
					ResultSet_getIntByName(resultItemlist, "fwis"),
					ResultSet_getIntByName(resultItemlist, "fdex"),
					ResultSet_getIntByName(resultItemlist, "shot"),
					ResultSet_getIntByName(resultItemlist, "perforation"),
					ResultSet_getIntByName(resultItemlist, "gongleft"),
					ResultSet_getIntByName(resultItemlist, "gongright"));
			}

			CMainSocket::Write(D2S_LOADPLAYER, "m", pBegin, p - pBegin);

			pAccount->m_Access.Release();
			break;
		}
		
		case S2D_SELECT_CHARACTER:
		{
			printf("S2D_SELECT_CHARACTER.\n");

			int nClientID=0;

			char *p = CSocket::ReadPacket(packet.data, "d", &nClientID);
			CAccount *pAccount = CServer::FindAccount(nClientID);
			if (pAccount) {
				pAccount->SendPlayerInfo(con);
				pAccount->m_Access.Release();
			}

			break;
		}


		case S2D_UPDATEPROPERTY:
		{
			printf("S2D_UPDATEPROPERTY.\n");

			int nPID=0;
			WORD wStats[5]={0,};
			WORD wPUPoint=0;

			CSocket::ReadPacket(packet.data, "dwwwwww", &nPID, &wStats[P_STR], &wStats[P_HTH], &wStats[P_INT], &wStats[P_WIS], &wStats[P_DEX], &wPUPoint);

			PreparedStatement_T p = Connection_prepareStatement(con,
				"UPDATE player SET strength=?, health=?, inteligence=?, wisdom=?, dexterity=?, pupoint=? WHERE idplayer=?");

			PreparedStatement_setInt(p, 1, wStats[P_STR]);
			PreparedStatement_setInt(p, 2, wStats[P_HTH]);
			PreparedStatement_setInt(p, 3, wStats[P_INT]);
			PreparedStatement_setInt(p, 4, wStats[P_WIS]);
			PreparedStatement_setInt(p, 5, wStats[P_DEX]);
			PreparedStatement_setInt(p, 6, wPUPoint);
			PreparedStatement_setInt(p, 7, nPID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_MAX_IID:
		{
			printf("S2D_MAX_IID.\n");

			ResultSet_T r = Connection_executeQuery(con, 
				"SELECT COALESCE(MAX(iditem), -2147483648) AS max_id FROM item");

			ResultSet_next(r);

			int nMaxIID = ResultSet_getInt(r, 1);
			
			CMainSocket::Write(D2S_MAX_IID, "d", nMaxIID);

			break;
		}

		case S2D_INSERTITEM:
		{
			printf("S2D_INSERTITEM.\n");

			int nPID=0;
			int unkn;
			WORD wIndex=0;
			int nIID=0;
			BYTE byPrefix=0;
			int nInfo=0, nNum=0;
			BYTE byMaxEnd=0, byCurEnd=0;
			BYTE byXAttack=0, byXMagic=0, byXDefense=0, byXHit=0, byXDodge=0, byExplosiveBlow=0;
			BYTE byFLevel=0;
			WORD wFMeele=0, wFMagic=0, wFDefense=0, wFAbsorb=0;
			BYTE byFDodge=0, byFHit=0, byFHP=0, byFMP=0;
			BYTE byFStats[5] = {0,};
			BYTE byShot=0;
			WORD wPerforation=0;
			int nGongLeft=0, nGongRight=0;

			CSocket::ReadPacket(packet.data, "dwdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbwdd", &nPID,
				&wIndex,
				&nIID,
				&byPrefix,
				&nInfo,
				&nNum,
				&byMaxEnd,
				&byCurEnd,
				&unkn,
				&byXAttack,
				&byXMagic,
				&byXDefense,
				&byXHit,
				&byXDodge,
				&unkn,
				&byExplosiveBlow,
				&unkn, &unkn, &unkn, &unkn, &unkn,
				&byFLevel,
				&wFMeele,
				&wFMagic,
				&wFDefense,
				&wFAbsorb,
				&byFDodge,
				&byFHit,
				&byFHP,
				&byFMP,
				&byFStats[P_STR],
				&byFStats[P_HTH],
				&byFStats[P_INT],
				&byFStats[P_WIS],
				&byFStats[P_DEX],
				&byShot,
				&wPerforation,
				&nGongLeft,
				&nGongRight);

			PreparedStatement_T p = Connection_prepareStatement(con,
				"INSERT INTO item (idplayer, `index`, prefix, info, num, maxend, curend, xattack, xmagic, xdefense, xhit, xdodge, explosiveblow, "
				"fusion, fmeele, fmagic, fdefense, fabsorb, fevasion, fhit, fhp, fmp, fstr, fhth, fint, fwis, fdex, shot, perforation, gongleft, gongright, iditem) "
				"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

			PreparedStatement_setInt(p, 1, nPID);
			PreparedStatement_setInt(p, 2, wIndex);
			PreparedStatement_setInt(p, 3, byPrefix);
			PreparedStatement_setInt(p, 4, nInfo);
			PreparedStatement_setInt(p, 5, nNum);
			PreparedStatement_setInt(p, 6, byMaxEnd);
			PreparedStatement_setInt(p, 7, byCurEnd);
			PreparedStatement_setInt(p, 8, byXAttack);
			PreparedStatement_setInt(p, 9, byXMagic);
			PreparedStatement_setInt(p, 10, byXDefense);
			PreparedStatement_setInt(p, 11, byXHit);
			PreparedStatement_setInt(p, 12, byXDodge);
			PreparedStatement_setInt(p, 13, byExplosiveBlow);
			PreparedStatement_setInt(p, 14, byFLevel);
			PreparedStatement_setInt(p, 15, wFMeele);
			PreparedStatement_setInt(p, 16, wFMagic);
			PreparedStatement_setInt(p, 17, wFDefense);
			PreparedStatement_setInt(p, 18, wFAbsorb);
			PreparedStatement_setInt(p, 19, byFDodge);
			PreparedStatement_setInt(p, 20, byFHit);
			PreparedStatement_setInt(p, 21, byFHP);
			PreparedStatement_setInt(p, 22, byFMP);
			PreparedStatement_setInt(p, 23, byFStats[P_STR]);
			PreparedStatement_setInt(p, 24, byFStats[P_HTH]);
			PreparedStatement_setInt(p, 25, byFStats[P_INT]);
			PreparedStatement_setInt(p, 26, byFStats[P_WIS]);
			PreparedStatement_setInt(p, 27, byFStats[P_DEX]);
			PreparedStatement_setInt(p, 28, byShot);
			PreparedStatement_setInt(p, 29, wPerforation);
			PreparedStatement_setInt(p, 30, nGongLeft);
			PreparedStatement_setInt(p, 31, nGongRight);
			PreparedStatement_setInt(p, 32, nIID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_UPDATEITEMNUM:
		{
			printf("S2D_UPDATEITEMNUM.\n");
			int nIID=0, nNum=0;
			BYTE byLogType=0;

			CSocket::ReadPacket(packet.data, "ddb", &nIID, &nNum, &byLogType);

			PreparedStatement_T p = Connection_prepareStatement(con,
				"UPDATE item SET num=? WHERE iditem=?");

			PreparedStatement_setInt(p, 1, nNum);
			PreparedStatement_setInt(p, 2, nIID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_SAVEALLPROPERTY:
		{
			printf("S2D_SAVEALLPROPERTY.\n");

			int nPID=0;
			BYTE byLevel=0;
			int nX=0, nY=0, nZ=0;
			WORD wContribute=0;
			DWORD nCurHP=0;
			WORD wCurMP=0;
			__int64 n64Exp=0;
			WORD wPUPoint=0, wSUPoint=0;
			int nAnger=0;

			CSocket::ReadPacket(packet.data, "dbdddwdwIwwd", &nPID, &byLevel, &nX, &nY, &nZ, &wContribute, &nCurHP, &wCurMP, &n64Exp, &wPUPoint, &wSUPoint, &nAnger);

			PreparedStatement_T p = Connection_prepareStatement(con, 
				"UPDATE player SET level=?, x=?, y=?, z=?, contribute=?, curhp=?, curmp=?, exp=?, pupoint=?, supoint=?, anger=? WHERE idplayer=?");

			PreparedStatement_setInt(p, 1, byLevel);
			PreparedStatement_setInt(p, 2, nX);
			PreparedStatement_setInt(p, 3, nY);
			PreparedStatement_setInt(p, 4, nZ);
			PreparedStatement_setInt(p, 5, wContribute);
			PreparedStatement_setInt(p, 6, nCurHP);
			PreparedStatement_setInt(p, 7, wCurMP);
			PreparedStatement_setInt(p, 8, n64Exp);
			PreparedStatement_setInt(p, 9, wPUPoint);
			PreparedStatement_setInt(p, 10, wSUPoint);
			PreparedStatement_setInt(p, 11, nAnger);
			PreparedStatement_setInt(p, 12, nPID);

			PreparedStatement_execute(p);

			printf("S2D_SAVEALLPROPERTY finished.\n");

			break;
		}

		case S2D_REMOVEITEM:
		{
			printf("S2D_REMOVEITEM.\n");

			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			PreparedStatement_T p = Connection_prepareStatement(con, 
				"DELETE FROM item WHERE iditem=?");

			PreparedStatement_setInt(p, 1, nIID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_PUTONITEM:
		{
			printf("S2D_PUTONITEM.\n");

			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			PreparedStatement_T p = Connection_prepareStatement(con, 
				"UPDATE item SET info = info | 1 WHERE iditem=?");

			PreparedStatement_setInt(p, 1, nIID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_PUTOFFITEM:
		{
			printf("S2C_PUTOFFITEM.\n");

			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			PreparedStatement_T p = Connection_prepareStatement(con, 
				"UPDATE item SET info = info & ~1 WHERE iditem=?");

			PreparedStatement_setInt(p, 1, nIID);

			PreparedStatement_execute(p);

			break;
		}

		case S2D_SHORTCUT:
		{
			printf("S2C_SHORTCUT.\n");

			BYTE byType=0;
			int nCID=0;
			int nPID=0;
			char *p = CSocket::ReadPacket(packet.data, "ddb", &nCID, &nPID, &byType);

			if (byType == 0) 
			{
				PreparedStatement_T ps = Connection_prepareStatement(con,
					"SELECT value FROM shortcut WHERE idplayer=? ORDER BY idslot ASC");

				PreparedStatement_setInt(ps, 1, nPID);

				ResultSet_T r = PreparedStatement_executeQuery(ps);

				PACKETBUFFER buffer;
				memset(&buffer, 0, sizeof(PACKETBUFFER));

				char *pBegin = (char*)&buffer;
				char *pEnd = pBegin;

				while (ResultSet_next(r))
				{
					pEnd = CSocket::WritePacket(pEnd, "w", ResultSet_getInt(r, 1));
				}

				CMainSocket::Write(D2S_SHORTCUT, "dm", nCID, pBegin, pEnd - pBegin);

				printf("S2C_SHORTCUT sent.\n");
			}
			else
			{
				PreparedStatement_T ps = Connection_prepareStatement(con,
					"UPDATE shortcut SET value=? WHERE idplayer=? AND idslot=?");

				for (int i = 1; i <= 20; i++)
				{
					WORD wValue=0;
					p = CSocket::ReadPacket(p, "w", &wValue);

					PreparedStatement_setInt(ps, 1, wValue);
					PreparedStatement_setInt(ps, 2, nPID);
					PreparedStatement_setInt(ps, 3, i);
					PreparedStatement_execute(ps);
				}
			}

			break;
		}
	}

	//delete packet;

	Connection_close(con);

	CDatabase::Unlock();

	//pthread_detach(pthread_self());

	//return NULL;
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

void CMainSocket::DebugRawPacket(Packet& packet)
{
	printf("Incoming S2D packet: [%u]\n", (BYTE)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%u ", (BYTE)((char*)&packet)[i]);
	printf("\n");
}

