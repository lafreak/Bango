#include <Socket/CSocket.h>
#include "../Socket/CDBSocket.h"
#include "CPlayer.h"
#include "../CServer.h"
#include "../Item/CItemPet.h"
#include "../Item/CItemWeapon.h"

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
	m_byFace = desc.byFace;
	m_byHair = desc.byHair;
	m_byLevel = desc.byLevel;
	m_wStr = desc.wStats[P_STR];
	m_wHth = desc.wStats[P_HTH];
	m_wInt = desc.wStats[P_INT];
	m_wWis = desc.wStats[P_WIS];
	m_wDex = desc.wStats[P_DEX];
	m_nCurHP = desc.nCurHP;
	m_wCurMP = desc.wCurMP;
	m_n64Exp = desc.n64Exp;
	m_wPUPoint = desc.wPUPoint;
	m_wSUPoint = desc.wSUPoint;
	m_wContribute = desc.wContribute;
	m_nAnger = desc.nAnger;
	m_nX = desc.nX;
	m_nY = desc.nY;
	m_nZ = desc.nZ;

	m_nOnTeleportX = 0;
	m_nOnTeleportY = 0;

	m_n64WearState = 0;
	m_byTrigramLevel = 0;

	m_byShortcutState = 0;

	m_nPartyID = 0;
	m_nPartyInviterID = 0;

	memset(m_Gear, 0, sizeof(int) * GEAR_NUM);
	memset(m_GearIndex, 0, sizeof(WORD) * GEAR_VISIBLE_NUM);

	m_byKind = CK_PLAYER;
}

CPlayer::~CPlayer()
{
	EmptyInven();

	LeaveParty();

	// Bad idea
	RemoveAggro();

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
	CItem *pItem=NULL;

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
	ApplySpec(pItem);

	if (pItem->GetWearType() < GEAR_NUM)
		m_Gear[pItem->GetWearType()] = pItem->GetIID();

	if (pItem->GetWearType() < GEAR_VISIBLE_NUM)
		m_GearIndex[pItem->GetWearType()] = pItem->GetIndex();

	if (pItem->GetMacro()->m_bySubClass == ISC_SWORD2HAND)
		AddWState(WS_2HANDWEAPON);

	if (pItem->GetMacro()->m_bySubClass >= ISC_TRIGRAM1 && pItem->GetMacro()->m_bySubClass <= ISC_TRIGRAM8)
		m_byTrigramLevel = pItem->GetLevel();

	if (pItem->GetWearType() == WS_WEAPON)
	{
		m_wAttackSpeed = ((CItemWeapon*)pItem)->GetAttackSpeed();
		m_wAttackRange = ((CItemWeapon*)pItem)->GetRange();
	}

	AddWState(pItem->GetWearType());
}

