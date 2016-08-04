#include "CClient.h"

bool CClient::Write(BYTE byType, ...)
{
	if (m_pSocket == INVALID_SOCKET)
		return false;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	send(m_pSocket, (char*)&packet, packet.wSize, 0);

	return true;
}