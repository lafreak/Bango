#include "CParty.h"

PartyMap CParty::g_mParty;
std::mutex CParty::g_mxParty;

int CParty::g_nMaxIID;
std::mutex CParty::g_mxMaxIID;

CParty::CParty(CPlayer* pPlayer, CPlayer* pPlayer2)
{
	m_Members.push_back(pPlayer);
	m_Members.push_back(pPlayer2);

	m_nID = NewIID();

	Add(this);
}

void CParty::Add(CParty* pParty)
{
	g_mxParty.lock();

	if (g_mParty.find(pParty->GetIID()) == g_mParty.end())
		g_mParty[pParty->GetIID()] = pParty;

	g_mxParty.unlock();
}

void CParty::AddMember(CPlayer* pPlayer)
{
    m_xMembers.lock();

	m_Members.push_back(pPlayer);

	m_xMembers.unlock();
}

void CParty::Remove(CParty* pParty)
{
	g_mxParty.lock();

	PartyMap::iterator it = g_mParty.find(pParty->GetIID());
	if(it != g_mParty.end())
		g_mParty.erase(it);

	g_mxParty.unlock();
}

void CParty::RemoveMember(CPlayer* pPlayer)
{
	m_xMembers.lock();

	MemberVec::iterator it = std::find(m_Members.begin(), m_Members.end(), pPlayer);
	if(it != m_Members.end())
		m_Members.erase(it);

	m_xMembers.unlock();
}

int CParty::NewIID(){

	g_mxMaxIID.lock();
	g_nMaxIID++;
	g_mxMaxIID.unlock();

	return g_nMaxIID;
}

void CParty::Discard()
{
	m_Members[0]->Write(S2C_PARTYINFO,"b",0);
	Remove(this);
}

CParty* CParty::FindParty(CPlayer* pPlayer)
{
	for (auto &a : g_mParty)
	{
		for (int i = 0; i < a.second->m_Members.size(); i++)
		{
			if (a.second->m_Members[i] == pPlayer)
			{
				a.second->m_Access.Grant();
				return a.second;
			}
		}
	}
	return NULL;
}

/*
keep me here i am just a draft <3
void CParty::UpdateParty()
{
	CParty* pParty = FindParty(id);

	if (pParty)
	{
		pParty->UpdatePartyInfo(pPlayer);
	    pParty->m_Access.Release();
	}
}

*/

void CParty::UpdatePartyInfo(CPlayer* pPlayer)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_UPDATEPARTY;

	char* end = CSocket::WritePacket(packet.data, "dbdd", 
		pPlayer->GetPID(), 
		P_CURHP, 
		pPlayer->GetCurHP(), 
		pPlayer->GetMaxHP());

	packet.wSize = end - ((char*)&packet);

	for (auto &a : m_Members)
		a->SendPacket(packet);
}

void CParty::SendPartyInfo()
{
	int byCount = m_Members.size();
	char* end;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_PARTYINFO;
	
	if (byCount >= 2)
	{
	    end = CSocket::WritePacket(packet.data, "b", byCount);
		for (auto &a : m_Members)
		{
			end =  CSocket::WritePacket(end, "dsbbww",
				a->GetPID(), 
	        	a->GetName().c_str(), 
	        	a->GetClass(), 
	        	a->GetLevel(), 
	        	a->GetCurHP(), 
	        	a->GetMaxHP());
		}
    }
    else
    {
    	end = CSocket::WritePacket(packet.data,"b",0);
    }

	packet.wSize = end - ((char*)&packet);

	for(auto &a : m_Members)
			a->SendPacket(packet);		
}

