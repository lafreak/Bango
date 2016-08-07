#include "Socket/CClientSocket.h"
#include "Socket/CDBSocket.h"

int main()
{

	if (!CDBSocket::Connect(2999))
		return 1;

	if (!CClientSocket::Start(3000))
		return 1;

	printf(KGRN "MainServer started on port 3000.\n" KNRM);

	CClientSocket::Accept();

	return 0;
}
