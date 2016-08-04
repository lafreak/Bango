#include "Socket/CMainSocket.h"

int main()
{
	if (!CMainSocket::Start(2999))
		return 1;

	printf("DBServer started on port 2999.\n");

	CMainSocket::Accept();

	return 0;
}