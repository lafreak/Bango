#include <string>
#include <mutex>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <minwindef.h>
#include <common.h>

typedef std::shared_ptr<sql::PreparedStatement> pstmt_ptr;
typedef std::shared_ptr<sql::ResultSet> rs_ptr;

class CDatabase
{
	static std::mutex m_mxConnection;

public:
	static sql::Connection* g_pConnection;
	static sql::Driver* g_pDriver;

	static void Lock() { m_mxConnection.lock(); }
	static void Unlock() { m_mxConnection.unlock(); }

	static bool Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword);
	static void Close();
	static void SetSchema(std::string szSchema);
};