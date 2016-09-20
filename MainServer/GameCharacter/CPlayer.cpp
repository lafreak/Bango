#include <Socket/CSocket.h>
#include "../Socket/CDBSocket.h"
#include "CPlayer.h"
#include "../CServer.h"
#include "../Item/CItemPet.h"

PlayerMap CPlayer::g_mPlayer;
std::mutex CPlayer::g_mxPlayer;

CPlayer::CPlayer(int nCID, D2S_LOADPLAYER_DESC& desc): CCharacter()
{
	m_nCID = nCID;

	m_nAID = desc.nAID;
	m_nPID = desc.nPID;
	m_szName = std::string(desc.szName);
	m_byClass = desc.byClass;
	m_byJob = desc.byJob;
	m_byLevel = desc.byLevel;
	m_wStr = desc.wStats[P_STR];
	m_wHth = desc.wStats[P_HTH];
	m_wInt = desc.wStats[P_INT];
	m_wWis = desc.wStats[P_WIS];
	m_wDex = desc.wStats[P_DEX];
	m_wCurHP = desc.wCurHP;
	m_wCurMP = desc.wCurMP;
	m_n64Exp = desc.n64Exp;
	m_wPUPoint = desc.wPUPoint;
	m_wSUPoint = desc.wSUPoint;
	m_wContribute = desc.wContribute;
	m_nAnger = desc.nAnger;
	m_nX = desc.nX;
	m_nY = desc.nY;
	m_nZ = desc.nZ;

	m_n64WearState = 0;
	m_byTrigramLevel = 0;

	m_byShortcutState = 0;

	memset(m_Gear, 0, sizeof(int) * GEAR_NUM);
	memset(m_GearIndex, 0, sizeof(WORD) * GEAR_VISIBLE_NUM);

	m_byKind = CK_PLAYER;
}

CPlayer::~CPlayer()
{
	EmptyInven();

	CMap::Remove(this);
	CPlayer::Remove(this);

	SaveAllProperty();

	WriteInSight(S2C_REMOVEPLAYER, "d", m_nID);

	while (m_Access.IsBusy()) {
		printf("CPlayer::~CPlayer: Player is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

void CPlayer::IntoInven(CItem* pItem)
{
	m_mxItem.lock();

	if (m_mItem.find(pItem->GetIID()) == m_mItem.end())
		m_mItem[pItem->GetIID()] = pItem;

	m_mxItem.unlock();
}

void CPlayer::OutofInven(CItem *pItem)
{
	m_mxItem.lock();

	ItemMap::iterator it = m_mItem.find(pItem->GetIID());
	if (it != m_mItem.end())
		m_mItem.erase(it);

	m_mxItem.unlock();
}

void CPlayer::EmptyInven()
{
	m_mxItem.lock();

	for (auto& a: m_mItem)
		delete a.second;

	m_mxItem.unlock();
}

CItem* CPlayer::FindItem(WORD wIndex, BYTE byOwnership)
{
	CItem *pItem=NULL;

	m_mxItem.lock();

	for (ItemMap::iterator it = m_mItem.begin(); it != m_mItem.end(); it++)
	{
		bool isOwnership = byOwnership == IFO_ANY ? true : 
						((it->second->IsState(ITEM_OWN)) && byOwnership == IFO_MUSTOWN ? true : 
						(!(it->second->IsState(ITEM_OWN)) && byOwnership == IFO_CANTOWN ? true : false));


		if (isOwnership && it->second->GetIndex() == wIndex) {
			pItem = it->second;
			pItem->m_Access.Grant();
			break;
		}
	}

	m_mxItem.unlock();

	return pItem;
}

CItem* CPlayer::FindItemByIID(int nIID)
{
	CItem *pItem = NULL;

	m_mxItem.lock();

	if (m_mItem.find(nIID) != m_mItem.end()) {
		pItem = m_mItem[nIID];
		pItem->m_Access.Grant();
	}

	m_mxItem.unlock();

	return pItem;
}

void CPlayer::OnPutOnGear(CItem *pItem)
{
	switch (pItem->GetMacro()->m_bySubClass)
	{
		case ISC_SWORD:
		case ISC_WAND:
		case ISC_BOW:
		case ISC_DAGGER:
			m_Gear[WS_WEAPON] = pItem->GetIID();
			m_GearIndex[WS_WEAPON] = pItem->GetIndex();
			AddWState(WS_WEAPON);
			break;

		case ISC_SWORD2HAND:
			m_Gear[WS_WEAPON] = pItem->GetIID();
			m_GearIndex[WS_WEAPON] = pItem->GetIndex();
			AddWState(WS_WEAPON);
			AddWState(WS_2HANDWEAPON);
			break;
		
		case ISC_SHIELD:
			m_Gear[WS_SHIELD] = pItem->GetIID();
			m_GearIndex[WS_SHIELD] = pItem->GetIndex();
			AddWState(WS_SHIELD);
			break;

		case ISC_HELMET:
			m_Gear[WS_HELMET] = pItem->GetIID();
			m_GearIndex[WS_HELMET] = pItem->GetIndex();
			AddWState(WS_HELMET);
			break;

		case ISC_UPPERARMOR:
			m_Gear[WS_UPPERARMOR] = pItem->GetIID();
			m_GearIndex[WS_UPPERARMOR] = pItem->GetIndex();
			AddWState(WS_UPPERARMOR);
			break;

		case ISC_LOWERARMOR:
			m_Gear[WS_LOWERARMOR] = pItem->GetIID();
			m_GearIndex[WS_LOWERARMOR] = pItem->GetIndex();
			AddWState(WS_LOWERARMOR);
			break;

		case ISC_GAUNTLET:
			m_Gear[WS_GAUNTLET] = pItem->GetIID();
			m_GearIndex[WS_GAUNTLET] = pItem->GetIndex();
			AddWState(WS_GAUNTLET);
			break;

		case ISC_BOOTS:
			m_Gear[WS_BOOTS] = pItem->GetIID();
			m_GearIndex[WS_BOOTS] = pItem->GetIndex();
			AddWState(WS_BOOTS);
			break;

		case ISC_YINYANGMIRROR:
			m_Gear[WS_MIRROR] = pItem->GetIID();
			AddWState(WS_MIRROR);
			break;

		case ISC_TAEGEUK:
			m_Gear[WS_TAEGEUK] = pItem->GetIID();
			AddWState(WS_TAEGEUK);
			break;

		case ISC_TRIGRAM1:
			m_Gear[WS_TRIGRAM1] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM1);
			break;

		case ISC_TRIGRAM2:
			m_Gear[WS_TRIGRAM2] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM2);
			break;

		case ISC_TRIGRAM3:
			m_Gear[WS_TRIGRAM3] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM3);
			break;

		case ISC_TRIGRAM4:
			m_Gear[WS_TRIGRAM4] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM4);
			break;

		case ISC_TRIGRAM5:
			m_Gear[WS_TRIGRAM5] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM5);
			break;

		case ISC_TRIGRAM6:
			m_Gear[WS_TRIGRAM6] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM6);
			break;

		case ISC_TRIGRAM7:
			m_Gear[WS_TRIGRAM7] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM7);
			break;

		case ISC_TRIGRAM8:
			m_Gear[WS_TRIGRAM8] = pItem->GetIID();
			m_byTrigramLevel = pItem->GetLevel();
			AddWState(WS_TRIGRAM8);
			break;

		case ISC_EGG:
			m_Gear[WS_PET] = pItem->GetIID();
			m_GearIndex[WS_PET] = pItem->GetIndex();
			AddWState(WS_PET);
			break;

		case ISC_RING:
			m_Gear[WS_RING] = pItem->GetIID();
			AddWState(WS_RING);
			break;

		case ISC_NECKLACE:
			m_Gear[WS_NECKLACE] = pItem->GetIID();
			AddWState(WS_NECKLACE);
			break;

		case ISC_TRINKET:
			m_Gear[WS_TRINKET] = pItem->GetIID();
			AddWState(WS_TRINKET);
			break;

		case ISC_RESISTNECKLACE2:
			m_Gear[WS_RESISTNECKLACE2] = pItem->GetIID();
			AddWState(WS_RESISTNECKLACE2);
			break;
	}
}

