#ifndef _CSERVER_
#define _CSERVER_

#include <map>

#include <minwindef.h>

#include "CAccount.h"

typedef std::map<SOCKET, CAccount*> AccountMap;

class CServer
{
public:
	static AccountMap g_mAccount;
	static std::mutex g_mxAccount;
	
	static void Add(CAccount* pAccount);
	static void Remove(CAccount* pAccount);
	static CAccount* FindAccount(SOCKET socket);
	static CAccount* FindAccountByAID(int nAccountID);
	static void EmptyAccount();
};

#endif