void CPlayer::OnPutOffGear(CItem *pItem)
{
	FreeSpec(pItem);

	if (pItem->GetWearType() < GEAR_NUM)
		m_Gear[pItem->GetWearType()] = 0;

	if (pItem->GetWearType() < GEAR_VISIBLE_NUM)
		m_GearIndex[pItem->GetWearType()] = 0;

	if (pItem->GetMacro()->m_bySubClass == ISC_SWORD2HAND)
		SubWState(WS_2HANDWEAPON);

	if (pItem->GetWearType() == WS_WEAPON)
	{
		m_wAttackSpeed = 0;
		m_wAttackRange = 0;
	}

	SubWState(pItem->GetWearType());

	if (!IsAnyTrigramState())
		m_byTrigramLevel = 0;
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

void CPlayer::TickAll()
{
	g_mxPlayer.lock();

	for (auto& a: g_mPlayer)
	{
		a.second->m_Access.Grant();
		a.second->Tick();
		a.second->m_Access.Release();
	}

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

WORD CPlayer::GetHit() const
{
	return GetAgi() / 8 + 15 * GetStr() / 54 + m_wHitAdd;
}

WORD CPlayer::GetDodge() const
{
	return GetAgi() / 3 + m_wDodgeAdd;
}

DWORD CPlayer::GetMaxHP() const
{
	return ((GetLevel() >= 96 ? 195 :
		(GetLevel() >= 91 ? 141.8147 :
		(GetLevel() >= 86 ? 111.426 :
			(GetLevel() >= 81 ? 91.758 :
			(GetLevel() >= 76 ? 78 :
				(GetLevel() >= 72 ? 67.8162 :
					52)))))) * GetLevel() / 3) + 115 + 2 * GetHth() * GetHth() / g_denoHP[m_byClass] + m_dwMaxHPAdd;
}

WORD CPlayer::GetMaxMP() const
{
	return ((GetLevel() >= 96 ? 20 :
		(GetLevel() >= 91 ? 18 :
		(GetLevel() >= 86 ? 16 :
			(GetLevel() >= 81 ? 14 :
			(GetLevel() >= 76 ? 12 :
				(GetLevel() >= 72 ? 10 :
					8)))))) * GetLevel()) + 140 + GetWis() + 2 * GetWis() * GetWis() / g_denoMP[m_byClass] + m_wMaxMPAdd;
}

WORD CPlayer::GetMinAttack() const
{
	return 1 + ((11 * GetStr() - 80) / 30) + ((GetAgi() - 5) / 11) + (7 * GetLevel() / 10) + m_wMinAttackAdd;
}

WORD CPlayer::GetMaxAttack() const
{
	return ((8 * GetStr() - 25) / 15) + (18 * GetAgi() / 77) + GetLevel() + m_wMaxAttackAdd;
}

WORD CPlayer::GetMinMagic() const
{
	return (7 * GetInt() - 20) / 12 + GetWis() / 7 + m_wMinMagicAdd;
}

WORD CPlayer::GetMaxMagic() const
{
	return 7 * GetInt() / 12 + 14 * GetWis() / 45 + m_wMaxMagicAdd;
}

WORD CPlayer::GetResist(BYTE byResist) const
{
	switch (byResist)
	{
	case RT_FIRE:
		return GetInt() / 9 + m_wResistFireAdd;
	case RT_ICE:
		return GetInt() / 9 + m_wResistIceAdd;
	case RT_LITNING:
		return GetInt() / 9 + m_wResistLitningAdd;
	case RT_PALSY:
		return GetHth() / 9 + m_wResistPalsyAdd;
	case RT_CURSE:
		return GetWis() / 9 + m_wResistCurseAdd;
	}
}

void CPlayer::Process(Packet packet)
{
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

			Lock();
			Rest(byType);
			Unlock();

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

			Lock();

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

			Unlock();

			break;
		}

		// Add Distance check and cooldown 
		// Otherwise it's possible to flood server with party requests & spam all players
		case C2S_ASKPARTY:
		{
			int nID=0;
			CSocket::ReadPacket(packet.data, "d", &nID);

			auto pTarget = CPlayer::FindPlayer(nID);

			if (pTarget)
			{
				Lock();
				pTarget->Lock();

				AskParty(pTarget);

				pTarget->Unlock();
				Unlock();
				
				pTarget->m_Access.Release();
			}

			break;
		}

		case C2S_ANS_ASKPARTY:
		{
			int nID=0;
			BYTE byAns=0;
			CSocket::ReadPacket(packet.data, "bd", &byAns, &nID);

			if (nID == GetID())
				break;

			if (nID != GetPartyInviterID())
				break;

			if (HasParty())
				break;

			if (byAns == 0) // Decline
			{
				Lock();
				SetPartyInviterID(0);
				// TODO: Sent packet to Inviter that request was declined.
				Unlock();
				break;
			}

			auto pInviter = CPlayer::FindPlayer(nID);

			if (pInviter)
			{
				auto pParty = CParty::FindParty(pInviter->GetPartyID());

				if (pParty)
				{
					if (!pParty->IsHead(pInviter))
						;
					else if (pParty->GetSize() < 8)
						pParty->AddMember(this);
					else
						; // TODO: Party is full packet
				}
				else
				{
					pParty = new CParty(pInviter, this);
				}

				pParty->m_Access.Release();
				pInviter->m_Access.Release();
			}

			break;
		}

		//TODO: Leave Party Message 
		case C2S_LEAVEPARTY:
		{
			LeaveParty();
			break;
		}

		case C2S_EXILEPARTY:
		{
			int nID = 0;
			CSocket::ReadPacket(packet.data, "d", &nID);

			if (!HasParty())
				break;

			CPlayer* pTarget = CPlayer::FindPlayer(nID);
			if (!pTarget)
				break;

			CParty* pParty = CParty::FindParty(pTarget->GetPartyID());

			if (pParty)
			{
				if (GetID() != pTarget->GetID() && pParty->IsHead(this))
				{
					pParty->m_Access.Release();
					pTarget->LeaveParty();
				}
				else
				{
					pParty->m_Access.Release();
				}
			}

			pTarget->m_Access.Release();
			break;
		}

		case C2S_REVIVAL:
		{
			Revival();
			break;
		}

		case C2S_ATTACK:
		{
			BYTE byKind=0;
			int nID=0;
			int nMove=0;//?
			CSocket::ReadPacket(packet.data, "bdd", &byKind, &nID, &nMove);

			CCharacter* pTarget=NULL;

			if (byKind == CK_PLAYER)
				pTarget = CPlayer::FindPlayer(nID);
			else if (byKind == CK_MONSTER)
				pTarget = CMonster::FindMonster(nID);

			if (pTarget)
			{
				Lock();
				pTarget->Lock();
				Attack(pTarget);
				pTarget->Unlock();
				Unlock();

				pTarget->m_Access.Release();
			}

			break;
		}
	}

	printf("C2S_? %d\n", packet.byType);
}