void CPlayer::OnPutOffGear(CItem *pItem)
{
	switch (pItem->GetMacro()->m_bySubClass)
	{
		case ISC_SWORD:
		case ISC_WAND:
		case ISC_BOW:
		case ISC_DAGGER:
			m_Gear[WS_WEAPON] = 0;
			m_GearIndex[WS_WEAPON] = 0;
			SubWState(WS_WEAPON);
			break;

		case ISC_SWORD2HAND:
			m_Gear[WS_WEAPON] = 0;
			m_GearIndex[WS_WEAPON] = 0;
			SubWState(WS_WEAPON);
			SubWState(WS_2HANDWEAPON);
			break;
		
		case ISC_SHIELD:
			m_Gear[WS_SHIELD] = 0;
			m_GearIndex[WS_SHIELD] = 0;
			SubWState(WS_SHIELD);
			break;

		case ISC_HELMET:
			m_Gear[WS_HELMET] = 0;
			m_GearIndex[WS_HELMET] = 0;
			SubWState(WS_HELMET);
			break;

		case ISC_UPPERARMOR:
			m_Gear[WS_UPPERARMOR] = 0;
			m_GearIndex[WS_UPPERARMOR] = 0;
			SubWState(WS_UPPERARMOR);
			break;

		case ISC_LOWERARMOR:
			m_Gear[WS_LOWERARMOR] = 0;
			m_GearIndex[WS_LOWERARMOR] = 0;
			SubWState(WS_LOWERARMOR);
			break;

		case ISC_GAUNTLET:
			m_Gear[WS_GAUNTLET] = 0;
			m_GearIndex[WS_GAUNTLET] = 0;
			SubWState(WS_GAUNTLET);
			break;

		case ISC_BOOTS:
			m_Gear[WS_BOOTS] = 0;
			m_GearIndex[WS_BOOTS] = 0;
			SubWState(WS_BOOTS);
			break;

		case ISC_YINYANGMIRROR:
			m_Gear[WS_MIRROR] = 0;
			SubWState(WS_MIRROR);
			break;

		case ISC_TAEGEUK:
			m_Gear[WS_TAEGEUK] = 0;
			SubWState(WS_TAEGEUK);
			break;

		case ISC_TRIGRAM1:
			m_Gear[WS_TRIGRAM1] = 0;
			SubWState(WS_TRIGRAM1);
			break;

		case ISC_TRIGRAM2:
			m_Gear[WS_TRIGRAM2] = 0;
			SubWState(WS_TRIGRAM2);
			break;

		case ISC_TRIGRAM3:
			m_Gear[WS_TRIGRAM3] = 0;
			SubWState(WS_TRIGRAM3);
			break;

		case ISC_TRIGRAM4:
			m_Gear[WS_TRIGRAM4] = 0;
			SubWState(WS_TRIGRAM4);
			break;

		case ISC_TRIGRAM5:
			m_Gear[WS_TRIGRAM5] = 0;
			SubWState(WS_TRIGRAM5);
			break;

		case ISC_TRIGRAM6:
			m_Gear[WS_TRIGRAM6] = 0;
			SubWState(WS_TRIGRAM6);
			break;

		case ISC_TRIGRAM7:
			m_Gear[WS_TRIGRAM7] = 0;
			SubWState(WS_TRIGRAM7);
			break;

		case ISC_TRIGRAM8:
			m_Gear[WS_TRIGRAM8] = 0;
			SubWState(WS_TRIGRAM8);
			break;

		case ISC_EGG:
			m_Gear[WS_PET] = 0;
			m_GearIndex[WS_PET]=0;
			SubWState(WS_PET);
			break;

		case ISC_RING:
			m_Gear[WS_RING] = 0;
			SubWState(WS_RING);
			break;

		case ISC_NECKLACE:
			m_Gear[WS_NECKLACE] = 0;
			SubWState(WS_NECKLACE);
			break;

		case ISC_TRINKET:
			m_Gear[WS_TRINKET] = 0;
			SubWState(WS_TRINKET);
			break;

		case ISC_RESISTNECKLACE2:
			m_Gear[WS_RESISTNECKLACE2] = 0;
			SubWState(WS_RESISTNECKLACE2);
			break;
	}

	if (!IsAnyTrigramState())
		m_byTrigramLevel=0;
}

WORD CPlayer::GetReqPU(BYTE *byStats)
{
	WORD wReqPU=0;

	if (m_byClass == PC_KNIGHT)
		wReqPU += FIND_NEED_PU_EX(m_wStr, byStats[P_STR]);
	else
		wReqPU += FIND_NEED_PU(m_wStr, byStats[P_STR]);

	if (m_byClass == PC_MAGE)
		wReqPU += FIND_NEED_PU_EX(m_wInt, byStats[P_INT]);
	else
		wReqPU += FIND_NEED_PU(m_wInt, byStats[P_INT]);

	if (m_byClass == PC_ARCHER || m_byClass == PC_THIEF)
		wReqPU += FIND_NEED_PU_EX(m_wDex, byStats[P_DEX]);
	else
		wReqPU += FIND_NEED_PU(m_wDex, byStats[P_DEX]);

	wReqPU += FIND_NEED_PU(m_wHth, byStats[P_HTH]);
	wReqPU += FIND_NEED_PU(m_wWis, byStats[P_WIS]);

	return wReqPU;
}

