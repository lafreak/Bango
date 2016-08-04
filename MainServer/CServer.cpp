#include "CServer.h"

std::map<SOCKET, CClient*> CServer::g_mClient;

void CServer::Add(CClient *pClient)
{
	if (g_mClient.find(pClient->GetSocket()) != g_mClient.end())
		return;

	g_mClient[pClient->GetSocket()] = pClient;
}

void CServer::Remove(CClient *pClient)
{
	std::map<SOCKET, CClient*>::iterator it = g_mClient.find(pClient->GetSocket());
	if (it != g_mClient.end()) {
		g_mClient.erase(it);
		delete pClient;
	}
}

CClient* CServer::FindClient(SOCKET socket)
{
	if (g_mClient.find(socket) == g_mClient.end())
		return NULL;

	return g_mClient[socket];
}