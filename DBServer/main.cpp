#include "Socket/CMainSocket.h"
#include "Database/CDatabase.h"

int main()
{

	if (!CDatabase::Connect("127.0.0.1", "3306", "root", "password"))
		return 1;

	CDatabase::SetSchema("kalonline");

	if (!CMainSocket::Start(2999))
		return 1;

	printf("DBServer started on port 2999.\n");

	CMainSocket::Accept();

	return 0;
}