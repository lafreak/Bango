#ifndef _CACCOUNT_
#define _CACCOUNT_

#include <string>

#include <minwindef.h>

class CAccount
{
	SOCKET m_pSocket;
	int m_nAccountID;
	std::string m_szLogin;
	std::string m_szPassword;

public:
	CAccount(SOCKET pSocket, int nAccountID, std::string szLogin, std::string szPassword): 
		m_pSocket(pSocket), m_nAccountID(nAccountID), m_szLogin(szLogin), m_szPassword(szPassword) {}
	~CAccount() {}

	int 		GetAID() const { return m_nAccountID; }
	std::string GetLogin() const { return m_szLogin; }
	std::string GetPassword() const { return m_szPassword; }
	SOCKET 		GetSocket() const { return m_pSocket; }

	void SendPlayerInfo();
};

#endif