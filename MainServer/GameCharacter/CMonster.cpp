#include "CMonster.h"

#include "Monster/CMonsterReal.h"

CMonster::CMonster(CMonsterInfo *pMacro, int nX, int nY)
{
	m_pMacro = pMacro;
	m_nX = nX;
	m_nY = nY;
}

CMonster::~CMonster()
{
	while (m_Access.IsBusy()) {
		printf("CMonster::~CMonster: Monster is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

CMonster* CMonster::CreateMonster(WORD wIndex, int nX, int nY)
{
	CMonsterInfo* pMacro = (CMonsterInfo*) CMacroDB::FindMacro(CMacro::MT_MONSTER, wIndex);
	if (!pMacro) {
		printf(KRED "Wrong monster index: %d\n" KNRM, wIndex);
		return NULL;
	}

	CMonster* pMonster=NULL;

	switch (pMacro->m_byRace)
	{
		default:
			printf(KRED "Unknown monster race (%d).\n" KNRM, pMacro->m_byRace);
			pMonster = new CMonsterReal(pMacro, nX, nY);
			break;
	}

	return pMonster;
}

Packet CMonster::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_CREATEMONSTER;

	char *end = CSocket::WritePacket(packet.data, "wdddwddIIsbdsIIb", 
		GetIndex(),
		GetID(),
		GetX(),
		GetY(),
		GetDir(),
		100, //curhp
		100, //maxhp
		(__int64)0, //gstate
		(__int64)0, //m64state
		"gname",
		GetRace(),
		0, // gid
		"gpos",
		(__int64)0, //gstateex
		(__int64)0, //mstateex
		0 //level
		); 

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CMonster::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_REMOVEMONSTER;

	char *end = CSocket::WritePacket(packet.data, "d", m_nID);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CMonster::GeneratePetPacket()
{
	Packet packet;
	packet.wSize=0;

	return packet;
}

Packet CMonster::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	packet.wSize=0;

	return packet;
}