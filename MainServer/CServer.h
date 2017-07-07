#ifndef _CSERVER_
#define _CSERVER_

#include <map>
#include <mutex>

#include <minwindef.h>

#include "CClient.h"
#include "GameCharacter/CPlayer.h"
#include "GameCharacter/CMonster.h"
#include "Map/CMap.h"

typedef std::map<int, CClient*> ClientMap;

class CServer
{

public:

	static ClientMap  g_mClient;
	static std::mutex g_mxClient;

	static void Add(CClient* pClient);
	static void Remove(CClient* pClient);
	static void EmptyClient();

	static bool Start();

	static PVOID Timer(PVOID param);

	// Remember to call m_Access.Release() after work on client is done.
	static CClient* FindClient(int nCID);
};

#endif