bool CPlayer::WriteAll(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;

	g_mxPlayer.lock();

	for (auto& a: g_mPlayer)
		a.second->SendPacket(packet);

	g_mxPlayer.unlock();

	return true;
}

bool CPlayer::Write(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	send(m_nCID, (char*)&packet, packet.wSize, MSG_NOSIGNAL);

	return true;
}

void CPlayer::SendPacket(Packet& packet)
{
	if (packet.wSize > 0)
		send(m_nCID, (char*)&packet, packet.wSize, MSG_NOSIGNAL);
}

Packet CPlayer::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	BYTE byUnknownV=0;
	int nUn2=0;
	int nUn3=0;
	BYTE byUn4=0; // level?

	BYTE byClass=m_byClass;

	if (bHero)
		byClass |= GAME_HERO;

	packet.byType = S2C_CREATEPLAYER;
	//char *end = CSocket::WritePacket(packet.data, "dsbdddwIwwwwwwwwbbIssdbdddIIwwwwwwwwwbddb", 
	char *end = CSocket::WritePacket(packet.data, "dsbdddwIwwwwwwwwbbIssdbdddIIbddb", 
		m_nID, 
		m_szName.c_str(), 
		byClass, 
		m_nX, 
		m_nY, 
		m_nZ, 
		m_wDir, 
		m_n64GState,
		m_GearIndex[WS_WEAPON],
		m_GearIndex[WS_SHIELD],
		m_GearIndex[WS_HELMET],
		m_GearIndex[WS_UPPERARMOR],
		m_GearIndex[WS_LOWERARMOR],
		m_GearIndex[WS_GAUNTLET],
		m_GearIndex[WS_BOOTS],
		0,//m_GearIndex[WS_PET], // no effect?
		m_byFace, 
		m_byHair, 
		m_n64MState, 
		m_szGuildClass.c_str(), 
		m_szGuildName.c_str(), 
		m_nGID, 
		m_byFlag, 
		m_nFlagItem, 
		m_nHonorGrade, 
		m_nHonorOption, 
		m_n64GStateEx, 
		m_n64MStateEx, 

		byUnknownV,
		nUn2,
		nUn3,
		byUn4
		);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CPlayer::GeneratePetPacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_ATTACH_PET;

	char *end = CSocket::WritePacket(packet.data, "dwdb", m_nID, m_GearIndex[WS_PET], m_Gear[WS_PET], 
		(m_GearIndex[WS_PET] >= 2004 && m_GearIndex[WS_PET] <= 2007) ? 1 : 0);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CPlayer::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_REMOVEPLAYER;

	char *end = CSocket::WritePacket(packet.data, "d", m_nID);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CPlayer::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType == 0 ? S2C_MOVEPLAYER_ON : S2C_MOVEPLAYER_END;

	char *end = CSocket::WritePacket(packet.data, "dbbb", m_nID, byX, byY, byZ);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

void CPlayer::Add(CPlayer *pPlayer)
{
	g_mxPlayer.lock();

	if (g_mPlayer.find(pPlayer->GetID()) == g_mPlayer.end())
		g_mPlayer[pPlayer->GetID()] = pPlayer;
	else
		printf(KRED "CPlayer::Add: Same player ingame.\n" KNRM);

	g_mxPlayer.unlock();
}

void CPlayer::Remove(CPlayer *pPlayer)
{
	g_mxPlayer.lock();

	PlayerMap::iterator it = g_mPlayer.find(pPlayer->GetID());
	if (it != g_mPlayer.end())
		g_mPlayer.erase(it);

	g_mxPlayer.unlock();
}

CPlayer* CPlayer::FindPlayer(int nID)
{
	CPlayer *pPlayer=NULL;

	g_mxPlayer.lock();

	if (g_mPlayer.find(nID) != g_mPlayer.end()) {
		pPlayer = g_mPlayer[nID];
		pPlayer->m_Access.Grant();
	}

	g_mxPlayer.unlock();

	return pPlayer;
}

CPlayer* CPlayer::FindPlayerByName(char* szName)
{
	CPlayer *pPlayer=NULL;

	g_mxPlayer.lock();

	for (auto& a: g_mPlayer) {
		if (!strcmp(szName, a.second->GetName().c_str())) {
			pPlayer = a.second;
			pPlayer->m_Access.Grant();
			break;
		}
	}

	g_mxPlayer.unlock();

	return pPlayer;
}

