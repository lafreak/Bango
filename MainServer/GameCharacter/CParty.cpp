#include "CParty.h"

PartyMap CParty::g_mParty;
std::mutex CParty::g_mxParty;

int CParty::g_nMaxIID;
std::mutex CParty::g_mxMaxIID;

CParty::CParty(CPlayer* pPlayer, CPlayer* pPlayer2)
{
	m_vec.push_back(pPlayer);
	m_vec.push_back(pPlayer2);

	m_nID = NewIID();

	SendPartyInfo();

	Add(this);
}

void CParty::Add(CParty* pParty)
{
	g_mxParty.lock();

	if(g_mParty.find(pParty->GetIID()) == g_mParty.end())
		g_mParty[pParty->GetIID()] = pParty;

	g_mxParty.unlock();

}

void CParty::AddMember(CPlayer* pPlayer)
{
    m_xvec.lock();

	m_vec.push_back(pPlayer);

	m_xvec.unlock();
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
	m_xvec.lock();

	MemberVec::iterator it = std::find(m_vec.begin(), m_vec.end(), pPlayer);
	if(it != m_vec.end())
		m_vec.erase(it);

	m_xvec.unlock();
}

int CParty::NewIID(){

	g_mxMaxIID.lock();
	g_nMaxIID++;
	g_mxMaxIID.unlock();

	return g_nMaxIID;
}

CParty* CParty::FindParty(CPlayer* pPlayer)
{
	for(auto &a : g_mParty)
	{
		for(int i = 0; i <= a.second->m_vec.size(); i++)
		{
			if(a.second->m_vec[i] == pPlayer)
			{
				a.second->m_Access.Grant();
				return a.second;
			}
		}
	}
}

void CParty::UpdateParty(CPlayer* pPlayer)
{
	CParty* pParty = FindParty(pPlayer);

	if(pParty)
	{
		pParty->UpdatePartyInfo(pPlayer);
	    pParty->m_Access.Release();
	}
}
/*
void CParty::WriteParty(const char* szName, const char* szTemp)
{
	for (auto &a : m_vec)
		a->Write(S2C_CHATTING, "ss", szName, szTemp);
}
*/
//void CParty::UpdatePartyInfo(CPlayer* pPlayer, int byKind)
void CParty::UpdatePartyInfo(CPlayer* pPlayer)
{
	Packet packet;

	int byCount = m_vec.size();

	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_UPDATEPARTY;

	char* end = CSocket::WritePacket(packet.data, "dbdd", 
		pPlayer->GetPID(), 
		P_CURHP, 
		pPlayer->GetCurHP(), 
		pPlayer->GetMaxHP());
    
    printf("Value of curHP i am about to send: %d\n", pPlayer->GetCurHP());
	packet.wSize = end - ((char*)&packet);

	for (auto &a : m_vec)
		a->SendPacket(packet);

}

void CParty::SendPartyInfo()
{
	Packet packet;

	int byCount = m_vec.size();

	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_PARTYINFO;

	char* end;

	if (m_vec.size() >= 2)
	{

	    end = CSocket::WritePacket(packet.data, "b", byCount);

	for (auto &a : m_vec)
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

	for(auto &a : m_vec)
			a->SendPacket(packet);
		
}

