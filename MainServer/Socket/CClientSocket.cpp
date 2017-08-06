#include "CClientSocket.h"
#include "CDBSocket.h"
#include "../Macro/CMacroDB.h"
#include "../Map/CMap.h"
#include "../GameCharacter/CNPC.h"

SOCKET CClientSocket::g_pSocket = INVALID_SOCKET;

bool CClientSocket::Start(WORD wPort)
{
	CClientSocket::g_pSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CClientSocket::g_pSocket <= INVALID_SOCKET) {
		printf(KRED "Error creating socket.\n" KNRM);
		return false;
	}

	int nYes=1;
	if (setsockopt(CClientSocket::g_pSocket, SOL_SOCKET, SO_REUSEADDR, &nYes, sizeof(nYes)) == SOCKET_ERROR) {
		printf(KRED "SetSockOpt error.\n" KNRM);
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

    if (listen(CClientSocket::g_pSocket, 5) <= SOCKET_ERROR) {	// TODO: 5? maybe more?
    	printf(KRED "Error listening on socket.\n" KNRM);		// TODO: close socket before app exit
    	return false;
    }

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = CClientSocket::Close;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
 
	return true;
}

bool CClientSocket::Start_Poll(WORD wPort)
{
	CClientSocket::g_pSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CClientSocket::g_pSocket <= INVALID_SOCKET) {
		printf(KRED "Error creating socket.\n" KNRM);
		return false;
	}

	int nYes = 1;
	if (setsockopt(CClientSocket::g_pSocket, SOL_SOCKET, SO_REUSEADDR, &nYes, sizeof(nYes)) == SOCKET_ERROR) {
		printf(KRED "SetSockOpt error.\n" KNRM);
		return false;
	}

	int nOn = 1;
	if (ioctl(CClientSocket::g_pSocket, FIONBIO, (char *)&nOn) <= SOCKET_ERROR) {
		printf(KRED "ioctl error.\n" KNRM);
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

	if (listen(CClientSocket::g_pSocket, 32) <= SOCKET_ERROR) {	// TODO: 5? maybe more?
		printf(KRED "Error listening on socket.\n" KNRM);		// TODO: close socket before app exit
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
	printf("\nAbout to send all player property...\n");
	CServer::g_mxClient.lock();

	for (auto& a: CServer::g_mClient)
	{
		CClient *pClient = a.second;
		pClient->m_Access.Grant();

		if (pClient->GetPlayer()) {
			CPlayer *pPlayer = pClient->GetPlayer();
			pPlayer->m_Access.Grant();

			pPlayer->SaveAllProperty();

			pPlayer->m_Access.Release();
		}

		pClient->m_Access.Release();
	}

	CServer::g_mxClient.unlock();
	printf("Property sent.\n");
	
	CServer::EmptyClient();

	close(CClientSocket::g_pSocket);

	CMonster::DestroyAll();

	CMacroDB::Destroy();
	CMap::UnloadMaps();
	CNPC::UnloadNPC();

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

		if (pthread_create(&t, NULL, &CClientSocket::Await, (PVOID)client) != THREAD_SUCCESS) 
		{
			printf(KRED "ERROR: Couldn't start thread.\n" KNRM);
			delete client;
		}
	}
}