void CPlayer::Process(Packet packet)
{
	printf("Incoming C2S packet: [%u]\n", (BYTE)packet.byType);
	for (int i = 0; i < packet.wSize; i++)
		printf("%u ", (BYTE)((char*)&packet)[i]);
	printf("\n");


	switch (packet.byType)
	{
		case C2S_START:
		{
			BYTE byUnknown=0;
			int nHeight=0;
			CSocket::ReadPacket(packet.data, "bd", &byUnknown, &nHeight);
			//printf("byUnknown: %d, nHeight: %d\n", byUnknown, nHeight);

			//if (nHeight != m_nZ)
			//	printf(KRED "Client map height[%d] differs from player Z[%d].\n" KNRM, nHeight, m_nZ);

			GameStart();

			break;
		}

		case C2S_RESTART:
		{
			BYTE byMessage=0;
			CSocket::ReadPacket(packet.data, "b", &byMessage);

			if (byMessage)
				Write(S2C_ANS_RESTART, "b", 1);
			else
				GameRestart();

			break;
		}

		case C2S_GAMEEXIT:
		{
			Write(S2C_ANS_GAMEEXIT, "b", 1);
			break;
		}

		case C2S_MOVE_ON:
		case C2S_MOVE_END:
		{
			char byX=0;
			char byY=0;
			char byZ=0;
			CSocket::ReadPacket(packet.data, "bbb", &byX, &byY, &byZ);

			Lock();
			if (CanMove())
				OnMove(byX, byY, byZ, packet.byType == C2S_MOVE_ON ? 0 : 1);
			Unlock();
			break;
		}

		case C2S_CHATTING:
		{
			char* szMsg=NULL;
			CSocket::ReadPacket(packet.data, "s", &szMsg);

			ProcessMsg(szMsg);
			
			break;
		}

		case C2S_REST:
		{
			BYTE byType=0;
			CSocket::ReadPacket(packet.data, "b", &byType);

			Rest(byType);

			break;
		}

		case C2S_UPDATEPROPERTY:
		{
			BYTE byStats[5]={0,};
			CSocket::ReadPacket(packet.data, "bbbbb", &byStats[P_STR], &byStats[P_HTH], &byStats[P_INT], &byStats[P_WIS], &byStats[P_DEX]);

			WORD wTotalReqPU = GetReqPU(byStats);

			//printf("wTotalReqPU: %d PUPoint: %d\n", wTotalReqPU, m_wPUPoint);

			if (wTotalReqPU > m_wPUPoint || wTotalReqPU <= 0)
				break;

			Lock();

			UpdateProperty(P_STR, byStats[P_STR]);
			UpdateProperty(P_HTH, byStats[P_HTH]);
			UpdateProperty(P_INT, byStats[P_INT]);
			UpdateProperty(P_WIS, byStats[P_WIS]);
			UpdateProperty(P_DEX, byStats[P_DEX]);

			m_wPUPoint -= wTotalReqPU;

			Unlock();

			CPlayer::Write(S2C_UPDATEPROPERTY, "bw", P_PUPOINT, m_wPUPoint);
			CDBSocket::Write(S2D_UPDATEPROPERTY, "dwwwwww", m_nPID, m_wStr, m_wHth, m_wInt, m_wWis, m_wDex, m_wPUPoint);

			break;
		}

		case C2S_TELEPORT:
		{
			BYTE byAnswer=0;
			int nZ=0;
			CSocket::ReadPacket(packet.data, "bd", &byAnswer, &nZ);

			OnTeleport(byAnswer, nZ);
			break;
		}

		case C2S_ASKNPC:
		{
			int nID=0;
			CSocket::ReadPacket(packet.data, "d", &nID);

			auto pNPC = CNPC::FindNPC(nID);
			if (!pNPC) break;

			Write(S2C_SENDHTML, "d", pNPC->GetHTML());

			pNPC->m_Access.Release();

			break;
		}

		case C2S_TRASHITEM:
		{
			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			CItem *pItem = FindItemByIID(nIID);
			if (pItem) {
				if (!pItem->CanTrash(this)) {
					pItem->m_Access.Release();
					break;
				}

				if (RemoveItem(pItem))
					pItem->m_Access.Release();
			}

			break;
		}

		case C2S_USEITEM:
		{
			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			CItem *pItem = FindItemByIID(nIID);
			if (pItem) {
				if (UseItem(pItem))
					pItem->m_Access.Release();
			}

			break;
		}

		case C2S_PUTONITEM:
		{
			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			CItem *pItem = FindItemByIID(nIID);
			if (pItem) {
				PutOnItem(pItem);
				pItem->m_Access.Release();
			}

			break;
		}

		case C2S_PUTOFFITEM:
		{
			int nIID=0;
			CSocket::ReadPacket(packet.data, "d", &nIID);

			CItem *pItem = FindItemByIID(nIID);
			if (pItem) {
				PutOffItem(pItem);
				pItem->m_Access.Release();
			}

			break;
		}

		case C2S_PLAYER_ANIMATION:
		{
			int nID=0;
			BYTE byAnim=0;
			CSocket::ReadPacket(packet.data, "db", &nID, &byAnim);

			WriteInSight(S2C_PLAYER_ANIMATION, "db", GetID(), byAnim);

			break;
		}

		case C2S_SHORTCUT:
		{
			BYTE byType=0;
			CSocket::ReadPacket(packet.data, "b", &byType);

			if (byType == 0 && m_byShortcutState != 0) {
				printf(KRED "Trying to load shortcut for the second time.\n" KNRM);
				break;
			}

			if (byType == 1 && m_byShortcutState != 1) {
				printf(KRED "Trying to save shortcut for the second time.\n" KNRM);
				break;
			}

			m_byShortcutState++;

			CDBSocket::Write(S2D_SHORTCUT, "ddm", GetCID(), GetPID(), packet.data, packet.wSize - (packet.data - (char*)&packet));

			break;
		}

		case C2S_DROPITEM:
		{
			int x = m_nX + 10;
			int y = m_nY + 10;

			int nIID;
			int count;

			CItem* pItem = NULL;
			CItem* pDropItem = NULL;

			CSocket::ReadPacket(packet.data, "dd", &nIID, &count);
      
			pItem = FindItemByIID(nIID);

			if (pItem != NULL)
			{
				pDropItem = CItem::CreateItem(pItem, count, x, y);

                if (pDropItem)
                {
                	CMap::AddItem(pDropItem);

				if (RemoveItem(pItem, count, TL_DROP))
						pItem->m_Access.Release();
				
					WriteInSight(S2C_CREATEITEM, "wddddd", pDropItem->GetIndex(), pDropItem->GetIID(), pDropItem->GetX(), pDropItem->GetY(), -1);

					pDropItem->Lock();
					pDropItem->SetGState(1);
					pDropItem->Unlock();

					pDropItem->SetTimer();
		        }
		    }

		    break;  
		}

		case C2S_PICKUPITEM:
		{
			int itemID, nx, nz = 0;

			CSocket::ReadPacket(packet.data, "ddd", &itemID, &nx, &nz);
		
			CItem *pItem = CItem::FindItemByIID(itemID);

            if (pItem && GetTickCount() - m_Time >= 500)
            {
            	WriteInSight(S2C_REMOVEITEM, "d", pItem->GetIID());
            	CMap::RemoveItem(pItem);
            	InsertItem(pItem);

            	pItem->m_Access.Release();

            	m_Time = GetTickCount();
            }

            break;
		}
		/*

		case C2S_ASKPARTY:
		{
			int nID = 0;
			Packet packet;

			CPlayer* pPlayer;

			CSocket::ReadPacket(packet.data, "d", &nID);

			pPlayer = FindPlayer(nID);

			packet = UpdateParty(pPlayer);

			if(pPlayer)
				pPlayer->Write(S2C_ASKPARTY, "d", m_nPID);

			Write(S2C_ASKPARTY, "d", pPlayer->GetPID());

			SendPacket(packet); 

			pPlayer->m_Access.Release();

		}	
		*/	
	}
}
/*

Packet CPlayer::UpdateParty(CPlayer* pPlayer)
{
	Packet packet;

	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_UPDATEPARTY;

	char *end = CSocket::WritePacket(packet.data, "bsbbb",
		pPlayer->GetPID(), pPlayer->GetName(), 1, pPlayer->GetLevel(), pPlayer->GetCurHP());

	packet.wSize = end - ((char*)&packet);

	return packet;
}
*/
	
