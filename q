[1mdiff --git a/MainServer/CClient.cpp b/MainServer/CClient.cpp[m
[1mindex 4a59a35..077d285 100644[m
[1m--- a/MainServer/CClient.cpp[m
[1m+++ b/MainServer/CClient.cpp[m
[36m@@ -1,344 +1,344 @@[m
[31m-#include "CClient.h"[m
[31m-#include "CServer.h"[m
[31m-[m
[31m-[m
[31m-CClient::~CClient()[m
[31m-{[m
[31m-	if (m_pPlayer) {[m
[31m-		delete m_pPlayer;[m
[31m-	}[m
[31m-[m
[31m-	while (m_Access.IsBusy()) {[m
[31m-		printf("CClient::~CClient: Client is in use, can't delete! Retrying in 10ms...\n");[m
[31m-		usleep(10000);[m
[31m-	}[m
[31m-}[m
[31m-[m
[31m-bool CClient::Write(BYTE byType, ...)[m
[31m-{[m
[31m-	if (m_nCID == INVALID_SOCKET)[m
[31m-		return false;[m
[31m-[m
[31m-	Packet packet;[m
[31m-	memset(&packet, 0, sizeof(Packet));[m
[31m-[m
[31m-	packet.byType = byType;[m
[31m-[m
[31m-	va_list va;[m
[31m-	va_start(va, byType);[m
[31m-[m
[31m-	char* end = CSocket::WriteV(packet.data, va);[m
[31m-[m
[31m-	va_end(va);[m
[31m-[m
[31m-	packet.wSize = end - (char*)&packet;[m
[31m-	send(m_nCID, (char*)&packet, packet.wSize, MSG_NOSIGNAL);[m
[31m-[m
[31m-	return true;[m
[31m-}[m
[31m-[m
[31m-void CClient::Process(Packet packet)[m
[31m-{[m
[31m-	if (packet.byType >= C2S_START) [m
[31m-	{[m
[31m-		if (m_pPlayer) {[m
[31m-			m_pPlayer->m_Access.Grant();[m
[31m-			m_pPlayer->Process(packet);[m
[31m-[m
[31m-			// Double check in case player was deleted in CPlayer::Process.[m
[31m-			if(m_pPlayer)[m
[31m-				m_pPlayer->m_Access.Release();[m
[31m-		}[m
[31m-		else[m
[31m-			printf(KRED "CClient::Process: ERROR: Packet manipulation - player packet sent on not logged account.\n" KNRM);[m
[31m-[m
[31m-		return;[m
[31m-	}[m
[31m-[m
[31m-	if (m_pPlayer) {[m
[31m-		printf(KRED "CClient::Process: ERROR: Packet manipulation - client packet sent on logged account.\n" KNRM);[m
[31m-		return;[m
[31m-	}[m
[31m-[m
[31m-	switch (packet.byType)[m
[31m-	{[m
[31m-		case C2S_CONNECT:[m
[31m-		{[m
[31m-			DWORD dwSeedL[4] = {0,};[m
[31m-			int nAppTime=0;[m
[31m-			BYTE byUnknown=0;[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "dddddb", &nAppTime, &dwSeedL[0], &dwSeedL[1], &dwSeedL[2], &dwSeedL[3], &byUnknown);[m
[31m-			//printf("nAppTime: %i\ndwSeedL: %u %u %u %u\nbyUnknown: %u\n", nAppTime, dwSeedL[0], dwSeedL[1], dwSeedL[2], dwSeedL[3], byUnknown);[m
[31m-[m
[31m-			DWORD dwProtocolVersion=0;[m
[31m-			BYTE byCode=0;[m
[31m-			int nTimeStamp=604800;// 1 week ;//0;[m
[31m-			int nTimeStart=0;[m
[31m-			DWORD dwSystem=0;[m
[31m-			DWORD dwEvent=0;[m
[31m-			BYTE byServerID=0;[m
[31m-			BYTE byAge=0;[m
[31m-			BYTE byCountry=N_EN;[m
[31m-[m
[31m-			Write(S2C_CODE, "dbdddIbbb", dwProtocolVersion, byCode, nTimeStamp, nTimeStart, dwSystem, dwEvent, byServerID, byAge, byCountry);[m
[31m-			//printf("S2C_CODE sent.\n");[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_ANS_CODE:[m
[31m-		{[m
[31m-			BYTE byUnknown=0;[m
[31m-			DWORD dwProtocolVersion=0;[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "bd", &byUnknown, &dwProtocolVersion);[m
[31m-			//printf("byUnknown: %u\ndwProtocolVersion: %u\n", byUnknown, dwProtocolVersion);[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_LOGIN:[m
[31m-		{[m
[31m-			char* szLogin=NULL;[m
[31m-			char* szPassword=NULL;[m
[31m-			char* szMac=NULL;[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "sss", &szLogin, &szPassword, &szMac);[m
[31m-			//printf("Login: %s\nPassword: %s\nMac: %s\n", szLogin, szPassword, szMac);[m
[31m-[m
[31m-			CDBSocket::Write(S2D_LOGIN, "dss", m_nCID, szLogin, szPassword);[m
[31m-			//printf("S2D_LOGIN sent.\n");[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_SECOND_LOGIN:[m
[31m-		{[m
[31m-			BYTE byType=0;[m
[31m-[m
[31m-			char *p = CSocket::ReadPacket(packet.data, "b", &byType);[m
[31m-[m
[31m-			switch (byType)[m
[31m-			{[m
[31m-				case SL_CREATE_PASSWORD:[m
[31m-				{[m
[31m-					char *szPassword=NULL;[m
[31m-					char *szSecondaryPW=NULL;[m
[31m-					CSocket::ReadPacket(p, "ss", &szPassword, &szSecondaryPW);[m
[31m-[m
[31m-					if (strlen(szSecondaryPW) != 8) {[m
[31m-						Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-						break;[m
[31m-					}[m
[31m-[m
[31m-					bool bQuit=false;[m
[31m-					for (char i = 0; i < 8; i++) {[m
[31m-						if (szSecondaryPW[i] < '0' || szSecondaryPW[i] > '9') {[m
[31m-							Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-							bQuit=true; break;[m
[31m-						}[m
[31m-					}[m
[31m-[m
[31m-					if (bQuit) break;[m
[31m-[m
[31m-					printf("OnCreate PW: %s\nSecondary: %s\n", szPassword, szSecondaryPW);[m
[31m-[m
[31m-					CDBSocket::Write(S2D_CREATE_SECONDARY, "dss", m_nCID, szPassword, szSecondaryPW);[m
[31m-					break;[m
[31m-				}[m
[31m-[m
[31m-				case SL_CHANGE_PASSWORD:[m
[31m-				{[m
[31m-					char *szOldPassword=NULL;[m
[31m-					char *szNewPassword=NULL;[m
[31m-[m
[31m-					CSocket::ReadPacket(p, "ss", &szOldPassword, &szNewPassword);[m
[31m-[m
[31m-					if (strlen(szOldPassword) != 8 || strlen(szNewPassword) != 8) {[m
[31m-						Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-						break;[m
[31m-					}[m
[31m-[m
[31m-					bool bQuit=false;[m
[31m-					for (char i = 0; i < 8; i++) {[m
[31m-						if (szOldPassword[i] < '0' || szOldPassword[i] > '9' || szNewPassword[i] < '0' || szNewPassword[i] > '9') {[m
[31m-							Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-							bQuit=true; break;[m
[31m-						}[m
[31m-					}[m
[31m-[m
[31m-					if (bQuit) break;[m
[31m-[m
[31m-					printf("Old password: %s\nNew password: %s\n", szOldPassword, szNewPassword);[m
[31m-[m
[31m-					CDBSocket::Write(S2D_CHANGE_SECONDARY, "dss", m_nCID, szOldPassword, szNewPassword);[m
[31m-					break;[m
[31m-				}[m
[31m-[m
[31m-				case SL_LOGIN: // Login[m
[31m-				{[m
[31m-					char *szPassword=NULL;[m
[31m-					CSocket::ReadPacket(p, "s", &szPassword);[m
[31m-[m
[31m-					//printf("Secondary password: %s\n", szPassword);[m
[31m-[m
[31m-					if (strlen(szPassword) != 8) {[m
[31m-						Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-						break;[m
[31m-					}[m
[31m-[m
[31m-					bool bQuit=false;[m
[31m-					for (char i = 0; i < 8; i++) {[m
[31m-						if (szPassword[i] < '0' || szPassword[i] > '9') {[m
[31m-							Write(S2C_CLOSE, "b", CC_KICK);[m
[31m-							bQuit=true; break;[m
[31m-						}[m
[31m-					}[m
[31m-[m
[31m-					if (bQuit) break;[m
[31m-[m
[31m-					CDBSocket::Write(S2D_SECONDARY_LOGIN, "ds", m_nCID, szPassword);[m
[31m-[m
[31m-					break;[m
[31m-				}[m
[31m-			}[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_DELPLAYER:[m
[31m-		{[m
[31m-			int nPID=0;[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "d", &nPID);[m
[31m-[m
[31m-			CDBSocket::Write(S2D_DELPLAYER, "dd", m_nCID, nPID);[m
[31m-[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_NEWPLAYER:[m
[31m-		{[m
[31m-			char* szName=NULL;[m
[31m-			BYTE byJob=0;[m
[31m-			WORD wStats[5]={0,};[m
[31m-			BYTE byShape[2]={0,};[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "sbwwwwwbb", &szName, &byJob, &wStats[0], &wStats[1], &wStats[2], &wStats[3], &wStats[4], &byShape[0], &byShape[1]);[m
[31m-			[m
[31m-			if (std::string(szName).empty() || std::string(szName).length() > 14) {[m
[31m-				Write(S2C_ANS_NEWPLAYER, "b", NA_ERROR);[m
[31m-				break;[m
[31m-			}[m
[31m-[m
[31m-			if (byJob < 0 || byJob > CLASS_NUM) {[m
[31m-				Write(S2C_ANS_NEWPLAYER, "b", NA_WRONGCLASS);[m
[31m-				break;[m
[31m-			}[m
[31m-[m
[31m-			if (wStats[0] + wStats[1] + wStats[2] + wStats[3] + wStats[4] != 5) {[m
[31m-				Write(S2C_ANS_NEWPLAYER, "b", NA_WRONGPROPERTY);[m
[31m-				break;[m
[31m-			}[m
[31m-[m
[31m-			if (byShape[0] < 0 || byShape[1] < 0 || byShape[0] > 6 || byShape[1] > 6) {[m
[31m-				Write(S2C_ANS_NEWPLAYER, "b", NA_WRONGPROPERTY);[m
[31m-				break;[m
[31m-			}[m
[31m-[m
[31m-			CDBSocket::Write(S2D_NEWPLAYER, "dm", m_nCID, packet.data, packet.wSize - (packet.data - (char*)&packet));[m
[31m-			break;[m
[31m-		}[m
[31m-[m
[31m-		case C2S_LOADPLAYER:[m
[31m-		{[m
[31m-			int nPID=0;[m
[31m-			int nGID=0;[m
[31m-			int nShow_honorGrade=0;[m
[31m-[m
[31m-			CSocket::ReadPacket(packet.data, "ddd", &nPID, &nGID, &nShow_honorGrade);[m
[31m-			//printf("Load PID: %d, GID: %d, Show_honorGrade: %d\n", nPID, nGID, nShow_honorGrade);[m
[31m-			[m
[31m-			CDBSocket::Write(S2D_LOADPLAYER, "dd", m_nCID, nPID);[m
[31m-			break;[m
[31m-		}[m
[31m-	}[m
[31m-}[m
[31m-[m
[31m-void CClient::OnLogin(char *p)[m
[31m-{[m
[31m-	BYTE byAnswer=0;[m
[31m-[m
[31m-	p = CSocket::ReadPacket(p, "b", &byAnswer);[m
[31m-[m
[31m-	if (byAnswer == LA_SAMEUSER) {[m
[31m-		int nClientExID=0;[m
[31m-		CSocket::ReadPacket(p, "d", &nClientExID);[m
[31m-[m
[31m-		auto pClientEx = CServer::FindClient(nClientExID);[m
[31m-		if (pClientEx) {[m
[31m-			pClientEx->Write(S2C_CLOSE, "b", CC_SAMEUSER);[m
[31m-			pClientEx->m_Access.Release();[m
[31m-			::shutdown(nClientExID, SHUT_RDWR);[m
[31m-		}[m
[31m-		[m
[31m-	}[m
[31m-[m
[31m-	Write(S2C_ANS_LOGIN, "b", byAnswer);[m
[31m-[m
[31m-	//printf("S2C_ANS_LOGIN sent.\n");[m
[31m-}[m
[31m-[m
[31m-char* CClient::OnLoadPlayer(char *p)[m
[31m-{[m
[31m-	D2S_LOADPLAYER_DESC desc;[m
[31m-	memset(&desc, 0, sizeof(D2S_LOADPLAYER_DESC));[m
[31m-[m
[31m-	p = CSocket::ReadPacket(p, "ddsbbbwwwwwdwIwwwddddbb", [m
[31m-		&desc.nAID, [m
[31m-		&desc.nPID,[m
[31m-		&desc.szName,[m
[31m-		&desc.byClass,[m
[31m-		&desc.byJob,[m
[31m-		&desc.byLevel,[m
[31m-		&desc.wStats[P_STR], [m
[31m-		&desc.wStats[P_HTH],[m
[31m-		&desc.wStats[P_INT],[m
[31m-		&desc.wStats[P_WIS], [m
[31m-		&desc.wStats[P_DEX],[m
[31m-		&desc.nCurHP, [m
[31m-		&desc.wCurMP, [m
[31m-		&desc.n64Exp, [m
[31m-		&desc.wPUPoint, [m
[31m-		&desc.wSUPoint, [m
[31m-		&desc.wContribute, [m
[31m-		&desc.nAnger, [m
[31m-		&desc.nX, [m
[31m-		&desc.nY, [m
[31m-		&desc.nZ,[m
[31m-		&desc.byFace,[m
[31m-		&desc.byHair);[m
[31m-[m
[31m-	Lock();[m
[31m-[m
[31m-	m_pPlayer = new CPlayer(m_nCID, desc);[m
[31m-[m
[31m-	m_pPlayer->m_Access.Grant();[m
[31m-[m
[31m-	Unlock();[m
[31m-[m
[31m-	m_pPlayer->OnLoadPlayer();[m
[31m-[m
[31m-	m_pPlayer->m_Access.Release();[m
[31m-[m
[31m-	return p;[m
[31m-}[m
[31m-[m
[31m-void CClient::OnLoadItems(char *p)[m
[31m-{[m
[31m-	if (!m_pPlayer) {[m
[31m-		printf(KRED "Cannot load items (non existing player)\n." KNRM);[m
[31m-		return;[m
[31m-	}[m
[31m-[m
[31m-	m_pPlayer->m_Access.Grant();[m
[31m-	m_pPlayer->OnLoadItems(p);[m
[31m-	m_pPlayer->m_Access.Release();[m
[31m-}[m
\ No newline at end of file[m
[32m+[m[32m#include "CClient.h"[m
[32m+[m[32m#include "CServer.h"[m
[32m+[m
[32m+[m
[32m+[m[32mCClient::~CClient()[m
[32m+[m[32m{[m
[32m+[m	[32mif (m_pPlayer) {[m
[32m+[m		[32mdelete m_pPlayer;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mwhile (m_Access.IsBusy()) {[m
[32m+[m		[32mprintf("CClient::~CClient: Client is in use, can't delete! Retrying in 10ms...\n");[m
[32m+[m		[32musleep(10000);[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mbool CClient::Write(BYTE byType, ...)[m
[32m+[m[32m{[m
[32m+[m	[32mif (m_nCID == INVALID_SOCKET)[m
[32m+[m		[32mreturn false;[m
[32m+[m
[32m+[m	[32mPacket packet;[m
[32m+[m	[32mmemset(&packet, 0, sizeof(Packet));[m
[32m+[m
[32m+[m	[32mpacket.byType = byType;[m
[32m+[m
[32m+[m	[32mva_list va;[m
[32m+[m	[32mva_start(va, byType);[m
[32m+[m
[32m+[m	[32mchar* end = CSocket::WriteV(packet.data, va);[m
[32m+[m
[32m+[m	[32mva_end(va);[m
[32m+[m
[32m+[m	[32mpacket.wSize = end - (char*)&packet;[m
[32m+[m	[32msend(m_nCID, (char*)&packet, packet.wSize, MSG_NOSIGNAL);[m
[32m+[m
[32m+[m	[32mreturn true;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid CClient::Process(Packet packet)[m
[32m+[m[32m{[m
[32m+[m	[32mif (packet.byType >= C2S_START)[m[41m [m
[32m+[m	[32m{[m
[32m+[m		[32mif (m_pPlayer) {[m
[32m+[m			[32mm_pPlayer->m_Access.Grant();[m
[32m+[m			[32mm_pPlayer->Process(packet);[m
[32m+[m
[32m+[m			[32m// Double check in case player was deleted in CPlayer::Process.[m
[32m+[m			[32mif(m_pPlayer)[m
[32m+[m				[32mm_pPlayer->m_Access.Release();[m
[32m+[m		[32m}[m
[32m+[m		[32melse[m
[32m+[m			[32mprintf(KRED "CClient::Process: ERROR: Packet manipulation - player packet sent on not logged account.\n" KNRM);[m
[32m+[m
[32m+[m		[32mreturn;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mif (m_pPlayer) {[m
[32m+[m		[32mprintf(KRED "CClient::Process: ERROR: Packet manipulation - client packet sent on logged account.\n" KNRM);[m
[32m+[m		[32mreturn;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mswitch (packet.byType)[m
[32m+[m	[32m{[m
[32m+[m		[32mcase C2S_CONNECT:[m
[32m+[m		[32m{[m
[32m+[m			[32mDWORD dwSeedL[4] = {0,};[m
[32m+[m			[32mint nAppTime=0;[m
[32m+[m			[32mBYTE byUnknown=0;[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "dddddb", &nAppTime, &dwSeedL[0], &dwSeedL[1], &dwSeedL[2], &dwSeedL[3], &byUnknown);[m
[32m+[m			[32m//printf("nAppTime: %i\ndwSeedL: %u %u %u %u\nbyUnknown: %u\n", nAppTime, dwSeedL[0], dwSeedL[1], dwSeedL[2], dwSeedL[3], byUnknown);[m
[32m+[m
[32m+[m			[32mDWORD dwProtocolVersion=0;[m
[32m+[m			[32mBYTE byCode=0;[m
[32m+[m			[32mint nTimeStamp=604800;// 1 week ;//0;[m
[32m+[m			[32mint nTimeStart=0;[m
[32m+[m			[32mDWORD dwSystem=0;[m
[32m+[m			[32mDWORD dwEvent=0;[m
[32m+[m			[32mBYTE byServerID=0;[m
[32m+[m			[32mBYTE byAge=0;[m
[32m+[m			[32mBYTE byCountry=N_EN;[m
[32m+[m
[32m+[m			[32mWrite(S2C_CODE, "dbdddIbbb", dwProtocolVersion, byCode, nTimeStamp, nTimeStart, dwSystem, dwEvent, byServerID, byAge, byCountry);[m
[32m+[m			[32m//printf("S2C_CODE sent.\n");[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_ANS_CODE:[m
[32m+[m		[32m{[m
[32m+[m			[32mBYTE byUnknown=0;[m
[32m+[m			[32mDWORD dwProtocolVersion=0;[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "bd", &byUnknown, &dwProtocolVersion);[m
[32m+[m			[32m//printf("byUnknown: %u\ndwProtocolVersion: %u\n", byUnknown, dwProtocolVersion);[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_LOGIN:[m
[32m+[m		[32m{[m
[32m+[m			[32mchar* szLogin=NULL;[m
[32m+[m			[32mchar* szPassword=NULL;[m
[32m+[m			[32mchar* szMac=NULL;[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "sss", &szLogin, &szPassword, &szMac);[m
[32m+[m			[32m//printf("Login: %s\nPassword: %s\nMac: %s\n", szLogin, szPassword, szMac);[m
[32m+[m
[32m+[m			[32mCDBSocket::Write(S2D_LOGIN, "dss", m_nCID, szLogin, szPassword);[m
[32m+[m			[32m//printf("S2D_LOGIN sent.\n");[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_SECOND_LOGIN:[m
[32m+[m		[32m{[m
[32m+[m			[32mBYTE byType=0;[m
[32m+[m
[32m+[m			[32mchar *p = CSocket::ReadPacket(packet.data, "b", &byType);[m
[32m+[m
[32m+[m			[32mswitch (byType)[m
[32m+[m			[32m{[m
[32m+[m				[32mcase SL_CREATE_PASSWORD:[m
[32m+[m				[32m{[m
[32m+[m					[32mchar *szPassword=NULL;[m
[32m+[m					[32mchar *szSecondaryPW=NULL;[m
[32m+[m					[32mCSocket::ReadPacket(p, "ss", &szPassword, &szSecondaryPW);[m
[32m+[m
[32m+[m					[32mif (strlen(szSecondaryPW) != 8) {[m
[32m+[m						[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m						[32mbreak;[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mbool bQuit=false;[m
[32m+[m					[32mfor (char i = 0; i < 8; i++) {[m
[32m+[m						[32mif (szSecondaryPW[i] < '0' || szSecondaryPW[i] > '9') {[m
[32m+[m							[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m							[32mbQuit=true; break;[m
[32m+[m						[32m}[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mif (bQuit) break;[m
[32m+[m
[32m+[m					[32mprintf("OnCreate PW: %s\nSecondary: %s\n", szPassword, szSecondaryPW);[m
[32m+[m
[32m+[m					[32mCDBSocket::Write(S2D_CREATE_SECONDARY, "dss", m_nCID, szPassword, szSecondaryPW);[m
[32m+[m					[32mbreak;[m
[32m+[m				[32m}[m
[32m+[m
[32m+[m				[32mcase SL_CHANGE_PASSWORD:[m
[32m+[m				[32m{[m
[32m+[m					[32mchar *szOldPassword=NULL;[m
[32m+[m					[32mchar *szNewPassword=NULL;[m
[32m+[m
[32m+[m					[32mCSocket::ReadPacket(p, "ss", &szOldPassword, &szNewPassword);[m
[32m+[m
[32m+[m					[32mif (strlen(szOldPassword) != 8 || strlen(szNewPassword) != 8) {[m
[32m+[m						[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m						[32mbreak;[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mbool bQuit=false;[m
[32m+[m					[32mfor (char i = 0; i < 8; i++) {[m
[32m+[m						[32mif (szOldPassword[i] < '0' || szOldPassword[i] > '9' || szNewPassword[i] < '0' || szNewPassword[i] > '9') {[m
[32m+[m							[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m							[32mbQuit=true; break;[m
[32m+[m						[32m}[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mif (bQuit) break;[m
[32m+[m
[32m+[m					[32mprintf("Old password: %s\nNew password: %s\n", szOldPassword, szNewPassword);[m
[32m+[m
[32m+[m					[32mCDBSocket::Write(S2D_CHANGE_SECONDARY, "dss", m_nCID, szOldPassword, szNewPassword);[m
[32m+[m					[32mbreak;[m
[32m+[m				[32m}[m
[32m+[m
[32m+[m				[32mcase SL_LOGIN: // Login[m
[32m+[m				[32m{[m
[32m+[m					[32mchar *szPassword=NULL;[m
[32m+[m					[32mCSocket::ReadPacket(p, "s", &szPassword);[m
[32m+[m
[32m+[m					[32m//printf("Secondary password: %s\n", szPassword);[m
[32m+[m
[32m+[m					[32mif (strlen(szPassword) != 8) {[m
[32m+[m						[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m						[32mbreak;[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mbool bQuit=false;[m
[32m+[m					[32mfor (char i = 0; i < 8; i++) {[m
[32m+[m						[32mif (szPassword[i] < '0' || szPassword[i] > '9') {[m
[32m+[m							[32mWrite(S2C_CLOSE, "b", CC_KICK);[m
[32m+[m							[32mbQuit=true; break;[m
[32m+[m						[32m}[m
[32m+[m					[32m}[m
[32m+[m
[32m+[m					[32mif (bQuit) break;[m
[32m+[m
[32m+[m					[32mCDBSocket::Write(S2D_SECONDARY_LOGIN, "ds", m_nCID, szPassword);[m
[32m+[m
[32m+[m					[32mbreak;[m
[32m+[m				[32m}[m
[32m+[m			[32m}[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_DELPLAYER:[m
[32m+[m		[32m{[m
[32m+[m			[32mint nPID=0;[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "d", &nPID);[m
[32m+[m
[32m+[m			[32mCDBSocket::Write(S2D_DELPLAYER, "dd", m_nCID, nPID);[m
[32m+[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_NEWPLAYER:[m
[32m+[m		[32m{[m
[32m+[m			[32mchar* szName=NULL;[m
[32m+[m			[32mBYTE byJob=0;[m
[32m+[m			[32mWORD wStats[5]={0,};[m
[32m+[m			[32mBYTE byShape[2]={0,};[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "sbwwwwwbb", &szName, &byJob, &wStats[0], &wStats[1], &wStats[2], &wStats[3], &wStats[4], &byShape[0], &byShape[1]);[m
[32m+[m[41m			[m
[32m+[m			[32mif (std::string(szName).empty() || std::string(szName).length() > 14) {[m
[32m+[m				[32mWrite(S2C_ANS_NEWPLAYER, "b", NA_ERROR);[m
[32m+[m				[32mbreak;[m
[32m+[m			[32m}[m
[32m+[m
[32m+[m			[32mif (byJob < 0 || byJob > CLASS_NUM) {[m
[32m+[m				[32mWrite(S2C_ANS_NEWPLAYER, "b", NA_WRONGCLASS);[m
[32m+[m				[32mbreak;[m
[32m+[m			[32m}[m
[32m+[m
[32m+[m			[32mif (wStats[0] + wStats[1] + wStats[2] + wStats[3] + wStats[4] != 5) {[m
[32m+[m				[32mWrite(S2C_ANS_NEWPLAYER, "b", NA_WRONGPROPERTY);[m
[32m+[m				[32mbreak;[m
[32m+[m			[32m}[m
[32m+[m
[32m+[m			[32mif (byShape[0] < 0 || byShape[1] < 0 || byShape[0] > 6 || byShape[1] > 6) {[m
[32m+[m				[32mWrite(S2C_ANS_NEWPLAYER, "b", NA_WRONGPROPERTY);[m
[32m+[m				[32mbreak;[m
[32m+[m			[32m}[m
[32m+[m
[32m+[m			[32mCDBSocket::Write(S2D_NEWPLAYER, "dm", m_nCID, packet.data, packet.wSize - (packet.data - (char*)&packet));[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m
[32m+[m		[32mcase C2S_LOADPLAYER:[m
[32m+[m		[32m{[m
[32m+[m			[32mint nPID=0;[m
[32m+[m			[32mint nGID=0;[m
[32m+[m			[32mint nShow_honorGrade=0;[m
[32m+[m
[32m+[m			[32mCSocket::ReadPacket(packet.data, "ddd", &nPID, &nGID, &nShow_honorGrade);[m
[32m+[m			[32m//printf("Load PID: %d, GID: %d, Show_honorGrade: %d\n", nPID, nGID, nShow_honorGrade);[m
[32m+[m[41m			[m
[32m+[m			[32mCDBSocket::Write(S2D_LOADPLAYER, "dd", m_nCID, nPID);[m
[32m+[m			[32mbreak;[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid CClient::OnLogin(char *p)[m
[32m+[m[32m{[m
[32m+[m	[32mBYTE byAnswer=0;[m
[32m+[m
[32m+[m	[32mp = CSocket::ReadPacket(p, "b", &byAnswer);[m
[32m+[m
[32m+[m	[32mif (byAnswer == LA_SAMEUSER) {[m
[32m+[m		[32mint nClientExID=0;[m
[32m+[m		[32mCSocket::ReadPacket(p, "d", &nClientExID);[m
[32m+[m
[32m+[m		[32mauto pClientEx = CServer::FindClient(nClientExID);[m
[32m+[m		[32mif (pClientEx) {[m
[32m+[m			[32mpClientEx->Write(S2C_CLOSE, "b", CC_SAMEUSER);[m
[32m+[m			[32mpClientEx->m_Access.Release();[m
[32m+[m			[32m::shutdown(nClientExID, SHUT_RDWR);[m
[32m+[m		[32m}[m
[32m+[m[41m		[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mWrite(S2C_ANS_LOGIN, "b", byAnswer);[m
[32m+[m
[32m+[m	[32m//printf("S2C_ANS_LOGIN sent.\n");[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mchar* CClient::OnLoadPlayer(char *p)[m
[32m+[m[32m{[m
[32m+[m	[32mD2S_LOADPLAYER_DESC desc;[m
[32m+[m	[32mmemset(&desc, 0, sizeof(D2S_LOADPLAYER_DESC));[m
[32m+[m
[32m+[m	[32mp = CSocket::ReadPacket(p, "ddsbbbwwwwwdwIwwwddddbb",[m[41m [m
[32m+[m		[32m&desc.nAID,[m[41m [m
[32m+[m		[32m&desc.nPID,[m
[32m+[m		[32m&desc.szName,[m
[32m+[m		[32m&desc.byClass,[m
[32m+[m		[32m&desc.byJob,[m
[32m+[m		[32m&desc.byLevel,[m
[32m+[m		[32m&desc.wStats[P_STR],[m[41m [m
[32m+[m		[32m&desc.wStats[P_HTH],[m
[32m+[m		[32m&desc.wStats[P_INT],[m
[32m+[m		[32m&desc.wStats[P_WIS],[m[41m [m
[32m+[m		[32m&desc.wStats[P_DEX],[m
[32m+[m		[32m&desc.nCurHP,[m[41m [m
[32m+[m		[32m&desc.wCurMP,[m[41m [m
[32m+[m		[32m&desc.n64Exp,[m[41m [m
[32m+[m		[32m&desc.wPUPoint,[m[41m [m
[32m+[m		[32m&desc.wSUPoint,[m[41m [m
[32m+[m		[32m&desc.wContribute,[m[41m [m
[32m+[m		[32m&desc.nAnger,[m[41m [m
[32m+[m		[32m&desc.nX,[m[41m [m
[32m+[m		[32m&desc.nY,[m[41m [m
[32m+[m		[32m&desc.nZ,[m
[32m+[m		[32m&desc.byFace,[m
[32m+[m		[32m&desc.byHair);[m
[32m+[m
[32m+[m	[32mLock();[m
[32m+[m
[32m+[m	[32mm_pPlayer = new CPlayer(m_nCID, desc);[m
[32m+[m
[32m+[m	[32mm_pPlayer->m_Access.Grant();[m
[32m+[m
[32m+[m	[32mUnlock();[m
[32m+[m
[32m+[m	[32mm_pPlayer->OnLoadPlayer();[m
[32m+[m
[32m+[m	[32mm_pPlayer->m_Access.Release();[m
[32m+[m
[32m+[m	[32mreturn p;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid CClient::OnLoadItems(char *p)[m
[32m+[m[32m{[m
[32m+[m	[32mif (!m_pPlayer) {[m
[32m+[m		[32mprintf(KRED "Cannot load items (non existing player)\n." KNRM);[m
[32m+[m		[32mreturn;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mm_pPlayer->m_Access.Grant();[m
[32m+[m	[32mm_pPlayer->OnLoadItems(p);[m
[32m+[m	[32mm_pPlayer->m_Access.Release();[m
[32m+[m[32m}[m
