#ifndef _CSERVER_
#define _CSERVER_

#include <map>
#include <mutex>

#include <minwindef.h>

#include "CClient.h"
#include "CPlayer.h"

typedef std::map<int, CClient*> ClientMap;

class CServer
{
public:
	static ClientMap  g_mClient;
	static std::mutex g_mxClient;

	static void Add(CClient* pClient);
	static void Remove(CClient* pClient);
	static CClient* FindClient(int nCID);
};

#endif