void CPlayer::OnLoadPlayer()
{
	Lock();

	m_Time = GetTickCount();

	m_byGrade = 1;
	m_szGuildName = "\0";
	m_byGRole = 1;
	m_wDefense = 90;
	m_byAbsorb = 5;

	m_szGuildClass = "\0";
	m_nGID = 0;
	m_byFlag = 0;
	m_nFlagItem = 0;
	m_nHonorGrade = 0;
	m_nHonorOption = 0;

	m_wDir = 0;

	Write(S2C_PROPERTY, "bsbwwwwwwwwwwwwwbIwwwwwwbbbbbd", 
			m_byGrade, 
			m_szGuildName.c_str(), 
			m_byGRole, 
			m_wContribute, 
			m_wStr, 
			m_wHth, 
			m_wInt, 
			m_wWis, 
			m_wDex,
			m_wCurHP, 
			GetMaxHP(),
			m_wCurMP, 
			GetMaxMP(),
			GetHit(),
			GetDodge(),
			m_wDefense, 
			m_byAbsorb,
			m_n64Exp, 
			GetMinAttack(),
			GetMaxAttack(),
			GetMinMagic(),
			GetMaxMagic(),
			m_wPUPoint, 
			m_wSUPoint, 
			GetResist(RT_FIRE),
			GetResist(RT_ICE),
			GetResist(RT_LITNING),
			GetResist(RT_CURSE), 
			GetResist(RT_PALSY),
			m_nAnger);

	//printf("S2C_PROPERTY sent.\n");

	WORD wTime=1200;

	// Moved to GameStart
	//CMap::Add(this);
	//CPlayer::Add(this);

	Write(S2C_ANS_LOAD, "wdd", wTime, m_nX, m_nY);

	//printf("S2C_ANS_LOAD sent.\n");

	Unlock();
}

void CPlayer::OnLoadItems(char *p)
{
	//printf("CPlayer::OnLoadItems\n");
	
	BYTE byCount=0;
	p = CSocket::ReadPacket(p, "b", &byCount);

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));
	char* pBegin = (char*)&buffer;
	char* pEnd = pBegin;

	pEnd = CSocket::WritePacket(pEnd, "b", byCount);

	for (BYTE i = 0; i < byCount; i++)
	{
		ITEMINFO_DESC desc;
		memset(&desc, 0, sizeof(ITEMINFO_DESC));

		p = CSocket::ReadPacket(p, "dwddbbbbbbbbbbwwwwbbbbbbbbbbwdd",
			&desc.nIID,
			&desc.wIndex,
			&desc.nNum,
			&desc.nInfo,
			&desc.byPrefix,
			&desc.byCurEnd,
			&desc.byMaxEnd,
			&desc.byXAttack,
			&desc.byXMagic,
			&desc.byXDefense,
			&desc.byXHit,
			&desc.byXDodge,
			&desc.byExplosiveBlow,
			&desc.fuse.byLevel,
			&desc.fuse.wMeele,
			&desc.fuse.wMagic,
			&desc.fuse.wDefense,
			&desc.fuse.wAbsorb,
			&desc.fuse.byDodge,
			&desc.fuse.byHit,
			&desc.fuse.byHP,
			&desc.fuse.byMP,
			&desc.fuse.byStats[P_STR],
			&desc.fuse.byStats[P_HTH],
			&desc.fuse.byStats[P_INT],
			&desc.fuse.byStats[P_WIS],
			&desc.fuse.byStats[P_DEX],
			&desc.byShot,
			&desc.wPerforation,
			&desc.nGongLeft,
			&desc.nGongRight);

		CItem *pItem = CItem::CreateItem(desc);
		if (!pItem) continue;

		IntoInven(pItem);
		

		if (pItem->IsState(ITEM_PUTON)) {
			if (!pItem->CanUse(this)) 
			{
				CDBSocket::Write(S2D_PUTOFFITEM, "d", pItem->GetIID());
				pItem->Lock();
				pItem->SubState(ITEM_PUTON);
				pItem->Unlock();
			}
			else
			{
				Lock();
				OnPutOnGear(pItem);
				Unlock();
			}
		}

		pEnd = CSocket::WritePacket(pEnd, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbwdd",
				desc.wIndex,
				desc.nIID,
				desc.byPrefix,
				pItem->GetInfo(),
				desc.nNum,
				desc.byMaxEnd,
				desc.byCurEnd,
				(BYTE)0, // bySetGem
				desc.byXAttack,
				desc.byXMagic,
				desc.byXDefense,
				desc.byXHit,
				desc.byXDodge,
				(WORD)0, // wProtectNum
				desc.byExplosiveBlow,
				(BYTE)0, // byCorrectionAddNum
				(BYTE)0, // 
				(BYTE)0, // byRemainingSeconds??
				(BYTE)0, // byRemainingMinutes??
				(DWORD)0, // byRemainingHours??

				desc.fuse.byLevel,
				desc.fuse.wMeele,
				desc.fuse.wMagic,
				desc.fuse.wDefense,
				desc.fuse.wAbsorb,
				desc.fuse.byDodge,
				desc.fuse.byHit,
				desc.fuse.byHP,
				desc.fuse.byMP,
				desc.fuse.byStats[P_STR],
				desc.fuse.byStats[P_HTH],
				desc.fuse.byStats[P_INT],
				desc.fuse.byStats[P_WIS],
				desc.fuse.byStats[P_DEX],

				desc.byShot,
				desc.wPerforation,
				desc.nGongLeft,
				desc.nGongRight);
	}

	Write(S2C_ITEMINFO, "m", pBegin, pEnd - pBegin);

	//printf("Items loaded.\n");
}

void CPlayer::GameStart()
{
	//printf("CPlayer::GameStart.\n");

	CMap::Add(this);
	CPlayer::Add(this);


	Packet createPacket 	= GenerateCreatePacket();
	Packet createHeroPacket = GenerateCreatePacket(true);
	Packet petPacket		= GeneratePetPacket();

	SendPacket(createHeroPacket);

	CharacterList list;
	CMap::GetCharacterListAround(this, MAX_PLAYER_SIGHT, list);

	for (CharacterList::iterator it = list.begin(); it != list.end(); it++)
	{
		Packet createPacketEx = (*it)->GenerateCreatePacket();
		Packet petPacketEx = 	(*it)->GeneratePetPacket();

		SendPacket(createPacketEx);
		SendPacket(petPacketEx);

		(*it)->m_Access.Release();
	}

	SendPacketInSight(createPacket);
	SendPacketInSight(petPacket);
}

void CPlayer::GameRestart()
{
	auto pClient = CServer::FindClient(m_nCID);
	if (!pClient) {
		printf(KRED "CPlayer::GameRestart: Player cannot find its client.\n" KNRM);
		return;
	}

	//printf("S2D_SELECT_CHARACTER sent.\n");
	CDBSocket::Write(S2D_SELECT_CHARACTER, "d", pClient->GetCID());

	m_Access.Release();

	delete this;

	pClient->Lock();
	pClient->RemovePlayer();
	pClient->Unlock();
	
	pClient->m_Access.Release();
}

bool CPlayer::CanMove()
{
	if (IsGState(CGS_REST | CGS_KO | CGS_FISH))
	{
		//printf("Can't move.\n");

		Write(S2C_MOVEBEFORE, "ddddw", m_nID, m_nX, m_nY, m_nZ, m_wDir);
		return false;
	}

	// CGS_INVISIBLE/CGS_ONPORTAL

	return true;
}

