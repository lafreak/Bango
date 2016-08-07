#ifndef _CSOCKET_
#define _CSOCKET_

#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>
#include <minwindef.h>

class CSocket
{
public:
	static bool g_bDebug;

	static char* WriteV(char* packet, va_list va);
	
	static char* WritePacket(char* packet, const char* format, ...);
	static char* ReadPacket(char* packet, const char* format, ...);
};

#endif