#ifndef _CNPC_
#define _CNPC_

#include <string.h>

#include "CCharacter.h"

class CNPC: public CCharacter
{
	WORD m_wIndex;
	int m_nShape;
	int m_nHtml;

	static std::map<int, CNPC*> g_mNPC;
	static std::mutex g_mxNPC;

public:
	/**
		Basic constructor for NPC.
		Assigns macro values from InitNPC.xml.
		\param desc Description struct loaded from InitNPC.xml
	*/
	CNPC(NPC_DESC& desc);

	/**
		\return File index linked to e.pk.
		Example: if X is returned, could be used to open e.pk s00000X.dat
	*/
	int GetHTML() { return m_nHtml; }

	/**
		Loads NPC from InitNPC.xml.
		Should be called <b>only</b> at server start.
		\return false if bad syntax error, true otherwise
	*/
	static bool LoadNPC();

	/**
		Unloads NPC and deallocates its memory.
		Should be called <b>only</b> at server close.
	*/
	static void UnloadNPC();

	/** 
		Adds NPC to world NPC list so it can 
		be found by ID or iterated through.
		\param pNPC NPC to add.
	*/
	static void Add(CNPC* pNPC);

	/**
		Removes NPC from world NPC list so it can 
		no longer be found by ID or iterated through.
		\param pNPC NPC to remove.
	*/
	static void Remove(CNPC* pNPC);

	/**
		Grants m_Access, so it is a <b>must</b> to Release it after usage.
		\param nID Game ID identifier.
		\return NPC with certain ID.
	*/
	static CNPC* FindNPC(int nID);

	/**
		Generates packet with information how NPC looks and behave.
		It is required to distribute this packet to clients each time they appears in sight.
		\param bHero Dummy.
		\return Generated packet ready to be sent.
	*/
	Packet GenerateCreatePacket(bool bHero=false);

	/**
		Generates pet item information.
		Since NPC does not use pets, it always returns empty, invalid packet.
		\return Empty packet.
	*/
	Packet GeneratePetPacket();

	/**
		Generates information about NPC deletion.
		Prepares packet for distribution among clients that disappear from its sight.
		\return Generated packet ready to be sent.
	*/
	Packet GenerateDeletePacket();

	/**
		Generates information about NPC move.
		Since NPC does not move, it always returns empty, invalid packet.
		\param byType Dummy.
		\param byX Dummy.
		\param byY Dummy.
		\param byZ Dummy.
		\return Empty packet.
	*/
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	/**
		Sends packet to socket contained by NPC.
		Since NPC does not have socket, it does nothing.
		\param packet Packet to be sent (dummy).
	*/
	void SendPacket(Packet& packet) {}

	/**
		Will get executed once a second once it's needed.
		Should be called inside TickAll when needed.
		\return false if instance should be deleted, true otherwise
	*/
	bool Tick() { return true; }
};

typedef std::map<int, CNPC*> NPCMap;
typedef std::list<CNPC*> NPCList;

#endif