void CPlayer::OnMove(char byX, char byY, char byZ, char byType)
{
	MapInfo mapInfoCur = CMap::GetMapInfo(m_nX, m_nY);
	MapInfo mapInfoDest = CMap::GetMapInfo(m_nX + byX, m_nY + byY);

	if (!mapInfoCur.equalTile(mapInfoDest)) 
	{
		//printf("Player tile changed.\n[%d %d]->[%d %d]\n",
		//	mapInfoCur.wTileX, mapInfoCur.wTileY,
		//	mapInfoDest.wTileX, mapInfoDest.wTileY);

		CMap::Remove(mapInfoCur, this);
		CMap::Add(mapInfoDest, this);
	}

	m_nX += byX;
	m_nY += byY;
	m_nZ += byZ;

	SetDirection(byX, byY);

	Packet createPacket = GenerateCreatePacket();
	Packet petPacket = 	  GeneratePetPacket();
	Packet deletePacket = GenerateDeletePacket();
	Packet movePacket =   GenerateMovePacket(byType, byX, byY, byZ);

	for (int i = mapInfoDest.wTileX-1; i <= mapInfoDest.wTileX+1; i++) {
		for (int j = mapInfoDest.wTileY-1; j <= mapInfoDest.wTileY+1; j++) {
			auto pTile = CMap::GetTile(i, j);
			if (pTile)
				pTile->SendMoveAction(this, byX, byY, createPacket, petPacket, deletePacket, movePacket);
		}
	}
}

void CPlayer::Rest(BYTE byType)
{
	if (byType)
	{
		if (IsGState(CGS_REST))
			return;

		Lock();
		AddGState(CGS_REST);
		Unlock();
		WriteInSight(S2C_ACTION, "dbb", m_nID, AT_REST, byType);
	}
	else
	{
		if (!IsGState(CGS_REST))
			return;

		Lock();
		SubGState(CGS_REST);
		Unlock();
		WriteInSight(S2C_ACTION, "dbb", m_nID, AT_REST, byType);
	}
}

void CPlayer::ProcessMsg(char* szMsg)
{
	if (strlen(szMsg) <= 0) return;

	switch (szMsg[0])
	{
		case '/':
			ChatCommand(szMsg);
			break;

		case '@':
		{
		    if (strstr(szMsg, " ") == NULL)
		    	return;

		    std::string szTemp = szMsg;
		    char *token = strtok(szMsg + 1, " ");

		    CPlayer *pTarget = FindPlayerByName(token);

		    if (pTarget)
		    {
		    	Write(S2C_CHATTING, "ss", m_szName.c_str(), szTemp.c_str());
		    	pTarget->Write(S2C_CHATTING, "ss", m_szName.c_str(), szTemp.c_str());

		    	pTarget->m_Access.Release();
		    }

		    else
		    {
		    	Write(S2C_MESSAGE, "b", MSG_THEREISNOPLAYER);
		    }
		}
		    break;

		default:
			WriteInSight(S2C_CHATTING, "ss", m_szName.c_str(), szMsg);
			break;
	}
}

void CPlayer::ChatCommand(char* szCommand)
{
	std::string szMsg = szCommand;
	char *token = std::strtok(szCommand, " ");

	if (!strcmp(token, "/ride")) {
		token = std::strtok(NULL, " ");

		if (!token)
			return;

		int nIndex = atoi(token);

		WriteInSight(S2C_RIDING, "bdd", 0, m_nID, nIndex);
	}

	else if (!strcmp(token, "/npc")) {
		token = std::strtok(NULL, " ");

		int nShape=0;

		if (token)
			nShape = atoi(token);

		WriteInSight(S2C_REMOVENPC, "d", 150000);
		WriteInSight(S2C_CREATENPC, "dwbdddwId", 150000, 1, nShape, m_nX, m_nY, m_nZ, m_wDir, (__int64)0, (int)0);
	}

	else if (!strcmp(token, "/tp")) {
		token = std::strtok(NULL, " ");

		int nX=0, nY=0, nZ=0;
		if (!token)
			return;

		nX = atoi(token);
		token = std::strtok(NULL, " ");

		if (!token)
			return;

		nY = atoi(token);
		token = std::strtok(NULL, " ");

		if (token)
			nZ = atoi(token);

		Teleport(nX, nY, nZ);
	}

	else if (!strcmp(token, "/vod")) {

		Teleport(360902, 187081, 42140);
	}

	else if(!strcmp(token, "/d2")) {
		Teleport(3188, 3116, 19768);
	}

	else if (!strcmp(token, "/moveto")) {
		token = std::strtok(NULL, "\0");

		if (!token)
			return;

		CPlayer *pPlayer = FindPlayerByName(token);
		if (pPlayer) {
			Teleport(pPlayer->GetX(), pPlayer->GetY(), pPlayer->GetZ());
			pPlayer->m_Access.Release();
		}
	}

	else if (!strcmp(token, "/get")) {
		token = std::strtok(NULL, " ");

		WORD wIndex=0;
		if (!token)
			return;

		wIndex = atoi(token);

		int nNum=1;
		token = std::strtok(NULL, " ");
		if (token)
			nNum = atoi(token);

		InsertItem(wIndex, nNum);
	}

	else if (!strcmp(token, "/notice")) {
		token = std::strtok(NULL, "\0");

		if (token)
			WriteAll(S2C_NOTICE, "s", token);
	}

	else if (!strcmp(token, "/summon")) {
		token = std::strtok(NULL, " ");

		int wIndex=0;

		if (token)
			wIndex = atoi(token);

		CMonster::Summon(wIndex, GetX(), GetY());
	}

	else if (!strcmp(token, "/test")) {
		token = std::strtok(NULL, " ");

		int wIndex=0;

		if (token)
			wIndex = atoi(token);

		for (int i = GetX() - 50; i <= GetX() + 50; i+=5) {
			for (int j = GetY() - 50; j <= GetY() + 50; j+=5) {
				CMonster::Summon(wIndex, i, j);
			}
		}
	}

	else if (!strcmp(token, "/s")) {
		CItem *pItem = FindItem(515);

		if (pItem)
		{
			CPlayer::WriteAll(S2C_CHATTING, "ss", m_szName.c_str(), szMsg.c_str());

			if (RemoveItem(pItem, 1, TL_USE))
				pItem->m_Access.Release();
		}
	}
}