void CPlayer::OnLoadPlayer()
{
	Lock();

	m_byGrade = 1;
	m_szGuildName = "\0";
	m_byGRole = 1;
	m_wDefense = 0;
	m_byAbsorb = 0;

	m_szGuildClass = "\0";
	m_nGID = 0;
	m_byFlag = 0;
	m_nFlagItem = 0;
	m_nHonorGrade = 0;
	m_nHonorOption = 0;

	m_wDir = 0;

	if (GetCurHP() <= 0)
		AddGState(CGS_KO);

	SendProperty();

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

bool CPlayer::CanAttack(CCharacter * pTarget) const
{
	if (!CCharacter::CanAttack(pTarget))
		return false;

	if (!IsWState(WS_WEAPON))
		return false;

	if (m_wAttackSpeed == 0)
		return false;

	if (m_dwLastAttackTime + m_wAttackSpeed > GetTickCount())
		return false; // TODO: It is better to decrease damage instead ignoring it completely

	int nDistance = GetDistance(pTarget);// -GetSize() - pTarget->GetSize();
	if (nDistance > m_wAttackRange)
	{
		printf(KRED "Too far away from monster Current[%d] Allowed[%d]\n" KNRM, nDistance, m_wAttackRange);
		//return false;
	}
	else
	{
		printf(KGRN "Range is OK Current[%d] Allowed[%d]\n" KNRM, nDistance, m_wAttackRange);
	}

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

		AddGState(CGS_REST);
		WriteInSight(S2C_ACTION, "dbb", m_nID, AT_REST, byType);
	}
	else
	{
		if (!IsGState(CGS_REST))
			return;

		SubGState(CGS_REST);
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

		case '#':
		{
			auto pParty = CParty::FindParty(GetPartyID());
			if (pParty)
			{
				pParty->Broadcast(S2C_CHATTING, "ss", (char *)m_szName.c_str(), szMsg);
				pParty->m_Access.Release();
			}

			break;
		}

		default:
			WriteInSight(S2C_CHATTING, "ss", m_szName.c_str(), szMsg);
			break;
	}
}

