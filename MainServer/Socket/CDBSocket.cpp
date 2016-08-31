#include "CDBSocket.h"
#include "../CServer.h"
#include "../Item/CItem.h"

SOCKET CDBSocket::g_pDBSocket = INVALID_SOCKET;

bool CDBSocket::Connect(WORD wPort)
{
	CDBSocket::g_pDBSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CDBSocket::g_pDBSocket <= INVALID_SOCKET) {
		printf(KRED "Error creating socket.\n" KNRM);
		return false;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(wPort);

    if (connect(CDBSocket::g_pDBSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= SOCKET_ERROR) {
    	printf(KRED "Failed to connect to DB Server.\n" KNRM);
    	return false;
    }
    
	printf("Connected to DBServer.\n");

	pthread_t t;
	pthread_create(&t, NULL, &CDBSocket::Await, NULL);

	CDBSocket::Write(S2D_MAX_IID, "");

	return true;
}

bool CDBSocket::Close()
{
	return true;
}

PVOID CDBSocket::Await(PVOID param)
{
	while (true)
	{
		PACKETBUFFER buffer;
		memset(&buffer, 0, sizeof(PACKETBUFFER));

		int nLen = recv(CDBSocket::g_pDBSocket, &buffer, sizeof(PACKETBUFFER), 0);
		if (nLen <= 0) {
			printf(KRED "DBServer disconnected.\n" KNRM);
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

			//DebugRawPacket(packet);

			pthread_t t;
			if (pthread_create(&t, NULL, &CDBSocket::Process, (PVOID)packet) != THREAD_SUCCESS) {
				printf(KRED "ERROR: Couldn't start thread.\n" KNRM);
				delete packet;
			}
			*/

			Packet packet;
			memset(&packet, 0, sizeof(Packet));
			memcpy(&packet, p, *(WORD*)p);

			//DebugRawPacket(packet);

			Process(packet);

			nLen -= *(WORD*)p;
			p += *(WORD*)p;
		}
	}
}

//PVOID CDBSocket::Process(PVOID param)
void CDBSocket::Process(Packet& packet)
{
	//Packet* packet = (Packet*)param;

	switch (packet.byType)
	{
		case D2S_LOGIN:
		{
			BYTE byAnswer=0;
			int nClientID=0;
			char *p = CSocket::ReadPacket(packet.data, "d", &nClientID);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) 
				break;

			pClient->OnLogin(p);
			pClient->m_Access.Release();
			break;
		}

		case D2S_SEC_LOGIN:
		{
			int nClientID=0;
			BYTE byAnswer=0;
			CSocket::ReadPacket(packet.data, "db", &nClientID, &byAnswer);

			CClient *pClient = CServer::FindClient(nClientID);
			if (pClient) {
				pClient->Write(S2C_SECOND_LOGIN, "bb", SL_RESULT_MSG, byAnswer);
				pClient->m_Access.Release();
			}

			break;
		}

		case D2S_PLAYER_INFO:
		{
			int nClientID=0;
			char *p = CSocket::ReadPacket(packet.data, "d", &nClientID);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) 
				break;

			BYTE byAuth=0;
			int nExpTime=0;
			BYTE byUnknwon=0;

			pClient->Write(S2C_PLAYERINFO, "bbdm", byAuth, byUnknwon, nExpTime, 
				p, ((char*)&packet + packet.wSize) - p);
			//printf("S2C_PLAYERINFO sent.\n");

			pClient->m_Access.Release();

			break;
		}

		case D2S_ANS_NEWPLAYER:
		{
			int nClientID=0;
			char *p = CSocket::ReadPacket(packet.data, "d", &nClientID);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) 
				break;

			pClient->Write(S2C_ANS_NEWPLAYER, "m", p, ((char*)&packet + packet.wSize) - p);

			pClient->m_Access.Release();
			break;
		}

		case D2S_LOADPLAYER:
		{
			int nClientID=0;
			BYTE byMessage=0;
			char* p= CSocket::ReadPacket(packet.data, "db", &nClientID, &byMessage);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) 
				break;

			if (byMessage == 1) {
				pClient->Write(S2C_MESSAGE, "b", MSG_NOTEXISTPLAYER);
				pClient->m_Access.Release();
				break;
			}

			p = pClient->OnLoadPlayer(p);
			pClient->OnLoadItems(p);

			pClient->m_Access.Release();
			break;
		}

/*
		case D2S_LOADITEMS:
		{

			int nClientID=0;

			char* p = CSocket::ReadPacket(packet.data, "d", &nClientID);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) break;

			//printf("Packet LOADITEMS received, size: %d\n", packet.wSize);
			pClient->OnLoadItems(p);

			pClient->m_Access.Release();

			break;
		}
*/

		case D2S_MAX_IID:
		{
			CSocket::ReadPacket(packet.data, "d", &CItem::g_nMaxIID);
			break;
		}

		case D2S_SHORTCUT:
		{
			int nClientID=0;
			char* p= CSocket::ReadPacket(packet.data, "d", &nClientID);

			CClient *pClient = CServer::FindClient(nClientID);
			if (!pClient) 
				break;

			pClient->Write(S2C_SHORTCUT, "bm", 1, p, packet.wSize - (p - (char*)&packet));

			pClient->m_Access.Release();
			break;
		}
	}

	//delete packet;

	//pthread_detach(pthread_self());

	//return NULL;
}

bool CDBSocket::Write(BYTE byType, ...)
{
	if (CDBSocket::g_pDBSocket == INVALID_SOCKET)
		return false;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	send(CDBSocket::g_pDBSocket, (char*)&packet, packet.wSize, 0);

	return true;
}

void CDBSocket::DebugRawPacket(Packet& packet)
{
	printf("Incoming D2S packet: [%u]\n", (BYTE)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%u ", (BYTE)((char*)&packet)[i]);
	printf("\n");
}

