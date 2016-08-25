#include <string>
#include <mutex>

#include <minwindef.h>
#include <common.h>

#include <zdb.h>

class CDatabase
{
	static URL_T g_pUrl;
public:

	static ConnectionPool_T g_pConnectionPool;

	static bool Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword, std::string szSchema);
	static void Close();
};