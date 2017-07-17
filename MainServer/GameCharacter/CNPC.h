#ifndef _CNPC_
#define _CNPC_

#include <string.h>

#include "CCharacter.h"

/**
	Class representation of NPC such as merchants and more.
*/
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
		Example: if X is returned, could be used to open e.pk s00000X.dat
		\return File index linked to e.pk.
	*/
	int GetHTML() const { return m_nHtml; }

	/**
		Loads all NPCs from InitNPC.xml.
		Should be called <b>only</b> once at server start.
		\return false if bad syntax error, true otherwise
	*/
	static bool LoadNPC();

	/**
		Unloads all NPCs and deallocates its memory.
		Should be called <b>only</b> once at server close.
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
		Find NPC with certain ID.
		Grants m_Access, so it is a <b>must</b> to Release it after usage.
		\param nID Game ID identifier.
		\return NPC with certain ID.
	*/
	static CNPC* FindNPC(int nID);

	/**
		Generates packet with information how NPC looks and behave.
		It is required to distribute this packet to clients each time they appear in sight.
		\param bHero Neither true or false does not affect NPC.
		\return Generated packet ready to be sent.
	*/
	Packet GenerateCreatePacket(bool bHero=false);

	/**
		Generates information about NPC deletion.
		Prepares packet for distribution among clients that disappear from its sight.
		\return Generated packet ready to be sent.
	*/
	Packet GenerateDeletePacket();
};

typedef std::map<int, CNPC*> NPCMap;
typedef std::list<CNPC*> NPCList;

#endif
