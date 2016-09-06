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
	CNPC(NPC_DESC& desc);

	int GetHTML() { return m_nHtml; }

	static bool LoadNPC();
	static void UnloadNPC();
	static void Add(CNPC* pNPC);
	static void Remove(CNPC* pNPC);

	// Remember to call m_Access.Release() on found NPC.
	static CNPC* FindNPC(int nID);

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GeneratePetPacket();
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	void SendPacket(Packet& packet) {}

	void Tick() {}
};

typedef std::map<int, CNPC*> NPCMap;
typedef std::list<CNPC*> NPCList;

#endif