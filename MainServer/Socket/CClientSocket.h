#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>
#include <minwindef.h>

#include <Socket/CSocket.h>

#include "../CServer.h"

class CClientSocket
{
	static SOCKET g_pSocket;

public:
	static bool Start(WORD wPort);
	static bool Close();
	static void Accept();
	static PVOID Await(PVOID client);
	static void Process(CClient *pClient, Packet packet);

	static bool Write(SOCKET client, BYTE byType, ...);

	static void DebugRawPacket(Packet packet);
};
