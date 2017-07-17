#include <Socket/CSocket.h>

#include "IAppearable.h"

Packet IAppearable::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	packet.wSize = 0;
	return packet;
}

Packet IAppearable::GeneratePetPacket()
{
	Packet packet;
	packet.wSize = 0;
	return packet;
}

Packet IAppearable::GenerateDeletePacket()
{
	Packet packet;
	packet.wSize = 0;
	return packet;
}

Packet IAppearable::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	packet.wSize = 0;
	return packet;
}
