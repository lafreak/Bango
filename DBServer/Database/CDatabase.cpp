#include "CDatabase.h"

sql::Connection* CDatabase::g_pConnection;

bool CDatabase::Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword)
{
	sql::Driver *pDriver = get_driver_instance();
	if (!pDriver) {
		printf("Can't get driver instance.\n");
		return false;
	}

	CDatabase::g_pConnection = pDriver->connect("tcp://"+szHostname+":"+szPort, szUsername, szPassword);
	if (!CDatabase::g_pConnection) {
		printf("Can't connect to database.\n");
		return false;
	}

	return true;
}

void CDatabase::SetSchema(std::string szSchema)
{
	if (CDatabase::g_pConnection) 
		CDatabase::g_pConnection->setSchema(szSchema);
}