#ifndef _CCLIENT_
#define _CCLIENT_

#include <string>
#include <mutex>

#include <cstdarg>
#include <string.h>
#include <unistd.h>

#include <Protocol/Packet.h>
#include <Protocol/MainProtocol.h>

#include <Socket/CSocket.h>

#include <minwindef.h>
#include <common.h>

#include <access.h>

#include "Socket/CDBSocket.h"
#include "CPlayer.h"

class CClient
{
	std::mutex m_mxThis;

	int m_nCID;
	
	std::string m_szMac;
	std::string m_szLogin;
	std::string m_szPassword;

	CPlayer* m_pPlayer;

public:
	CClient(int nCID): m_nCID(nCID), m_pPlayer(NULL), m_Access() {}
	~CClient();

	Access m_Access;

	bool Write(BYTE byType, ...);

	void Process(Packet packet);

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	void 		SetMAC(std::string szMac) { m_szMac = szMac; }
	std::string GetMAC() const { return m_szMac; }
	void 		SetLogin(std::string szLogin) { m_szLogin = szLogin; }
	std::string GetLogin() const { return m_szLogin; }
	void 		SetPassword(std::string szPassword) { m_szPassword = szPassword; }
	std::string GetPassword() const { return m_szPassword; }

	int 		GetCID() const { return m_nCID; }

	void		RemovePlayer() { m_pPlayer=NULL; }

	void OnLogin(char *p);
	void OnLoadPlayer(char *p);
};

#endif