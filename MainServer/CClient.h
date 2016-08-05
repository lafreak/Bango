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
	std::string m_szLogin;
	std::string m_szPassword;

public:
	CClient(SOCKET pSocket): m_pSocket(pSocket) {}
	~CClient() {}

	bool Write(BYTE byType, ...);

	void 		SetMAC(std::string szMac) { m_szMac = szMac; }
	std::string GetMAC() const { return m_szMac; }
	void 		SetLogin(std::string szLogin) { m_szLogin = szLogin; }
	std::string GetLogin() const { return m_szLogin; }
	void 		SetPassword(std::string szPassword) { m_szPassword = szPassword; }
	std::string GetPassword() const { return m_szPassword; }

	SOCKET 		GetSocket() const { return m_pSocket; }
};

#endif