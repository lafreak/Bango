#include "CDatabase.h"

std::mutex 			CDatabase::m_mxConnection;

sql::Connection* 	CDatabase::g_pConnection = NULL;
sql::Driver* 		CDatabase::g_pDriver = NULL;

bool CDatabase::Connect(std::string szHostname, std::string szPort, std::string szUsername, std::string szPassword)
{
	CDatabase::g_pDriver = get_driver_instance();
	if (!CDatabase::g_pDriver) {
		printf(KRED "Can't get driver instance.\n" KNRM);
		return false;
	}

	CDatabase::g_pConnection = CDatabase::g_pDriver->connect("tcp://"+szHostname+":"+szPort, szUsername, szPassword);
	if (!CDatabase::g_pConnection) {
		printf(KRED "Can't connect to database.\n" KNRM);
		return false;
	}

	return true;
}

void CDatabase::Close()
{
	Lock();

	if (CDatabase::g_pConnection)
		delete CDatabase::g_pConnection;

	Unlock();
}

void CDatabase::SetSchema(std::string szSchema)
{
	if (CDatabase::g_pConnection) 
		CDatabase::g_pConnection->setSchema(szSchema);
}