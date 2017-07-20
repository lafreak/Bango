#ifndef _C_PARTY_
#define _C_PARTY_

#include <map>
#include <unistd.h>
#include <mutex>
#include <list>

#include <vector>

#include <access.h>

#include <Protocol/Packet.h>
#include <Socket/CSocket.h>

#include <cstring>
#include <cstdlib>

#include <string.h>

#include <algorithm>

#include <access.h>

#include "CPlayer.h"

typedef std::vector<CPlayer*> PlayerVector;

/**
	Class representation of ingame Party.
	Group of Players playing together.
*/
class CParty
{
private:
	int m_nID;

	PlayerVector m_vMembers;
	std::mutex m_mxThis;

	static std::map<int, CParty*> g_mParty;
	static std::mutex g_mxParty;

	static int g_nMaxID;
	static std::mutex g_mxMaxID;

	static int NewID();
	static void Add(CParty* pParty);
	static void Remove(CParty* pParty);

public:
	/**
		Keeps track if instance is busy or not.
	*/
	Access m_Access;

	/**
		Basic party constructor.
		Takes two players which start a new party.
		\param pLeader Leader of newly created party.
		\param pPlayer Second player of newly created party.
	*/
	CParty(CPlayer* pLeader, CPlayer* pPlayer);

	/**
		Basic destructor.
		Removes party from global party list before destruction.
	*/
	~CParty();
	
	/**
		Iterates through all parties ingame and calls Tick method on it.
		Gets called once a second.
	*/
	static void TickAll();

	/**
		Find Party with certain ID.
		Grants m_Access, so it is a <b>must</b> to Release it after usage.
		\param nID Party ID identifier.
		\return Party with certain ID.
	*/
	static CParty* FindParty(int nID);

	/**
		Teleports all party members to given position.
		Given spread value, it will randomize position in certain distance.
		\param nX X map coordinate.
		\param nY Y map coordinate.
		\param nSpread Distance around X and Y.
	*/
	void Teleport(int nX, int nY, int nSpread =0);

	/**
		Retrieves party ID assigned while creation.
		Party IDs are assigned starting from 1 up to MAX INT value.
		\return Party ID
	*/
	int GetID() const { return m_nID; }

	/**
		\return Amount of members currently in the party.
	*/
	int GetSize() const { return m_vMembers.size(); }

	/**
		Finds out whether player is currently a leader or not.
		Leadership may change during party lifetime.
		\param pPlayer Player to be checked for leadership
		\return true if player is head, false otherwise
	*/
	bool IsHead(CPlayer *pPlayer);

	/**
		Removes last member from party.
		Should be called only once per party, right before deletion.
		WARNING: Depreciated
	*/
	void Discard();

	/**
		Finds leader of the party.
		Grants access, so it <b>must</b> be released after usage.
		\return NULL if party is empty, leader player otherwise
	*/
	CPlayer* FindLeader();

	/**
		Adds member to last position of the party.
		Assigns party ID to player and resets his party invitation ID.
		Additionally, it distributes new player list packet among all party members.
		\param pPlayer New player to be added to party
	*/
	void AddMember(CPlayer* pPlayer);

	/**
		If given player is a member, removes him.
		Resets player party ID and sends party exit packet.
		Broadcasts new party list packet to other party members.
		\param pPlayer Player to be removed from party
	*/
	void RemoveMember(CPlayer* pPlayer);

	/**
		Sends packet with CurHP & MaxHP update information to all party members.
		\param pPlayer Player whose HP has been changed
		Client uses the information to update party window.
	*/
	void UpdateMemberHP(CPlayer *pPlayer);

	/**
		Send packet with level update information to all party members.
		\param pPlayer Player whose level has been changed
		Client uses the information to update party window.
	*/
	void UpdateMemberLevel(CPlayer *pPlayer);

	/**
		Sends information about ID, Name, Class, Level, CurHP, MaxHP of all party members to all party members.
		Does nothing if party is invalid (size smaller than 2).
		Client uses the information to update party window.
	*/
	void SendPartyInfo();

	/**
		Sends information about position (ID, X, Y) of all party members to all party members.
		Does nothing if party is invalid (size smaller than 2).
		Client uses the information to update minimap.
	*/
	void SendPositionInfo();

	/**
		Gets executed once a second.
	*/
	void Tick();

	/**
		Distributes packet among all party members.
		\param byType Packet header ID (from MainProtocol.h)
		\param ... First goes data format (ex. "bddb") and then values matching that format.
		Example: Broadcast(S2C_CHATTING, "sd", "String", 150);
	*/
	void Broadcast(BYTE byType, ...);

	/**
		Distributes packet among all party members.
		\param packet Generated packet ready to be sent.
	*/
	void Broadcast(Packet& packet);
};

typedef std::map<int, CParty*> PartyMap;

#endif
