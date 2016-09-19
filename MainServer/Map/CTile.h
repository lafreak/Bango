#ifndef _CTILE_
#define _CTILE_

#include <mutex>
#include <math.h>

#include "../GameCharacter/CPlayer.h"
#include "../GameCharacter/CNPC.h"
#include "../GameCharacter/CMonster.h"
#include "../Item/CItem.h"

class CTile
{
	std::mutex m_mxThis;

	//CharacterMap m_mCharacter;

	PlayerMap m_mPlayer;
	NPCMap m_mNPC;
	MonsterMap m_mMonster;
	ItemMap m_mItem;

public:
	CTile() {}

	void Add(CCharacter *pCharacter);
	void Remove(CCharacter *pCharacter);

	void AddItem(CItem *pItem);
	void RemoveItem(CItem* pItem);

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	// Remember to run m_Access.Release on each used object in the list.
	void GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list);
	void GetPlayerListAround(CCharacter *pCharacter, int nDistance, PlayerList& list);
	void GetMonsterListAround(CCharacter *pCharacter, int nDistance, MonsterList& list);
	void GetItemListAround(CCharacter *pCharacter, int nDistance, ItemList& list);

	void SendPacket(CCharacter *pCharacter, Packet& packet);

	void SendMoveAction(CCharacter *pCharacter, char byX, char byY, 
		Packet& createPacket, Packet& petPacket, Packet& deletePacket, Packet& movePacket);
};

#endif