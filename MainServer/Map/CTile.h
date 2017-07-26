#ifndef _CTILE_
#define _CTILE_

#include <mutex>
#include <math.h>

#include "../GameCharacter/CPlayer.h"
#include "../GameCharacter/CNPC.h"
#include "../GameCharacter/CMonster.h"

/**
	Represents square tile of 1024x1024 cells.
	Keeps track of all dynamic objects on that area.
*/
class CTile
{
	std::mutex m_mxThis;

	PlayerMap m_mPlayer;
	NPCMap m_mNPC;
	MonsterMap m_mMonster;

public:
	/** Basic constructor. */
	CTile() {}

	/**
		Adds character to tile.
		Gets called when player enters this tile or enters game.
		\param pCharacter Object to add.
	*/
	void Add(CCharacter *pCharacter);

	/**
		Removes character from tile.
		Gets called when player enters another tile or quits the game completely.
		\param pCharacter Object to remove.
	*/
	void Remove(CCharacter *pCharacter);

	/** Locks access to instance. */
	void Lock() { m_mxThis.lock(); }

	/** Unlocks access to instance */
	void Unlock() { m_mxThis.unlock(); }

	/**
		Retrieves all characters around certain character on a tile.
		Grants access to each one, so it is a <b>MUST</b> to release it after usage.
		\param pCharacter Character to find objects around it.
		\param nDistance Max distance from character.
		\param list Empty list that will get populated with found characters.
	*/
	void GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list);

	/**
		Retrieves all players around certain character on a tile.
		Grants access to each one, so it is a <b>MUST</b> to release it after usage.
		\param pCharacter Character to find players around it.
		\param nDistance Max distance from character.
		\param list Empty list that will get populated with found players.
	*/
	void GetPlayerListAround(CCharacter *pCharacter, int nDistance, PlayerList& list);

	/**
		Retrieves all monsters around certain character on a tile.
		Grants access to each one, so it is a <b>MUST</b> to release it after usage.
		\param pCharacter Character to find monsters around it.
		\param nDistance Max distance from character.
		\param list Empty list that will get populated with found monsters.
	*/
	void GetMonsterListAround(CCharacter *pCharacter, int nDistance, MonsterList& list);

	/**
		Sends packet to all players on tile within sight of certain character.
		\param pCharacter Character to send packet around it.
		\param packet Packet to be sent.
	*/
	void SendPacket(CCharacter *pCharacter, Packet& packet);

	/**
		Distributes appear/pet appear/disappear/move packets to players nearby.
		Decides who to send depending on character kind.
		\param pCharacter Character to exchange packets with.
		\param byX X coordinate movement delta.
		\param byY Y coordinate movement delta.
		\param createPacket Pre-generated appear packet for distribution.
		\param petPacket Pre-generated pet appear packet for distribution.
		\param deletePacket Pre-generated disappear packet for distribution.
		\param movePacket Pre-generated move packet for distribution.
	*/
	void SendMoveAction(CCharacter *pCharacter, char byX, char byY, 
		Packet& createPacket, Packet& petPacket, Packet& deletePacket, Packet& movePacket);

	/**
		Exchanges appear/pet appear/disappear/move packets with players nearby.
		Decides what to send depending on distance between objects.
		\param pCharacter Character to exchange packets with.
		\param byX X coordinate movement delta.
		\param byY Y coordinate movement delta.
		\param createPacket Pre-generated appear packet for distribution.
		\param petPacket Pre-generated pet appear packet for distribution.
		\param deletePacket Pre-generated disappear packet for distribution.
		\param movePacket Pre-generated move packet for distribution.
	*/
	void ExchangeMoveActionWithPlayers(CCharacter *pCharacter, char byX, char byY,
		Packet& createPacket, Packet& petPacket, Packet& deletePacket, Packet& movePacket);

	/**
		Exchanges appear/pet appear/disappear/move packets with monsters nearby.
		Decides what to send depending on distance between objects.
		\param pPlayer Player to exchange packets with.
		\param byX X coordinate movement delta.
		\param byY Y coordinate movement delta.
	*/
	void ExchangeMoveActionWithMonsters(CPlayer *pPlayer, char byX, char byY);

	/**
		Exchanges appear/pet appear/disappear/move packets with NPCs nearby.
		Decides what to send depending on distance between objects.
		\param pPlayer Player to exchange packets with.
		\param byX X coordinate movement delta.
		\param byY Y coordinate movement delta.
	*/
	void ExchangeMoveActionWithNPCs(CPlayer *pPlayer, char byX, char byY);
};

#endif
