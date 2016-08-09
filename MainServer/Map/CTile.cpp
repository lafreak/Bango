#include "CTile.h"

void CTile::Add(CCharacter *pCharacter)
{
	Lock();

	if (m_mCharacter.find(pCharacter->GetID()) == m_mCharacter.end())
		m_mCharacter[pCharacter->GetID()] = pCharacter;

	Unlock();
}

void CTile::Remove(int nID)
{
	Lock();

	CharacterMap::iterator it = m_mCharacter.find(nID);
	if (it != m_mCharacter.end())
		m_mCharacter.erase(it);

	Unlock();
}

void CTile::SendPacket(int nX, int nY, Packet &packet)
{
	Lock();

	for (auto& a: m_mCharacter) {
		a.second->m_Access.Grant();

		if (a.second->GetKind() == CK_PLAYER) {
			CPlayer *pPlayer = (CPlayer*)a.second;

			//if (abs(pPlayer->GetX() - nX) < MAX_PLAYER_SIGHT && abs(pPlayer->GetY() - nY) < MAX_PLAYER_SIGHT) {
			if (sqrt(pow(pPlayer->GetX() - nX, 2) + pow(pPlayer->GetY() - nY, 2)) < MAX_PLAYER_SIGHT) {
				printf("Sent to %d.\n", pPlayer->GetID());
				pPlayer->SendPacket(packet);
			}
		}

		a.second->m_Access.Release();
	}

	Unlock();
}

void CTile::SendPacket(CCharacter *pCharacter, Packet &packet)
{
	Lock();

	for (auto& a: m_mCharacter) {
		a.second->m_Access.Grant();

		if (a.second->GetKind() == CK_PLAYER && a.second->GetID() != pCharacter->GetID()) {
			CPlayer *pPlayer = (CPlayer*)a.second;

			//if (abs(pPlayer->GetX() - nX) < MAX_PLAYER_SIGHT && abs(pPlayer->GetY() - nY) < MAX_PLAYER_SIGHT) {
			if (sqrt(pow(pPlayer->GetX() - pCharacter->GetX(), 2) + pow(pPlayer->GetY() - pCharacter->GetY(), 2)) < MAX_PLAYER_SIGHT) {
				printf("Sent to %d.\n", pPlayer->GetID());
				pPlayer->SendPacket(packet);
			}
		}

		a.second->m_Access.Release();
	}

	Unlock();
}

void CTile::SendMoveAction(CCharacter *pCharacter, char byX, char byY,
	Packet &createPacket, Packet& deletePacket, Packet& movePacket)
{
	Lock();

	for (auto& a: m_mCharacter) {
		a.second->m_Access.Grant();

		if (a.second->GetKind() == CK_PLAYER && a.second->GetID() != pCharacter->GetID()) {
			CPlayer *pPlayer = (CPlayer*)a.second;

			switch (pCharacter->GetMoveAction(pPlayer, byX, byY))
			{
				case MV_AC_CREATE:
				{
					pPlayer->SendPacket(createPacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pPlayer->GenerateCreatePacket();
						((CPlayer*)pCharacter)->SendPacket(p);
					}
					break;
				}
				case MV_AC_DELETE:
				{
					pPlayer->SendPacket(deletePacket);
					if (pCharacter->GetKind() == CK_PLAYER) {
						Packet p=pPlayer->GenerateDeletePacket();
						((CPlayer*)pCharacter)->SendPacket(p);
					}
					break;
				}
				case MV_AC_MOVE:
					pPlayer->SendPacket(movePacket);
					break;
			}
		}

		a.second->m_Access.Release();
	}

	Unlock();
}