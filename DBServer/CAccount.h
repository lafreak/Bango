#ifndef _CACCOUNT_
#define _CACCOUNT_

#include <string>
#include <mutex>
#include <unistd.h>

#include <access.h>

#include <minwindef.h>

class CAccount
{
	std::mutex m_mxThis;

	int m_nClientID;
	int m_nAccountID;
	std::string m_szLogin;
	std::string m_szPassword;
	std::string m_szSecondary;

public:
	CAccount(int nClientID, int nAccountID, std::string szLogin, std::string szPassword, std::string szSecondary): 
		m_nClientID(nClientID), m_nAccountID(nAccountID), m_szLogin(szLogin), m_szPassword(szPassword), m_szSecondary(szSecondary),
		m_Access()
		{ }
	~CAccount();

	static WORD g_wDebugItems[4][8];

	Access m_Access;

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	int 		GetAID() const { return m_nAccountID; }
	int 		GetCID() const { return m_nClientID; }
	std::string GetLogin() const { return m_szLogin; }
	std::string GetPassword() const { return m_szPassword; }
	std::string GetSecondary() const { return m_szSecondary; }
	void 		SetSecondary(std::string szSecondary) { m_szSecondary = szSecondary; }

	void SendPlayerInfo();
};

#endif