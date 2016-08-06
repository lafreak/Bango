#include "CServer.h"

std::map<SOCKET, CAccount*> CServer::g_mAccount;

void CServer::Add(CAccount *pAccount)
{
	if (g_mAccount.find(pAccount->GetSocket()) != g_mAccount.end())
		return;

	g_mAccount[pAccount->GetSocket()] = pAccount;
}

void CServer::Remove(CAccount *pAccount)
{
	std::map<SOCKET, CAccount*>::iterator it = g_mAccount.find(pAccount->GetSocket());
	if (it != g_mAccount.end()) {
		g_mAccount.erase(it);
		delete pAccount;
	}
}

CAccount* CServer::FindAccount(SOCKET socket)
{
	if (g_mAccount.find(socket) == g_mAccount.end())
		return NULL;

	return g_mAccount[socket];
}

CAccount* CServer::FindAccount(std::string szLogin)
{
	for (auto const &a: g_mAccount) {
		if (a.second->GetLogin() == szLogin)
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