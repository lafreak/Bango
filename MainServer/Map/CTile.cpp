#include "CTile.h"

void CTile::Add(CCharacter *pCharacter)
{
	Lock();

	switch (pCharacter->GetKind())
	{
		case CK_PLAYER:
			if (m_mPlayer.find(pCharacter->GetID()) == m_mPlayer.end())
				m_mPlayer[pCharacter->GetID()] = (CPlayer*)pCharacter;
			break;

		case CK_NPC:
			if (m_mNPC.find(pCharacter->GetID()) == m_mNPC.end())
				m_mNPC[pCharacter->GetID()] = (CNPC*)pCharacter;
			break;
	}

	Unlock();
}

void CTile::Remove(CCharacter *pCharacter)
{
	Lock();

	switch (pCharacter->GetKind())
	{
		case CK_PLAYER:
		{
			PlayerMap::iterator it = m_mPlayer.find(pCharacter->GetID());
			if (it != m_mPlayer.end())
				m_mPlayer.erase(it);
			break;
		}

		case CK_NPC:
		{
			NPCMap::iterator it = m_mNPC.find(pCharacter->GetID());
			if (it != m_mNPC.end())
				m_mNPC.erase(it);
			break;
		}
	}

	Unlock();
}

void CTile::GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list)
{
	Lock();

	for (auto& a: m_mPlayer) {
		a.second->m_Access.Grant();
		auto pTarget = a.second;

		if (pCharacter->GetDistance(pTarget) <= nDistance)
			list.push_back(pTarget);
		else 
			pTarget->m_Access.Release();
	}

	for (auto& a: m_mNPC) {
		a.second->m_Access.Grant();
		auto pTarget = a.second;

		if (pCharacter->GetDistance(pTarget) <= nDistance)
			list.push_back(pTarget);
		else 
			pTarget->m_Access.Release();
	}

	Unlock();
}

void CTile::GetPlayerListAround(CCharacter *pCharacter, int nDistance, PlayerList& list)
{
	Lock();

	for (auto& a: m_mPlayer) {
		a.second->m_Access.Grant();
		auto pTarget = a.second;

		if (pCharacter->GetDistance(pTarget) <= nDistance)
			list.push_back(pTarget);
		else 
			pTarget->m_Access.Release();
	}

	Unlock();
}

void CTile::SendPacket(CCharacter *pCharacter, Packet &packet)
{
	Lock();

	for (auto& a: m_mPlayer) {
		a.second->m_Access.Grant();

		CPlayer *pPlayer = (CPlayer*)a.second;

		if (sqrt(pow(pPlayer->GetX() - pCharacter->GetX(), 2) + pow(pPlayer->GetY() - pCharacter->GetY(), 2)) < MAX_PLAYER_SIGHT) {
			//printf("Sent to %d.\n", pPlayer->GetID());
			pPlayer->SendPacket(packet);
		}

		a.second->m_Access.Release();
	}

	Unlock();
}

void CTile::SendMoveAction(CCharacter *pCharacter, char byX, char byY,
	Packet &createPacket, Packet &petPacket, Packet& deletePacket, Packet& movePacket)
{
	Lock();

	for (auto& a: m_mPlayer) {
		a.second->m_Access.Grant();

		if (a.second->GetID() != pCharacter->GetID()) {
			auto pCharacterEx = a.second;

			switch (pCharacter->GetMoveAction(pCharacterEx, byX, byY))
			{
				case MV_AC_CREATE:
				{
					pCharacterEx->SendPacket(createPacket);
					pCharacterEx->SendPacket(petPacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pCharacterEx->GenerateCreatePacket();
						Packet r=pCharacterEx->GeneratePetPacket();
						pCharacter->SendPacket(p);
						pCharacter->SendPacket(r);
					}
					break;
				}
				case MV_AC_DELETE:
				{
					pCharacterEx->SendPacket(deletePacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pCharacterEx->GenerateDeletePacket();
						pCharacter->SendPacket(p);
					}
					break;
				}
				case MV_AC_MOVE:
					pCharacterEx->SendPacket(movePacket);
					break;
			}
		}

		a.second->m_Access.Release();
	}

	for (auto& a: m_mNPC) {
		a.second->m_Access.Grant();

		if (a.second->GetID() != pCharacter->GetID()) {
			auto pCharacterEx = a.second;

			switch (pCharacter->GetMoveAction(pCharacterEx, byX, byY))
			{
				case MV_AC_CREATE:
				{
					pCharacterEx->SendPacket(createPacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pCharacterEx->GenerateCreatePacket();
						pCharacter->SendPacket(p);
					}
					break;
				}
				case MV_AC_DELETE:
				{
					pCharacterEx->SendPacket(deletePacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pCharacterEx->GenerateDeletePacket();
						pCharacter->SendPacket(p);
					}
					break;
				}
				case MV_AC_MOVE:
					pCharacterEx->SendPacket(movePacket);
					break;
			}
		}

		a.second->m_Access.Release();
	}

	Unlock();
}