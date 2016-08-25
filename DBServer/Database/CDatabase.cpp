#include "CDatabase.h"

std::mutex			CDatabase::g_mxThis;

URL_T				CDatabase::g_pUrl = NULL;
ConnectionPool_T 	CDatabase::g_pConnectionPool = NULL;

bool CDatabase::Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword, std::string szSchema)
{
	std::string szUrl = "mysql://"+szHostname+":"+szPort+"/"+szSchema+"?user="+szUsername+"&password="+szPassword;
	
	CDatabase::g_pUrl = URL_new(szUrl.c_str());
	CDatabase::g_pConnectionPool = ConnectionPool_new(CDatabase::g_pUrl);
	
	ConnectionPool_start(CDatabase::g_pConnectionPool);

	return true;
}

void CDatabase::Close()
{
	if (CDatabase::g_pConnectionPool)
		ConnectionPool_free(&CDatabase::g_pConnectionPool);

	if (CDatabase::g_pUrl)
		URL_free(&CDatabase::g_pUrl);
}