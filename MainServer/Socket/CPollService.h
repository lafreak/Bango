#ifndef _CPOLLSERVICE_
#define _CPOLLSERVICE_

#include <Protocol/Packet.h>
#include <minwindef.h>
#include <vector>
#include <functional>
#include <sys/poll.h>

#define POLLSERVICE_OK					0
#define POLLSERVICE_MAINSOCKETMISSING	1
#define POLLSERVICE_POLLERROR			2
#define POLLSERVICE_ACCEPTERROR			3
#define POLLSERVICE_RECVERROR			4

class CPollService
{
	SOCKET m_socket;

	std::vector<pollfd> m_pollfds;

	std::function<void(SOCKET)>				m_fnOnNewConnection;
	std::function<void(SOCKET)>				m_fnOnCloseConnection;
	std::function<void(SOCKET, Packet&)>	m_fnOnIncomingPacket;

public:
	CPollService(SOCKET socket);

	void AddNewConnectionHandler	(std::function<void(SOCKET)> fn)			{ m_fnOnNewConnection = fn; }
	void AddCloseConnectionHandler	(std::function<void(SOCKET)> fn)			{ m_fnOnCloseConnection = fn; }
	void AddIncomingPacketHandler	(std::function<void(SOCKET, Packet&)> fn)	{ m_fnOnIncomingPacket = fn; }

	BYTE Poll();
};

#endif
