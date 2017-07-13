#include "CItemGeneral.h"

#include "../GameCharacter/CPlayer.h"


bool CItemGeneral::Use(CPlayer *pPlayer)
{
	if (!CanUse(pPlayer))
		return false;

	if (m_pMacro->m_bySubClass == ISC_REFRESH) 
	{
		pPlayer->Lock();

		pPlayer->UpdateProperty(P_CURHP, m_pMacro->m_nRefresh[CItemInfo::R_HP]);
		pPlayer->UpdateProperty(P_CURMP, m_pMacro->m_nRefresh[CItemInfo::R_MP]);

		pPlayer->Unlock();
	}
	else if (m_pMacro->m_bySubClass == ISC_ETC && m_pMacro->m_wTeleport >= 0)
	{
		switch (m_pMacro->m_wTeleport)
		{
			case CItemInfo::NARO_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(257303, 258710);
				else
					pPlayer->Teleport(257303, 258710);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::CARGO_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(264931, 262029);
				else
					pPlayer->Teleport(264931, 262029);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::GEUM_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(265642, 285434);
				else
					pPlayer->Teleport(265642, 285434);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::PUB_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(256442, 288522);
				else
					pPlayer->Teleport(256442, 288522);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::TEMP_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(267895, 242644);
				else
					pPlayer->Teleport(267895, 242644);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::PRIEST_PT:
			{
				CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());
				if (pParty && pParty->IsHead(pPlayer))
					pParty->Teleport(232828, 294721);
				else
					pPlayer->Teleport(232828, 294721);

				if (pParty)
					pParty->m_Access.Release();

				break;
			}
			case CItemInfo::NARO_INDIV:
			{
				pPlayer->Teleport(257303, 258710);
				break;
			}
			case CItemInfo::CARGO_INDIV:
			{
				pPlayer->Teleport(264931, 262029);
				break;
			}
			case CItemInfo::GEUM_INDIV:
			{
				pPlayer->Teleport(265642, 285434);
				break;
			}
			case CItemInfo::PUB_INDIV:
			{
				pPlayer->Teleport(256442, 288522);
				break;
			}
			case CItemInfo::TEMP_INDIV:
			{
				pPlayer->Teleport(267895, 242644);
				break;
			}
			case CItemInfo::PRIEST_INDIV:
			{
				pPlayer->Teleport(232828, 294721);
				break;
			}
    	}
    }

	if (m_pMacro->m_byEffect)
		pPlayer->WriteInSight(S2C_EFFECT, "db", pPlayer->GetID(), m_pMacro->m_byEffect);

	return true;
}