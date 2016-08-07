#include "CServer.h"

std::map<int, CClient*> CServer::g_mClient;
std::map<int, CPlayer*> CServer::g_mPlayer;

void CServer::Add(CClient *pClient)
{
	if (g_mClient.find(pClient->GetCID()) != g_mClient.end())
		return;

	g_mClient[pClient->GetCID()] = pClient;
}

void CServer::Remove(CClient *pClient)
{
	std::map<int, CClient*>::iterator it = g_mClient.find(pClient->GetCID());
	if (it != g_mClient.end()) {
		g_mClient.erase(it);
		delete pClient;
	}
}

CClient* CServer::FindClient(int nCID)
{
	if (g_mClient.find(nCID) == g_mClient.end())
		return NULL;

	return g_mClient[nCID];
}

void CServer::Add(CPlayer *pPlayer)
{
	if (g_mPlayer.find(pPlayer->GetID()) != g_mPlayer.end())
		return;

	g_mPlayer[pPlayer->GetID()] = pPlayer;
}

void CServer::Remove(CPlayer *pPlayer)
{
	std::map<int, CPlayer*>::iterator it = g_mPlayer.find(pPlayer->GetID());
	if (it != g_mPlayer.end()) {
		g_mPlayer.erase(it);
		delete pPlayer;
	}
}

CPlayer* CServer::FindPlayer(int nID)
{
	if (g_mPlayer.find(nID) == g_mPlayer.end())
		return NULL;

	return g_mPlayer[nID];
}