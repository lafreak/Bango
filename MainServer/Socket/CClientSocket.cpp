#include "CClientSocket.h"
#include "CDBSocket.h"

SOCKET CClientSocket::g_pSocket = INVALID_SOCKET;

bool CClientSocket::Start(WORD wPort)
{
	CClientSocket::g_pSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CClientSocket::g_pSocket <= INVALID_SOCKET) {
		printf(KRED "Error creating socket.\n" KNRM);
		return false;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(wPort);

    if (bind(CClientSocket::g_pSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= SOCKET_ERROR) {
    	printf(KRED "Bind failed.\n" KNRM);
    	return false;
    }

    if (listen(CClientSocket::g_pSocket, 5) <= SOCKET_ERROR) {
    	printf(KRED "Error listening on socket.\n" KNRM);
    	return false;
    }

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = CClientSocket::Close;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
 
	return true;
}

void CClientSocket::Close(int)
{
	close(CClientSocket::g_pSocket);
	exit(1);
}

void CClientSocket::Accept()
{
	if (CClientSocket::g_pSocket == INVALID_SOCKET)
		return;

	while (true) {
		SOCKET *client = new SOCKET;
		*client = INVALID_SOCKET;

		while (*client == INVALID_SOCKET)
			*client = accept(CClientSocket::g_pSocket, NULL, NULL);

		pthread_t t;

		if (pthread_create(&t, NULL, &CClientSocket::Await, (PVOID)client) != THREAD_SUCCESS) {
			printf(KRED "ERROR: Couldn't start thread.\n" KNRM);
			delete client;
		}
	}
}

PVOID CClientSocket::Await(PVOID param)
{
	CClient *pClient = new CClient(*(SOCKET*)param);
	delete (SOCKET*)param;

	printf("Client[%d] connected.\n", pClient->GetCID());

	CServer::Add(pClient);

	while (true)
	{
		Packet packet;
		memset(&packet, 0, sizeof(Packet));
		//Sleep?

		int nLen = recv(pClient->GetCID(), &packet, MAX_PACKET_LENGTH + (packet.data-(char*)&packet), 0);
		if (nLen <= 0 || packet.wSize <=0) {
			printf("Client[%d] disconnected.\n", pClient->GetCID());
			CDBSocket::Write(S2D_DISCONNECT, "d", pClient->GetCID());
			CServer::Remove(pClient);
			break;
		}

		if (nLen > MAX_PACKET_LENGTH || packet.wSize > MAX_PACKET_LENGTH) continue;

		DebugRawPacket(packet);

		pClient->Process(packet);
	}

	return NULL;
}

void CClientSocket::DebugRawPacket(Packet packet)
{
	printf("Incoming C2S packet: [%u]\n", (BYTE)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%u ", (BYTE)((char*)&packet)[i]);
	printf("\n");
}
