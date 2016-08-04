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

class CMainSocket
{
	static SOCKET g_pDBSocket;
	static SOCKET g_pMainSocket;

public:
	static bool Start(WORD wPort);
	static bool Close();
	static void Accept();
	static PVOID Process(PVOID packet);

	static bool Write(BYTE byType, ...);

	static void DebugRawPacket(Packet *packet);
};
