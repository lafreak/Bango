#include <cstdlib>

#include "Socket/CClientSocket.h"
#include "Socket/CDBSocket.h"

#include "Map/CMap.h"
#include "GameCharacter/CNPC.h"
#include "Macro/CMacroDB.h"

#include "CServer.h"

#include "Config/CConfig.h"

int main()
{
	MAINCONFIG mainconf;
	if (CConfig::Read(mainconf) == CConfig::READ_ERROR)
		return 1;

	srand(time(NULL));

	if (!CDBSocket::Connect(mainconf.wDBPort))
		return 1;

	if (!CClientSocket::Start(mainconf.wMainPort))
		return 1;

	if (!CMacroDB::Initialize())
		return 1;

	printf("Loading Maps...\n");
	CMap::LoadMaps();

	printf("Loading NPC...\n");
	if (!CNPC::LoadNPC())
		return 1;

	if (!CServer::Start())
		return 1;

	printf(KGRN "MainServer started on port %d.\n" KNRM, mainconf.wMainPort);

	CClientSocket::Accept();

	return 0;
}
