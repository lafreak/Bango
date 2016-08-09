#ifndef _CTILE_
#define _CTILE_

#include <map>
#include <mutex>
#include <math.h>

#include "../CPlayer.h"

typedef std::map<int, CCharacter*> CharacterMap;

class CTile
{
	std::mutex m_mxThis;

	CharacterMap m_mCharacter;

public:
	CTile() {}

	void Add(CCharacter *pCharacter);
	void Remove(int nID);

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	void SendPacket(int nX, int nY, Packet& packet);
};

#endif