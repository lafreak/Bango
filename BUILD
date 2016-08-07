g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CSocket.o include/Socket/CSocket.cpp

# DBServer
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CAccount.o DBServer/CAccount.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CServer.o DBServer/CServer.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CMainSocket.o DBServer/Socket/CMainSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CDatabase.o DBServer/Database/CDatabase.cpp 
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/main.o DBServer/main.cpp

g++ --std=c++11 -pthread -o bin/DBServer bin/obj/CSocket.o bin/obj/CAccount.o bin/obj/CServer.o bin/obj/CDatabase.o bin/obj/CMainSocket.o bin/obj/main.o -lmysqlcppconn

# MainServer
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CClient.o MainServer/CClient.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CCharacter.o MainServer/CCharacter.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CPlayer.o MainServer/CPlayer.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CServer.o MainServer/CServer.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CDBSocket.o MainServer/Socket/CDBSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/CClientSocket.o MainServer/Socket/CClientSocket.cpp
g++ --std=c++11 -pthread -I include/ -c -o bin/obj/main.o MainServer/main.cpp

g++ --std=c++11 -pthread -o bin/MainServer bin/obj/CSocket.o bin/obj/CClient.o bin/obj/CCharacter.o bin/obj/CPlayer.o bin/obj/CServer.o bin/obj/CDBSocket.o bin/obj/CClientSocket.o bin/obj/main.o