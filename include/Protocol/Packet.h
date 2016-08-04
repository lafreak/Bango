#ifndef _PACKET_
#define _PACKET_

#include <minwindef.h>

#define MAX_PACKET_LENGTH		8000

struct Packet
{
	WORD wSize;
	BYTE byType;
	char data[MAX_PACKET_LENGTH];
};

#endif