#include "CServer.h"

ClientMap CServer::g_mClient;

std::mutex CServer::g_mxClient;

void CServer::Add(CClient *pClient)
{
	g_mxClient.lock();

	if (g_mClient.find(pClient->GetCID()) == g_mClient.end())
		g_mClient[pClient->GetCID()] = pClient;

	g_mxClient.unlock();
}

void CServer::Remove(CClient *pClient)
{
	g_mxClient.lock();

	ClientMap::iterator it = g_mClient.find(pClient->GetCID());
	if (it != g_mClient.end()) {
		g_mClient.erase(it);
		delete pClient; // delete client/player that is still present in another thread?
 	}

 	g_mxClient.unlock();
}

CClient* CServer::FindClient(int nCID)
{
	CClient* pClient=NULL;

	g_mxClient.lock();

	if (g_mClient.find(nCID) != g_mClient.end())
		pClient = g_mClient[nCID];

	g_mxClient.unlock();

	return pClient;
}