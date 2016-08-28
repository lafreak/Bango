#ifndef _PACKET_
#define _PACKET_

#include <minwindef.h>

#define MAX_PACKET_LENGTH		8000

#pragma pack (push, 1)

struct PACKETBUFFER
{
	char data[MAX_PACKET_LENGTH];
};

struct Packet
{
	WORD wSize;
	BYTE byType;
	char data[MAX_PACKET_LENGTH];
};

#pragma pack (pop)

#endif