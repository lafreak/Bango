#ifndef _CCLIENTSOCKET_
#define _CCLIENTSOCKET_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>
#include <minwindef.h>
#include <common.h>

#include "../CServer.h"

class CClientSocket
{
	static SOCKET g_pSocket;

public:
	static bool Start(WORD wPort);
	static void Close(int);
	static void Accept();
	static PVOID Await(PVOID client);

	// Threadless
	static bool Start_Poll(WORD wPort);
	static void Accept_Poll();
	static void Poll();

	static void OnNewConnection(SOCKET connection);
	static void OnCloseConnection(SOCKET connection);
	static void OnIncomingPacket(SOCKET connection, Packet& packet);

	static void DebugRawPacket(Packet& packet);
};

#endif
