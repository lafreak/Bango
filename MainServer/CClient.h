#ifndef _CCLIENT_
#define _CCLIENT_

#include <string>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>
#include <minwindef.h>

#include <Socket/CSocket.h>
#include <minwindef.h>

class CClient
{
	SOCKET m_pSocket;
	std::string m_szMac;

public:
	CClient(SOCKET pSocket): m_pSocket(pSocket) {}
	~CClient() {}

	bool Write(BYTE byType, ...);

	void 		SetMAC(std::string szMac) { m_szMac = szMac; }
	std::string GetMAC() const { return m_szMac; }

	SOCKET 		GetSocket() const { return m_pSocket; }
};

#endif