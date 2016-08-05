#include <string>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

typedef std::shared_ptr<sql::PreparedStatement> pstmt_ptr;
typedef std::shared_ptr<sql::ResultSet> rs_ptr;

class CDatabase
{
public:
	static sql::Connection* g_pConnection;

	static bool Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword);
	static void SetSchema(std::string szSchema);
};