void CPlayer::UpdateProperty(BYTE byProperty, __int64 n64Amount)
{
	if (!n64Amount) return;

	switch (byProperty)
	{
		case P_STR:
		{
			if ((-n64Amount) > m_wStr)
				n64Amount = -m_wStr;

			m_wStr += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwww", P_STR, m_wStr, GetHit(), GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_HTH:
		{
			if ((-n64Amount) > m_wHth)
				n64Amount = -m_wHth;

			m_wHth += n64Amount;

			WORD wMaxHP = GetMaxHP();
			if (m_wCurHP > wMaxHP)
				m_wCurHP = wMaxHP;

			Write(S2C_UPDATEPROPERTY, "bwwww", P_HTH, m_wHth, m_wCurHP, wMaxHP, GetResist(RT_PALSY));
			break;
		}

		case P_INT:
		{
			if ((-n64Amount) > m_wInt)
				n64Amount = -m_wInt;

			m_wInt += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_INT, m_wInt, GetMinMagic(), GetMaxMagic(), GetResist(RT_FIRE), GetResist(RT_ICE), GetResist(RT_LITNING));
			break;
		}

		case P_WIS:
		{
			if ((-n64Amount) > m_wWis)
				n64Amount = -m_wWis;

			m_wWis += n64Amount;

			WORD wMaxMP = GetMaxMP();
			if (m_wCurMP > wMaxMP)
				m_wCurMP = wMaxMP;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_WIS, m_wWis, m_wCurMP, wMaxMP, GetMinMagic(), GetMaxMagic(), GetResist(RT_CURSE));
			break;
		}

		case P_DEX:
		{
			if ((-n64Amount) > m_wDex)
				n64Amount = -m_wDex;

			m_wDex += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_DEX, m_wDex, GetHit(), GetDodge(), GetDodge(), GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_CURHP:
		{
			if ((-n64Amount) > m_wCurHP)
				n64Amount = -m_wCurHP;
			if (n64Amount > GetMaxHP() - m_wCurHP)
				n64Amount = GetMaxHP() - m_wCurHP;

			m_wCurHP += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bw", P_CURHP, m_wCurHP);			
			break;
		}

		case P_CURMP:
		{
			if ((-n64Amount) > m_wCurMP)
				n64Amount = -m_wCurMP;
			if (n64Amount > GetMaxMP() - m_wCurMP)
				n64Amount = GetMaxMP() - m_wCurMP;

			m_wCurMP += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bw", P_CURMP, m_wCurMP);			
			break;
		}
	}
}

void CPlayer::Teleport(int nX, int nY, int nZ)
{
	Lock();
	m_nOnTeleportX = nX;
	m_nOnTeleportY = nY;
	Unlock();

	BYTE byMap=0;
	BYTE byCheat=0;
	Write(S2C_TELEPORT, "bdddb", byMap, nX, nY, nZ, byCheat);
}

void CPlayer::OnTeleport(BYTE byAnswer, int nZ)
{
	// TODO: Add check for packet hack
	if (!byAnswer) {
		printf(KRED "CPlayer::OnTeleport: Client response: cannot teleport.\n" KNRM);
		return;
	}

	PlayerList plist;
	CMap::GetPlayerListAround(this, MAX_PLAYER_SIGHT, plist);

	Packet deletePacket = GenerateDeletePacket();

	for (PlayerList::iterator it = plist.begin(); it != plist.end(); it++)
	{
		if ((*it)->GetID() != m_nID)
			(*it)->SendPacket(deletePacket);

		(*it)->m_Access.Release();
	}

	CMap::Remove(this);

	Lock();

	m_nX = m_nOnTeleportX;
	m_nY = m_nOnTeleportY;
	m_nZ = nZ;

	Unlock();

	CMap::Add(this);

	CharacterList clist;
	CMap::GetCharacterListAround(this, MAX_PLAYER_SIGHT, clist);

	ItemList ilist;
	CMap::GetItemListAround(this, MAX_PLAYER_SIGHT, ilist);

	for (CharacterList::iterator it = clist.begin(); it != clist.end(); it++)
	{
		Packet createPacketEx = (*it)->GenerateCreatePacket();
		Packet petPacketEx = (*it)->GeneratePetPacket();

		SendPacket(createPacketEx);
		SendPacket(petPacketEx);

		(*it)->m_Access.Release();
	}

	for (ItemList::iterator it = ilist.begin(); it != ilist.end(); it++)
	{
		Packet createPacketEx = (*it)->GenerateCreatePacket();

		SendPacket(createPacketEx);

		(*it)->m_Access.Release();
	}

	Packet createPacket = GenerateCreatePacket();
	Packet petPacket = GeneratePetPacket();

	SendPacketInSight(createPacket);
	SendPacketInSight(petPacket);
}

void CPlayer::InsertItem(CItem *pItem)
{
	if (pItem->GetNum() <= 0)
		return;

	ITEMINFO_DESC desc = pItem->GetDesc();

	CItemInfo* pMacro = (CItemInfo*) CMacroDB::FindMacro(CMacro::MT_ITEM, desc.wIndex);
	if (!pMacro)
		return;

	if (pMacro->m_bPlural && MergeItem(pItem))
		return;

	IntoInven(pItem);
	CItem::Remove(pItem);

	pItem->Lock();
    pItem->SetGState(0);
    pItem->Unlock();
    	
	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));

	char *pBegin = (char*)&buffer;
	char *pEnd = pBegin;

	pEnd = CSocket::WritePacket(pBegin, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbwdd",
				desc.wIndex,
				desc.nIID,
				desc.byPrefix,
				desc.nInfo,
				desc.nNum,
				desc.byMaxEnd,
				desc.byCurEnd,
				(BYTE)0, // bySetGem
				desc.byXAttack,
				desc.byXMagic,
				desc.byXDefense,
				desc.byXHit,
				desc.byXDodge,
				(WORD)0, // wProtectNum
				desc.byExplosiveBlow,
				(BYTE)0, // byCorrectionAddNum
				(BYTE)0, // 
				(BYTE)0, // byRemainingSeconds??
				(BYTE)0, // byRemainingMinutes??
				(DWORD)0, // byRemainingHours??

				desc.fuse.byLevel,
				desc.fuse.wMeele,
				desc.fuse.wMagic,
				desc.fuse.wDefense,
				desc.fuse.wAbsorb,
				desc.fuse.byDodge,
				desc.fuse.byHit,
				desc.fuse.byHP,
				desc.fuse.byMP,
				desc.fuse.byStats[P_STR],
				desc.fuse.byStats[P_HTH],
				desc.fuse.byStats[P_INT],
				desc.fuse.byStats[P_WIS],
				desc.fuse.byStats[P_DEX],

				desc.byShot,
				desc.wPerforation,
				desc.nGongLeft,
				desc.nGongRight);

	Write(S2C_INSERTITEM, "m", pBegin, pEnd - pBegin);

	CDBSocket::Write(S2D_INSERTITEM, "dm", m_nPID, pBegin, pEnd - pBegin);
}

