#ifndef _CSERVER_
#define _CSERVER_

#include <map>

#include <minwindef.h>

#include "CClient.h"
#include "CPlayer.h"

class CServer
{
public:
	static std::map<int, CClient*> g_mClient;
	static std::map<int, CPlayer*> g_mPlayer;
	
	static void Add(CClient* pClient);
	static void Remove(CClient* pClient);
	static CClient* FindClient(int nCID);

	static void Add(CPlayer* pPlayer);
	static void Remove(CPlayer* pPlayer);
	static CPlayer* FindPlayer(int nID);
};

#endif