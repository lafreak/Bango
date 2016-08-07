#include "Socket/CClientSocket.h"
#include "Socket/CDBSocket.h"

int main()
{

	if (!CDBSocket::Connect(2999))
		return 1;

	if (!CClientSocket::Start(3000))
		return 1;

	printf("MainServer started on port 3000.\n");

	CClientSocket::Accept();

	return 0;
}