void CPlayer::ChatCommand(char* szCommand)
{
	char *token = std::strtok(szCommand, " ");

	if (!strcmp(token, "/party")) {
		token = std::strtok(NULL, " ");

		if (!token)
			return;

		auto pTarget = CPlayer::FindPlayerByName(token);
		if (pTarget)
		{
			Lock();
			pTarget->Lock();

			AskParty(pTarget);

			pTarget->Unlock();
			Unlock();

			pTarget->m_Access.Release();
		}
	}

	if (!strcmp(token, "/ride")) {
		token = std::strtok(NULL, " ");

		if (!token)
			return;

		int nIndex = atoi(token);

		WriteInSight(S2C_RIDING, "bdd", 0, m_nID, nIndex);
	}

	else if (!strcmp(token, "/expelparty")) {
		token = std::strtok(NULL, " ");

		if (!token)
			return;

		if (!HasParty())
			return;

		CPlayer* pTarget = CPlayer::FindPlayerByName(token);
		if (!pTarget)
			return;

		CParty* pParty = CParty::FindParty(pTarget->GetPartyID());

		if (pParty)
		{
			if (GetID() != pTarget->GetID() && pParty->IsHead(this))
			{
				pParty->m_Access.Release();
				pTarget->LeaveParty();
			}
			else
			{
				pParty->m_Access.Release();
			}
		}
	
		pTarget->m_Access.Release();
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

		Teleport(nX, nY, 0, nZ);
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

		CMonster *pMonster = CMonster::Summon(wIndex, GetX(), GetY());
		if (pMonster) {
		//	pMonster->SetTarget(this);
		//	pMonster->SetAIS(CMonster::AIS_CHASE);
		}
	}

	else if (!strcmp(token, "/test")) {
		token = std::strtok(NULL, " ");

		int wIndex=0;

		if (token)
			wIndex = atoi(token);

		
		for (int i = GetX() - 500; i <= GetX() + 500; i+=50) {
			for (int j = GetY() - 500; j <= GetY() + 500; j+=50) {
				CMonster::Summon(wIndex, i, j);
			}
		}
		
		//Write(S2C_ITEMSHOP, "b", 0);
		//Write(S2C_ITEMSHOP, "bddd", 4, 100, 200, 300);

		//Write(S2C_ITEMSHOP, "bbwwwbbdbwbbdb", 3, wIndex, 400, 2, 255, 1, 2, 3, 4, 256, 1, 2, 3, 4);
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

		case P_STRADD:
		{
			if ((-n64Amount) > m_wStrAdd)
				n64Amount = -m_wStrAdd;

			m_wStrAdd += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwww", P_STRADD, m_wStrAdd, GetHit(), GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_HTH:
		{
			if ((-n64Amount) > m_wHth)
				n64Amount = -m_wHth;

			m_wHth += n64Amount;

			DWORD nMaxHP = GetMaxHP();
			if (m_nCurHP > nMaxHP)
				m_nCurHP = nMaxHP;

			Write(S2C_UPDATEPROPERTY, "bwddw", P_HTH, m_wHth, m_nCurHP, nMaxHP, GetResist(RT_PALSY));

			CParty *pParty = CParty::FindParty(GetPartyID());
			if (pParty)
			{
				pParty->UpdateMemberHP(this);
				pParty->m_Access.Release();
			}

			break;
		}

		case P_HTHADD:
		{
			if ((-n64Amount) > m_wHthAdd)
				n64Amount = -m_wHthAdd;

			m_wHthAdd += n64Amount;

			DWORD nMaxHP = GetMaxHP();
			if (m_nCurHP > nMaxHP)
				m_nCurHP = nMaxHP;

			Write(S2C_UPDATEPROPERTY, "bwddw", P_HTHADD, m_wHthAdd, m_nCurHP, nMaxHP, GetResist(RT_PALSY));

			CParty *pParty = CParty::FindParty(GetPartyID());
			if (pParty)
			{
				pParty->UpdateMemberHP(this);
				pParty->m_Access.Release();
			}

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

		case P_INTADD:
		{
			if ((-n64Amount) > m_wIntAdd)
				n64Amount = -m_wIntAdd;

			m_wIntAdd += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_INTADD, m_wIntAdd, GetMinMagic(), GetMaxMagic(), GetResist(RT_FIRE), GetResist(RT_ICE), GetResist(RT_LITNING));
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

		case P_WISADD:
		{
			if ((-n64Amount) > m_wWisAdd)
				n64Amount = -m_wWisAdd;

			m_wWisAdd += n64Amount;

			WORD wMaxMP = GetMaxMP();
			if (m_wCurMP > wMaxMP)
				m_wCurMP = wMaxMP;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_WISADD, m_wWisAdd, m_wCurMP, wMaxMP, GetMinMagic(), GetMaxMagic(), GetResist(RT_CURSE));
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

		case P_DEXADD:
		{
			if ((-n64Amount) > m_wDexAdd)
				n64Amount = -m_wDexAdd;

			m_wDexAdd += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bwwwwww", P_DEXADD, m_wDexAdd, GetHit(), GetDodge(), GetDodge(), GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_CURHP:
		{
			if ((-n64Amount) > m_nCurHP)
				n64Amount = -m_nCurHP;
			if (n64Amount > GetMaxHP() - m_nCurHP)
				n64Amount = GetMaxHP() - m_nCurHP;

			m_nCurHP += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bd", P_CURHP, m_nCurHP);

			CParty *pParty = CParty::FindParty(GetPartyID());
			if (pParty)
			{
				pParty->UpdateMemberHP(this);
				pParty->m_Access.Release();
			}

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

		case P_DEFENSE:
		{
			if ((-n64Amount) > m_wDefense)
				n64Amount = -m_wDefense;

			m_wDefense += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bww", P_DEFENSE, GetDefense(), GetDefense());
			break;
		}

		case P_DODGE:
		{
			if ((-n64Amount) > m_wDodgeAdd)
				n64Amount = -m_wDodgeAdd;

			m_wDodgeAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bww", P_DODGE, GetDodge(), GetDodge());
			break;
		}

		case P_HIT:
		{
			if ((-n64Amount) > m_wHitAdd)
				n64Amount = -m_wHitAdd;

			m_wHitAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_HIT, GetHit());
			break;
		}

		case P_ABSORB:
		{
			if ((-n64Amount) > m_byAbsorb)
				n64Amount = -m_byAbsorb;

			m_byAbsorb += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_ABSORB, GetAbsorb());
			break;
		}

		case P_HP:
		{
			if ((-n64Amount) > m_dwMaxHPAdd)
				n64Amount = -m_dwMaxHPAdd;

			m_dwMaxHPAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bdd", P_HP, GetCurHP(), GetMaxHP());
			break;
		}

		case P_MP:
		{
			if ((-n64Amount) > m_wMaxMPAdd)
				n64Amount = -m_wMaxMPAdd;

			m_wMaxMPAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bww", P_MP, GetCurMP(), GetMaxMP());
			break;
		}

		case P_MINATTACK:
		{
			if ((-n64Amount) > m_wMinAttackAdd)
				n64Amount = -m_wMinAttackAdd;

			m_wMinAttackAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_MINATTACK, GetMinAttack());
			break;
		}
		
		case P_MAXATTACK:
		{
			if ((-n64Amount) > m_wMaxAttackAdd)
				n64Amount = -m_wMaxAttackAdd;

			m_wMaxAttackAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_MAXATTACK, GetMaxAttack());
			break;
		}

		case P_MINMAXATTACK:
		{
			if ((-n64Amount) > m_wMinAttackAdd)
				n64Amount = -m_wMinAttackAdd;

			if ((-n64Amount) > m_wMaxAttackAdd)
				n64Amount = -m_wMaxAttackAdd;

			m_wMinAttackAdd += n64Amount;
			m_wMaxAttackAdd += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bw", P_MINMAXATTACK, GetMinAttack(), GetMaxAttack());
			break;
		}

		case P_MINMAGIC:
		{
			if ((-n64Amount) > m_wMinMagicAdd)
				n64Amount = -m_wMinMagicAdd;

			m_wMinMagicAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_MINMAGIC, GetMinMagic());
			break;
		}

		case P_MAXMAGIC:
		{
			if ((-n64Amount) > m_wMaxMagicAdd)
				n64Amount = -m_wMaxMagicAdd;

			m_wMaxMagicAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_MAXMAGIC, GetMaxMagic());
			break;
		}

		case P_MINMAXMAGIC:
		{
			if ((-n64Amount) > m_wMinMagicAdd)
				n64Amount = -m_wMinMagicAdd;

			if ((-n64Amount) > m_wMaxMagicAdd)
				n64Amount = -m_wMaxMagicAdd;

			m_wMinMagicAdd += n64Amount;
			m_wMaxMagicAdd += n64Amount;

			Write(S2C_UPDATEPROPERTY, "bw", P_MINMAXMAGIC, GetMinMagic(), GetMinMagic());
			break;
		}

		case P_RESFIRE:
		{
			if ((-n64Amount) > m_wResistFireAdd)
				n64Amount = -m_wResistFireAdd;

			m_wResistFireAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_RESFIRE, GetResist(RT_FIRE));
			break;
		}

		case P_RESICE:
		{
			if ((-n64Amount) > m_wResistIceAdd)
				n64Amount = -m_wResistIceAdd;

			m_wResistIceAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_RESICE, GetResist(RT_ICE));
			break;
		}

		case P_RESLITNING:
		{
			if ((-n64Amount) > m_wResistLitningAdd)
				n64Amount = -m_wResistLitningAdd;

			m_wResistLitningAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_RESLITNING, GetResist(RT_LITNING));
			break;
		}

		case P_RESCURSE:
		{
			if ((-n64Amount) > m_wResistCurseAdd)
				n64Amount = -m_wResistCurseAdd;

			m_wResistCurseAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_RESCURSE, GetResist(RT_CURSE));
			break;
		}

		case P_RESPALSY:
		{
			if ((-n64Amount) > m_wResistPalsyAdd)
				n64Amount = -m_wResistPalsyAdd;

			m_wResistPalsyAdd += n64Amount;
			Write(S2C_UPDATEPROPERTY, "bw", P_RESPALSY, GetResist(RT_PALSY));
			break;
		}
	}
}

