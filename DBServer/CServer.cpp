#include "CServer.h"

AccountMap CServer::g_mAccount;

std::mutex CServer::g_mxAccount;

void CServer::Add(CAccount *pAccount)
{
	g_mxAccount.lock();

	if (g_mAccount.find(pAccount->GetCID()) == g_mAccount.end())
		g_mAccount[pAccount->GetCID()] = pAccount;

	g_mxAccount.unlock();
}

void CServer::Remove(CAccount *pAccount)
{
	g_mxAccount.lock();

	AccountMap::iterator it = g_mAccount.find(pAccount->GetCID());
	if (it != g_mAccount.end()) {
		g_mAccount.erase(it);
		delete pAccount;
	}

	g_mxAccount.unlock();
}

CAccount* CServer::FindAccount(int nClientID)
{
	g_mxAccount.lock();

	CAccount* pAccount=NULL;

	if (g_mAccount.find(nClientID) != g_mAccount.end()){
		pAccount = g_mAccount[nClientID];
		pAccount->m_Access.Grant();
	}

	g_mxAccount.unlock();

	return pAccount;
}

CAccount* CServer::FindAccountByAID(int nAccountID)
{
	g_mxAccount.lock();

	CAccount* pAccount=NULL;

	for (auto const &a: g_mAccount) {
		if (a.second->GetAID() == nAccountID) {
			pAccount = a.second;
			pAccount->m_Access.Grant();
			break;
		}
	}

	g_mxAccount.unlock();

	return pAccount;
}

void CServer::EmptyAccount()
{
	g_mxAccount.lock();

	for (auto a: g_mAccount)
		delete a.second; // ??
	
	g_mAccount.empty();

	g_mxAccount.unlock();
}