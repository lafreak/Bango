#include "CItemTeleport.h"

#include "../../GameCharacter/CPlayer.h"

CoordsMap CItemTeleport::g_mTeleportCoords = {
	{ NARO,	   {257778, 259392} },
	{ CARGO,   {264931, 262029} },
	{ GEUM,    {265642, 285434} },
	{ PUB,     {256442, 288522} },
	{ TEMP,    {267637, 242752} },
	{ PRIEST,  {232919, 294735} },
	{ CHEONJI, {360931, 187024} },
	{ HONDEL,  {359758, 233913} }
};

#define ITEMTELEPORT_SPREAD 30

bool CItemTeleport::Use(CPlayer *pPlayer)
{
	if (!CanUse(pPlayer))
		return false;

	switch (m_pMacro->m_nTeleport[1])
	{
		case CItemInfo::TELEPORT::T_SINGLE:
		{
			int nX = g_mTeleportCoords[m_pMacro->m_nTeleport[2]][0];
			int nY = g_mTeleportCoords[m_pMacro->m_nTeleport[2]][1];
			pPlayer->Teleport(nX, nY, ITEMTELEPORT_SPREAD);

			break;
		}
		case CItemInfo::TELEPORT::T_PARTY:
		{
			int nX = g_mTeleportCoords[m_pMacro->m_nTeleport[2]][0];
			int nY = g_mTeleportCoords[m_pMacro->m_nTeleport[2]][1];

			auto pParty = CParty::FindParty(pPlayer->GetPartyID());
			if (pParty)
			{
				if (pParty->IsHead(pPlayer))
					pParty->Teleport(nX, nY, ITEMTELEPORT_SPREAD);
				else
					pPlayer->Teleport(nX, nY, ITEMTELEPORT_SPREAD);

				pParty->m_Access.Release();
			}
			else
			{
				pPlayer->Teleport(nX, nY, ITEMTELEPORT_SPREAD);
			}

			break;
		}
		case CItemInfo::TELEPORT::T_DUNGEON:
		case CItemInfo::TELEPORT::T_DAWN:
		{
			int nX = m_pMacro->m_nTeleport[0];
			int nY = m_pMacro->m_nTeleport[2];
			pPlayer->Teleport(nX, nY, ITEMTELEPORT_SPREAD);

			break;
		}
	}

	return true;
}

