#include "CItemGeneral.h"

#include "../GameCharacter/CPlayer.h"


// ToDo: Find coords of Hondel / Cheonji
CoordsMap CItemGeneral::g_mTeleScrolls = {
	{ NARO,	   {257303, 258710} },
	{ CARGO,   {264931, 262029} },
	{ GEUM,    {265642, 285434} },
	{ PUB,     {256442, 288522} },
	{ TEMP,    {267895, 242644} },
	{ PRIEST,  {232828, 294721} },
	{ CHEONJI, {257303, 258710} },
	{ HONDEL,  {257303, 258710} }
};

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

	else if (m_pMacro->m_bySubClass == ISC_ETC)
	{
		if (m_pMacro->m_nTeleportKind >= 0)
			Teleport(pPlayer);			
    }

	if (m_pMacro->m_byEffect)
		pPlayer->WriteInSight(S2C_EFFECT, "db", pPlayer->GetID(), m_pMacro->m_byEffect);

	return true;
}

void CItemGeneral::Teleport(CPlayer* pPlayer)
{
	if (m_pMacro->m_nTeleportKind == 0)
	{
		int nX = g_mTeleScrolls[m_pMacro->m_wTeleportID][0];
		int nY = g_mTeleScrolls[m_pMacro->m_wTeleportID][1];

		if (m_pMacro->m_bTeleportType)
		{
			pPlayer->Teleport(nX, nY);
		}
		else
		{
			CParty* pParty = CParty::FindParty(pPlayer->GetPartyID());

			if (pParty)
			{
				if (pParty->IsHead(pPlayer))
					pParty->Teleport(nX, nY);
				else
					pPlayer->Teleport(nX, nY);

				pParty->m_Access.Release();
			}
			else
			{
				pPlayer->Teleport(nX, nY);
			}
		}
	}
	else
	{
		pPlayer->Teleport(m_pMacro->m_nX, m_pMacro->m_nY);
	}
}