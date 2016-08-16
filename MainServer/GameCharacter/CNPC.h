#ifndef _CNPC_
#define _CNPC_

#include <string.h>

#include "CCharacter.h"

class CNPC: public CCharacter
{
	WORD m_wIndex;
	int m_nShape;
	int m_nHtml;

public:
	CNPC(NPC_DESC& desc);

	static bool LoadNPC();

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	void SendPacket(Packet& packet) {}
};

#endif