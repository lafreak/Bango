#include <string>
#include <mutex>

#include <minwindef.h>
#include <common.h>

#include <zdb.h>

class CDatabase
{
	static std::mutex g_mxThis;

	static URL_T g_pUrl;
public:

	static ConnectionPool_T g_pConnectionPool;

	static void Lock() { g_mxThis.lock(); }
	static void Unlock() { g_mxThis.unlock(); }

	static bool Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword, std::string szSchema);
	static void Close();
};