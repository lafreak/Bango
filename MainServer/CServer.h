#ifndef _CSERVER_
#define _CSERVER_

#include <map>
#include <mutex>

#include <minwindef.h>

#include "CClient.h"
#include "CPlayer.h"
#include "Map/CMap.h"

typedef std::map<int, CClient*> ClientMap;

class CServer
{
	static ClientMap  g_mClient;
	static std::mutex g_mxClient;

public:

	static void Add(CClient* pClient);
	static void Remove(CClient* pClient);

	// Remember to call m_Access.Release() after work on client is done.
	static CClient* FindClient(int nCID);

	static void LoadMaps();
};

#endif