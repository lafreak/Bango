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
		delete pClient;
 	}

 	g_mxClient.unlock();
}

void CServer::EmptyClient()
{
	g_mxClient.lock();

	for (auto& a: g_mClient) {
		delete a.second;
	}

	g_mClient.clear();

 	g_mxClient.unlock();
}

CClient* CServer::FindClient(int nCID)
{
	CClient* pClient=NULL;

	g_mxClient.lock();

	if (g_mClient.find(nCID) != g_mClient.end()) {
		pClient = g_mClient[nCID];
		pClient->m_Access.Grant();
	}

	g_mxClient.unlock();

	return pClient;
}

bool CServer::Start()
{
	pthread_t t;

	if (pthread_create(&t, NULL, &CServer::Timer, NULL) != THREAD_SUCCESS) 
	{
		printf(KRED "ERROR: Couldn't start thread.\n" KNRM);
		return false;
	}

	return true;
}

PVOID CServer::Timer(PVOID)
{
	DWORD dwTickTime = GetTickCount();

	while (true)
	{
		usleep(30000);

		DWORD dwNow = GetTickCount();

		if (dwNow - dwTickTime >= 1000) 
		{
			CPlayer::g_mxPlayer.lock();

			for (auto& a: CPlayer::g_mPlayer) 
			{
				a.second->m_Access.Grant();
				a.second->Tick();
				a.second->m_Access.Release();
			}

			CPlayer::g_mxPlayer.unlock();

			CMonster::g_mxMonster.lock();

			for (auto& a: CMonster::g_mMonster) 
			{
				a.second->m_Access.Grant();
				a.second->Tick();
				a.second->m_Access.Release();
			}

			CMonster::g_mxMonster.unlock();

			dwTickTime = dwNow;
		}
	}
}