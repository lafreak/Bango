#include "CServer.h"

std::map<SOCKET, CAccount*> CServer::g_mAccount;

void CServer::Add(CAccount *pAccount)
{
	if (g_mAccount.find(pAccount->GetCID()) != g_mAccount.end())
		return;

	g_mAccount[pAccount->GetCID()] = pAccount;
}

void CServer::Remove(CAccount *pAccount)
{
	std::map<SOCKET, CAccount*>::iterator it = g_mAccount.find(pAccount->GetCID());
	if (it != g_mAccount.end()) {
		g_mAccount.erase(it);
		delete pAccount;
	}
}

CAccount* CServer::FindAccount(int nClientID)
{
	if (g_mAccount.find(nClientID) == g_mAccount.end())
		return NULL;

	return g_mAccount[nClientID];
}

CAccount* CServer::FindAccountByAID(int nAccountID)
{
	for (auto const &a: g_mAccount) {
		if (a.second->GetAID() == nAccountID)
			return a.second;
	}

	return NULL;
}

void CServer::EmptyAccount()
{
	for (auto a: g_mAccount)
		delete a.second;
	
	g_mAccount.empty();
}