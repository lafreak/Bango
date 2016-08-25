g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CSocket.o include/Socket/CSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/tinyxml2.o include/TinyXML2/tinyxml2.cpp

# XMLConfigExporter
g++ --std=c++11 -I include/ -o Utility/XMLConfigExporter/bin/Convert bin/obj/tinyxml2.o Utility/XMLConfigExporter/ConvertC++.cpp

# DBServer
g++ --std=c++11 -pthread -I include/ -I /usr/include/zdb/ -c -o bin/obj/CAccount.o DBServer/CAccount.cpp
g++ --std=c++11 -pthread -I include/ -I /usr/include/zdb/ -c -o bin/obj/CServer.o DBServer/CServer.cpp
g++ --std=c++11 -pthread -I include/ -I /usr/include/zdb/ -c -o bin/obj/CMainSocket.o DBServer/Socket/CMainSocket.cpp
g++ --std=c++11 -pthread -I include/ -I /usr/include/zdb/ -c -o bin/obj/CDatabase.o DBServer/Database/CDatabase.cpp 
g++ --std=c++11 -pthread -I include/ -I /usr/include/zdb/ -c -o bin/obj/main.o DBServer/main.cpp

g++ --std=c++11 -pthread -o bin/DBServer bin/obj/CSocket.o bin/obj/CAccount.o bin/obj/CServer.o bin/obj/CDatabase.o bin/obj/CMainSocket.o bin/obj/main.o -lzdb

# MainServer
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CMacro.o MainServer/Macro/CMacro.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemInfo.o MainServer/Macro/CItemInfo.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CMacroDB.o MainServer/Macro/CMacroDB.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItem.o MainServer/Item/CItem.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemGeneral.o MainServer/Item/CItemGeneral.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemWeapon.o MainServer/Item/CItemWeapon.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemDefense.o MainServer/Item/CItemDefense.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemYinyang.o MainServer/Item/CItemYinyang.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CItemPet.o MainServer/Item/CItemPet.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CClient.o MainServer/CClient.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CCharacter.o MainServer/GameCharacter/CCharacter.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CPlayer.o MainServer/GameCharacter/CPlayer.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CNPC.o MainServer/GameCharacter/CNPC.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CTile.o MainServer/Map/CTile.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CMap.o MainServer/Map/CMap.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CServer.o MainServer/CServer.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CDBSocket.o MainServer/Socket/CDBSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CClientSocket.o MainServer/Socket/CClientSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/main.o MainServer/main.cpp

g++ --std=c++11 -pthread -o bin/MainServer bin/obj/tinyxml2.o bin/obj/CSocket.o bin/obj/CMacro.o bin/obj/CItemInfo.o bin/obj/CMacroDB.o bin/obj/CItem.o bin/obj/CItemGeneral.o bin/obj/CItemWeapon.o bin/obj/CItemDefense.o bin/obj/CItemYinyang.o bin/obj/CItemPet.o bin/obj/CClient.o bin/obj/CCharacter.o bin/obj/CPlayer.o bin/obj/CNPC.o bin/obj/CTile.o bin/obj/CMap.o bin/obj/CServer.o bin/obj/CDBSocket.o bin/obj/CClientSocket.o bin/obj/main.o