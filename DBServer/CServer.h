#ifndef _CSERVER_
#define _CSERVER_

#include <map>

#include <minwindef.h>

#include "CAccount.h"

class CServer
{
public:
	static std::map<SOCKET, CAccount*> g_mAccount;
	
	static void Add(CAccount* pAccount);
	static void Remove(CAccount* pAccount);
	static CAccount* FindAccount(SOCKET socket);
	static CAccount* FindAccountByAID(int nAccountID);
	static void EmptyAccount();
};

#endif