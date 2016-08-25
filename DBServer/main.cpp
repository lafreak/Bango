#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

int main()
{

	if (!CDatabase::Connect("127.0.0.1", "3306", "root", "iostream;", "kalonline"))
		return 1;

	if (!CMainSocket::Start(2999))
		return 1;

	printf(KGRN "DBServer started on port 2999.\n" KNRM);

	CMainSocket::Accept();

	return 0;
}