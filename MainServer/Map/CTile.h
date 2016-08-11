#ifndef _CTILE_
#define _CTILE_

#include <map>
#include <list>
#include <mutex>
#include <math.h>

#include "../CPlayer.h"

typedef std::map<int, CCharacter*> CharacterMap;
typedef std::map<int, CPlayer*> PlayerMap;
typedef std::list<CCharacter*> ObjectList;

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

	// Remember to run m_Access.Release on each used object in the list.
	void GetObjectListAround(CCharacter *pCharacter, int nDistance, ObjectList& list);

	void SendPacket(CCharacter *pCharacter, Packet& packet);

	void SendMoveAction(CCharacter *pCharacter, char byX, char byY, 
		Packet& createPacket, Packet& deletePacket, Packet& movePacket);
};

#endif