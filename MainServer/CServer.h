#ifndef _CSERVER_
#define _CSERVER_

#include <map>

#include <minwindef.h>

#include "CClient.h"

class CServer
{
public:
	static std::map<SOCKET, CClient*> g_mClient;
	
	static void Add(CClient* pClient);
	static void Remove(CClient* pClient);
	static CClient* FindClient(SOCKET socket);
};

#endif