void CPlayer::InsertItem(WORD wIndex, int nNum, BYTE byLogType, bool bOwn, bool bForceSingular, BYTE byPrefix, BYTE byXAttack, BYTE byXMagic, BYTE byXHit, BYTE byEBlow, int nInfo, BYTE byXDodge, BYTE byXDefense, FUSION_DESC* pFuse, BYTE byShot, WORD wPerforation, int nGongLeft, int nGongRight)
{
	CItemInfo* pMacro = (CItemInfo*) CMacroDB::FindMacro(CMacro::MT_ITEM, wIndex);
	if (!pMacro)
		return;

	if (!bForceSingular && pMacro->m_bPlural && MergeItem(wIndex, nNum, byLogType, bOwn))
		return;

	if (nNum <= 0)
		return;

	if (bOwn)
		nInfo = nInfo & ITEM_OWN;

	ITEMINFO_DESC desc;

	desc.nIID = CItem::NewIID();
	desc.wIndex = wIndex;
	desc.nNum = nNum;
	desc.nInfo = nInfo;
	desc.byPrefix = byPrefix;
	desc.byCurEnd = pMacro->m_byEndurance;
	desc.byMaxEnd = desc.byCurEnd;
	desc.byXAttack = byXAttack;
	desc.byXMagic = byXMagic;
	desc.byXDefense = byXDefense;
	desc.byXHit = byXHit;
	desc.byXDodge = byXDodge;
	desc.byExplosiveBlow = byEBlow;

	if (!pFuse)
		memset(&desc.fuse, 0, sizeof(FUSION_DESC));
	else
		desc.fuse = *pFuse;

	desc.byShot = byShot;
	desc.wPerforation = wPerforation;
	desc.nGongLeft = nGongLeft;
	desc.nGongRight = nGongRight;

	CItem* pItem = CItem::CreateItem(desc);
	if (!pItem)
		return;

	IntoInven(pItem);

	PACKETBUFFER buffer;
	memset(&buffer, 0, sizeof(PACKETBUFFER));

	char *pBegin = (char*)&buffer;
	char *pEnd = pBegin;

	pEnd = CSocket::WritePacket(pBegin, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbwdd",
				desc.wIndex,
				desc.nIID,
				desc.byPrefix,
				desc.nInfo,
				desc.nNum,
				desc.byMaxEnd,
				desc.byCurEnd,
				(BYTE)0, // bySetGem
				desc.byXAttack,
				desc.byXMagic,
				desc.byXDefense,
				desc.byXHit,
				desc.byXDodge,
				(WORD)0, // wProtectNum
				desc.byExplosiveBlow,
				(BYTE)0, // byCorrectionAddNum
				(BYTE)0, // 
				(BYTE)0, // byRemainingSeconds??
				(BYTE)0, // byRemainingMinutes??
				(DWORD)0, // byRemainingHours??

				desc.fuse.byLevel,
				desc.fuse.wMeele,
				desc.fuse.wMagic,
				desc.fuse.wDefense,
				desc.fuse.wAbsorb,
				desc.fuse.byDodge,
				desc.fuse.byHit,
				desc.fuse.byHP,
				desc.fuse.byMP,
				desc.fuse.byStats[P_STR],
				desc.fuse.byStats[P_HTH],
				desc.fuse.byStats[P_INT],
				desc.fuse.byStats[P_WIS],
				desc.fuse.byStats[P_DEX],

				desc.byShot,
				desc.wPerforation,
				desc.nGongLeft,
				desc.nGongRight);

	Write(S2C_INSERTITEM, "m", pBegin, pEnd - pBegin);

	CDBSocket::Write(S2D_INSERTITEM, "dm", m_nPID, pBegin, pEnd - pBegin);

}

bool CPlayer::MergeItem(WORD wIndex, int nNum, BYTE byLogType, bool bOwn)
{
	CItem *pItem = FindItem(wIndex, bOwn ? IFO_MUSTOWN : IFO_CANTOWN);
	if (!pItem) return false;

	pItem->Lock();
	pItem->SetNum(pItem->GetNum() + nNum);
	pItem->Unlock();

	Write(S2C_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum(), byLogType);

	CDBSocket::Write(S2D_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum(), byLogType);

	pItem->m_Access.Release();
	return true;
}

bool CPlayer::MergeItem(CItem* dropitem)
{
	CItem *pItem = FindItem(dropitem->GetIndex());

	if(!pItem)
		return false;

	pItem->Lock();
	pItem->SetNum(pItem->GetNum() + dropitem->GetNum());
	pItem->Unlock();

	Write(S2C_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum());

	CDBSocket::Write(S2D_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum());

	pItem->m_Access.Release();

	return true;
}


bool CPlayer::UseItem(CItem *pItem)
{
	if (!pItem->Use(this))
		return true;

	return RemoveItem(pItem, 1, TL_USE);
}

bool CPlayer::RemoveItem(CItem *pItem, int nNum, BYTE byLogType)
{
	if (!nNum)
		nNum = pItem->GetNum();

	if (pItem->GetNum() <= nNum)
	{
		CDBSocket::Write(S2D_REMOVEITEM, "d", pItem->GetIID());
		Write(S2C_UPDATEITEMNUM, "ddb", pItem->GetIID(), 0, byLogType);
		OutofInven(pItem);
		pItem->m_Access.Release();
		delete pItem;
		return false;
	}
	else
	{
		pItem->Lock();
		pItem->SetNum(pItem->GetNum() - nNum);
		pItem->Unlock();
		CDBSocket::Write(S2D_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum(), byLogType);
		Write(S2C_UPDATEITEMNUM, "ddb", pItem->GetIID(), pItem->GetNum(), byLogType);
	}

	return true;
}

void CPlayer::RemoveItem(WORD wIndex, int nNum, BYTE byLogType)
{
	CItem* pItem = FindItem(wIndex);
	if (!pItem)
		return;

	if (RemoveItem(pItem, nNum, byLogType))
		pItem->m_Access.Release();
}

void CPlayer::PutOnItem(CItem *pItem)
{
	pItem->PutOn(this);
}

void CPlayer::PutOffItem(CItem *pItem)
{
	pItem->PutOff(this);
}

void CPlayer::SaveAllProperty()
{
	CDBSocket::Write(S2D_SAVEALLPROPERTY, "dbdddwwwIwwd",
		m_nPID,
		m_byLevel,
		m_nX,
		m_nY,
		m_nZ,
		m_wContribute,
		m_wCurHP,
		m_wCurMP,
		m_n64Exp,
		m_wPUPoint,
		m_wSUPoint,
		m_nAnger);
}

void CPlayer::Tick()
{
	DWORD dwTime = GetTickCount();

	//printf("CPlayer::Tick %s.\n", m_szName.c_str());
}