void CPlayer::Teleport(int nX, int nY, int nSpread, int nZ)
{
	if (nSpread > 0)
	{
		nX += ((rand() % nSpread) - nSpread / 2);
		nY += ((rand() % nSpread) - nSpread / 2);
	}

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

	for (CharacterList::iterator it = clist.begin(); it != clist.end(); it++)
	{
		Packet createPacketEx = (*it)->GenerateCreatePacket();
		Packet petPacketEx = (*it)->GeneratePetPacket();

		SendPacket(createPacketEx);
		SendPacket(petPacketEx);

		(*it)->m_Access.Release();
	}

	Packet createPacket = GenerateCreatePacket();
	Packet petPacket = GeneratePetPacket();

	SendPacketInSight(createPacket);
	SendPacketInSight(petPacket);
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
	CDBSocket::Write(S2D_SAVEALLPROPERTY, "dbdddwdwIwwd",
		m_nPID,
		m_byLevel,
		m_nX,
		m_nY,
		m_nZ,
		m_wContribute,
		m_nCurHP,
		m_wCurMP,
		m_n64Exp,
		m_wPUPoint,
		m_wSUPoint,
		m_nAnger);
}

void CPlayer::SendProperty()
{
	//					 bsbwwwwwwddwwwwwbIwwwwwwbbbbbd
	Write(S2C_PROPERTY, "bsbwwwwwwddwwwwwbIwwwwwwbbbbbd",
		m_byGrade,
		m_szGuildName.c_str(),
		m_byGRole,
		m_wContribute,
		m_wStr,
		m_wHth,
		m_wInt,
		m_wWis,
		m_wDex,
		m_nCurHP,
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
}

void CPlayer::ApplySpec(CItem * pItem)
{
	UpdateProperty(P_DEFENSE, pItem->GetMacro()->m_wDefense);
	UpdateProperty(P_HIT, pItem->GetMacro()->m_wHit);
	UpdateProperty(P_DODGE, pItem->GetMacro()->m_wDodge);
	UpdateProperty(P_ABSORB, pItem->GetMacro()->m_wAbsorb);
	UpdateProperty(P_RESFIRE, pItem->GetMacro()->m_wResistFire);
	UpdateProperty(P_RESICE, pItem->GetMacro()->m_wResistIce);
	UpdateProperty(P_RESLITNING, pItem->GetMacro()->m_wResistLitning);
	UpdateProperty(P_RESCURSE, pItem->GetMacro()->m_wResistCurse);
	UpdateProperty(P_RESPALSY, pItem->GetMacro()->m_wResistPalsy);
	UpdateProperty(P_HP, pItem->GetMacro()->m_dwHP);
	UpdateProperty(P_MP, pItem->GetMacro()->m_dwMP);
	UpdateProperty(P_MINATTACK, pItem->GetMacro()->m_wMinAttack);
	UpdateProperty(P_MAXATTACK, pItem->GetMacro()->m_wMaxAttack);
	UpdateProperty(P_MINMAGIC, pItem->GetMacro()->m_wMinMagic);
	UpdateProperty(P_MAXMAGIC, pItem->GetMacro()->m_wMaxMagic);
	UpdateProperty(P_STRADD, pItem->GetMacro()->m_wStr);
	UpdateProperty(P_HTHADD, pItem->GetMacro()->m_wHth);
	UpdateProperty(P_INTADD, pItem->GetMacro()->m_wInt);
	UpdateProperty(P_WISADD, pItem->GetMacro()->m_wWis);
	UpdateProperty(P_DEXADD, pItem->GetMacro()->m_wDex);
}

void CPlayer::FreeSpec(CItem * pItem)
{
	UpdateProperty(P_DEFENSE, -pItem->GetMacro()->m_wDefense);
	UpdateProperty(P_HIT, -pItem->GetMacro()->m_wHit);
	UpdateProperty(P_DODGE, -pItem->GetMacro()->m_wDodge);
	UpdateProperty(P_ABSORB, -pItem->GetMacro()->m_wAbsorb);
	UpdateProperty(P_RESFIRE, -pItem->GetMacro()->m_wResistFire);
	UpdateProperty(P_RESICE, -pItem->GetMacro()->m_wResistIce);
	UpdateProperty(P_RESLITNING, -pItem->GetMacro()->m_wResistLitning);
	UpdateProperty(P_RESCURSE, -pItem->GetMacro()->m_wResistCurse);
	UpdateProperty(P_RESPALSY, -pItem->GetMacro()->m_wResistPalsy);
	UpdateProperty(P_HP, -pItem->GetMacro()->m_dwHP);
	UpdateProperty(P_MP, -pItem->GetMacro()->m_dwMP);
	UpdateProperty(P_MINATTACK, -pItem->GetMacro()->m_wMinAttack);
	UpdateProperty(P_MAXATTACK, -pItem->GetMacro()->m_wMaxAttack);
	UpdateProperty(P_MINMAGIC, -pItem->GetMacro()->m_wMinMagic);
	UpdateProperty(P_MAXMAGIC, -pItem->GetMacro()->m_wMaxMagic);
	UpdateProperty(P_STRADD, -pItem->GetMacro()->m_wStr);
	UpdateProperty(P_HTHADD, -pItem->GetMacro()->m_wHth);
	UpdateProperty(P_INTADD, -pItem->GetMacro()->m_wInt);
	UpdateProperty(P_WISADD, -pItem->GetMacro()->m_wWis);
	UpdateProperty(P_DEXADD, -pItem->GetMacro()->m_wDex);
}

void CPlayer::AskParty(CPlayer * pTarget)
{
	if (pTarget->GetID() == GetID())
		return;

	if (pTarget->HasParty())
		return;

	auto pParty = CParty::FindParty(GetPartyID());

	if (pParty)
	{
		if (pParty->IsHead(this))
		{
			pTarget->SetPartyInviterID(GetID());
			pTarget->Write(S2C_ASKPARTY, "d", GetID());
		}

		pParty->m_Access.Release();
	}
	else
	{
		pTarget->SetPartyInviterID(GetID());
		pTarget->Write(S2C_ASKPARTY, "d", GetID());
	}
}

void CPlayer::LeaveParty()
{
	auto pParty = CParty::FindParty(GetPartyID());

	if (pParty)
	{
		pParty->RemoveMember(this);

		if (pParty->GetSize() == 1)
		{
			//pParty->Discard();
			auto pLeader = pParty->FindLeader();
			pParty->RemoveMember(pLeader);
			pLeader->m_Access.Release();
			pParty->m_Access.Release();
			delete pParty;
		}
		else
		{
			pParty->m_Access.Release();
		}
	}
}

void CPlayer::RemoveAggro()
{
	MonsterList list;
	CMap::GetMonsterListAround(this, MAX_PLAYER_SIGHT, list);

	for (auto &m : list)
	{
		if (m->GetTarget() == this)
		{
			m->Lock();
			m->SetTarget(NULL);
			m->Unlock();
		}

		m->m_Access.Release();
	}
}

void CPlayer::Tick()
{
	DWORD dwTime = GetTickCount();

	//printf("CPlayer::Tick %s.\n", m_szName.c_str());
}

void CPlayer::Damage(CCharacter * pAttacker, DWORD& dwDamage, BYTE& byType)
{
	byType = ATF_HIT;

	dwDamage = GetFinalDamage(pAttacker, dwDamage);
	dwDamage = pAttacker->GetFatalDamage(dwDamage, byType);

	if (dwDamage > GetCurHP())
		dwDamage = GetCurHP();

	if (dwDamage <= 0)
	{
		byType = 0;
		return;
	}

	m_nCurHP -= dwDamage;
	// TODO: Party HP broadcast?

	if (GetCurHP() > 0)
	{
		Rest(0);
	}
	else
	{
		if (pAttacker->GetKind() == CK_MONSTER)
			((CMonster*)pAttacker)->SetTarget(NULL);

		Die();
	}
}

void CPlayer::Die()
{
	AddGState(CGS_KO);
	WriteInSight(S2C_ACTION, "db", GetID(), AT_DIE);
}

void CPlayer::Revival()
{
	if (!IsGState(CGS_KO))
		return;

	Lock();
	UpdateProperty(P_CURHP, GetMaxHP());
	SubGState(CGS_KO);
	Unlock();

	Teleport(360931, 187024);
}

void CPlayer::Attack(CCharacter *pTarget)
{
	if (!CanAttack(pTarget))
		return;

	m_dwLastAttackTime = GetTickCount();

	SetDirection(pTarget);

	// TODO: Distance check
	// TODO: Player OnPVP Check

	DWORD dwDamage = GetAttack();
	DWORD dwExplosiveBlow = 0;
	BYTE byType = 0;

	if (CheckHit(pTarget))
		pTarget->Damage(this, dwDamage, byType);
	else
		dwDamage = 0;

	// TODO: Bugfix - last hit doesn't display damage on monster.
	WriteInSight(S2C_ATTACK, "ddddb", GetID(), pTarget->GetID(), dwDamage, dwExplosiveBlow, byType);
}