void CClientSocket::Accept_Poll()
{
	// Initialize pollfd structure
	struct pollfd fds[200]; // 200 concurrent connections?
	memset(fds, 0, sizeof(fds));

	// Set up the initial listening socket
	fds[0].fd = CClientSocket::g_pSocket;
	fds[0].events = POLLIN;

	bool end_server = false;
	bool close_conn = false;
	bool compress_array = false;
	Packet buffer;
	nfds_t current_size, nfds = 1;
	// Loop waiting for incoming connections or for incoming packets
	do
	{
		printf("Waiting on poll()...\n");

		if (poll(fds, nfds, POLL_FOREVER) <= 0) {
			printf(KRED "poll() error.\n" KNRM);
			break;
		}

		current_size = nfds;
		// One or more descriptors are readable, need to determine which ones.
		for (nfds_t i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;

			if (fds[i].revents != POLLIN) {
				printf(KRED "Error: revents = %d\n" KNRM, fds[i].revents);
				end_server = true;
				break;
			}

			// Main descriptior is readable, new connection incoming
			if (fds[i].fd == CClientSocket::g_pSocket)
			{
				int new_sd = -1;
				// Accept new connections
				do
				{
					new_sd = accept(CClientSocket::g_pSocket, NULL, NULL);
					if (new_sd < 0) {
						if (errno != EWOULDBLOCK) {
							printf(KRED "accept() failed.\n" KNRM);
							end_server = true;
						}
						break;
					}

					printf("New connection: %d\n", new_sd);

					int nOn = 1;
					if (ioctl(new_sd, FIONBIO, (char *)&nOn) <= SOCKET_ERROR) {
						printf(KRED "Error making non-blocking file descriptor for %d.\n" KNRM, new_sd);
						close(new_sd);
						break;
					}

					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++; // Limit?

					CClient *pClient = new CClient(new_sd);
					CServer::Add(pClient);

				} while (new_sd != -1);
			}

			// Existing connection is readable, new packet icoming
			else
			{
				close_conn = false;

				auto pClient = CServer::FindClient(fds[i].fd);

				do
				{
					ssize_t nread = recv(fds[i].fd, &buffer, sizeof(buffer), 0);

					// Receive data until recv failed with EWOULDBLOCK
					if (nread < 0) {
						if (errno != EWOULDBLOCK) {
							printf(KRED "recv() failed for %d.\n" KNRM, fds[i].fd);
							close_conn = true;
						}
						break;
					}
					// Connection closed by client?
					else if (nread == 0) {
						printf("Connection closed by %d.\n", fds[i].fd);
						close_conn = true;

						CDBSocket::Write(S2D_DISCONNECT, "d", pClient->GetCID());
						CServer::Remove(pClient);

						break;
					}

					printf("%ld bytes received from %d (planned %d).\n", nread, fds[i].fd, buffer.wSize);

					DebugRawPacket(buffer);
					pClient->Process(buffer);

				} while (true);

				pClient->m_Access.Release();

				if (close_conn) {
					close(fds[i].fd);
					fds[i].fd = -1;
					compress_array = true;
				}
			}
		}

		if (compress_array)
		{
			compress_array = true;
			for (nfds_t i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for (nfds_t j = i; j < nfds; j++)
						fds[j].fd = fds[j + 1].fd;

					nfds--;
				}
			}
		}

	} while (!end_server);

	for (nfds_t i = 0; i < nfds; i++)
	{
		if (fds[i].fd >= 0)
			close(fds[i].fd);
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
		PACKETBUFFER buffer;
		memset(&buffer, 0, sizeof(PACKETBUFFER));

		int nLen = recv(pClient->GetCID(), &buffer, sizeof(PACKETBUFFER), 0);
		if (nLen <= 0) {
			printf("Client[%d] disconnected.\n", pClient->GetCID());
			int nClientDescriptor = pClient->GetCID();

			CDBSocket::Write(S2D_DISCONNECT, "d", pClient->GetCID());
			CServer::Remove(pClient);
			
			close(nClientDescriptor);
			break;
		}

		if (nLen > MAX_PACKET_LENGTH) continue;

		// Cut buffer into packets
		char *p = (char*)&buffer;
		while (nLen > 0 && nLen >= *(WORD*)p) 
		{
			Packet packet;
			memset(&packet, 0, sizeof(Packet));
			memcpy(&packet, p, *(WORD*)p);

			DebugRawPacket(packet);
			pClient->Process(packet);

			nLen -= *(WORD*)p;
			p += *(WORD*)p;
		}
	}

	pthread_detach(pthread_self());

	return NULL;
}

void CClientSocket::DebugRawPacket(Packet& packet)
{
	if (packet.byType == C2S_MOVE_ON)
		return;
	if (packet.byType == C2S_MOVE_END)
		return;

	printf("Incoming C2S packet: [%u]\n", (BYTE)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%u ", (BYTE)((char*)&packet)[i]);
	printf("\n");
}
