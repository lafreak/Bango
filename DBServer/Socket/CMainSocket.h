#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory>
#include <signal.h>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>
#include <minwindef.h>
#include <common.h>

#include <Socket/CSocket.h>

#include "../CServer.h"

class CMainSocket
{
	static SOCKET g_pDBSocket;
	static SOCKET g_pMainSocket;

public:
	static bool Start(WORD wPort);
	static void Close(int);
	static void Accept();
	static PVOID Process(PVOID packet);
	static void Process(Packet& packet);

	static bool Write(BYTE byType, ...);
	static bool WritePacket(Packet packet);

	static void DebugRawPacket(Packet& packet);
};
