#include "CParty.h"

PartyMap CParty::g_mParty;
std::mutex CParty::g_mxParty;

int CParty::g_nMaxID = 1;
std::mutex CParty::g_mxMaxID;

CParty::CParty(CPlayer* pLeader, CPlayer* pPlayer)
{
	m_vMembers.push_back(pLeader);
	m_vMembers.push_back(pPlayer);

	m_nID = NewID();

	pLeader->Lock();
	pPlayer->Lock();

	pLeader->SetPartyID(m_nID);
	pPlayer->SetPartyID(m_nID);

	pLeader->Unlock();
	pPlayer->Unlock();

	CParty::Add(this);

	m_Access.Grant();
}

CParty::~CParty()
{
	CParty::Remove(this);

	while (m_Access.IsBusy()) {
		printf("CParty::~CParty: Party is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

int CParty::NewID() {

	g_mxMaxID.lock();
	g_nMaxID++;
	g_mxMaxID.unlock();

	return g_nMaxID;
}

void CParty::Add(CParty* pParty)
{
	g_mxParty.lock();

	if (g_mParty.find(pParty->GetID()) == g_mParty.end())
		g_mParty[pParty->GetID()] = pParty;

	printf("%d\n", (int) g_mParty.size());

	g_mxParty.unlock();
}

void CParty::Remove(CParty* pParty)
{
	g_mxParty.lock();

	PartyMap::iterator it = g_mParty.find(pParty->GetID());
	if (it != g_mParty.end())
		g_mParty.erase(it);

	printf("%d\n", (int) g_mParty.size());

	g_mxParty.unlock();
}

void CParty::AddMember(CPlayer* pPlayer)
{
	m_mxThis.lock();

	m_vMembers.push_back(pPlayer);

	pPlayer->Lock();
	pPlayer->SetPartyID(m_nID);
	pPlayer->Unlock();

	m_mxThis.unlock();
}

void CParty::RemoveMember(CPlayer* pPlayer)
{
	m_mxThis.lock();

	MemberVec::iterator it = std::find(m_vMembers.begin(), m_vMembers.end(), pPlayer);
	if (it != m_vMembers.end())
		m_vMembers.erase(it);

	pPlayer->Lock();
	pPlayer->SetPartyID(0);
	pPlayer->Unlock();

	m_mxThis.unlock();
}

void CParty::Discard()
{
	m_vMembers[0]->m_Access.Grant();
	m_vMembers[0]->Lock();
	m_vMembers[0]->SetPartyID(0);
	m_vMembers[0]->Write(S2C_PARTYINFO, "b", 0);
	m_vMembers[0]->Unlock();
	m_vMembers[0]->m_Access.Release();
}

CParty* CParty::FindParty(int nID)
{
	/*
	for (auto &a : g_mParty)
	{
		for (int i = 0; i < a.second->m_vMembers.size(); i++)
		{
			if (a.second->m_vMembers[i] == pPlayer)
			{
				a.second->m_Access.Grant();
				return a.second;
			}
		}
	}
	return NULL;
	*/

	if (nID <= 0)
		return NULL;

	CParty *pParty = NULL;

	g_mxParty.lock();

	if (g_mParty.find(nID) != g_mParty.end()) {
		pParty = g_mParty[nID];
		pParty->m_Access.Grant();
	}

	g_mxParty.unlock();

	return pParty;
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

	for (auto &a : m_vMembers)
		a->SendPacket(packet);
}

void CParty::GetPlayerList(MemberVec& list)
{
	for (auto &a : m_vMembers)
	{
		a->m_Access.Grant();
		list.push_back(a);
	}
}

void CParty::SendPartyInfo()
{
	m_mxThis.lock();

	int byCount = m_vMembers.size();
	char* end;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_PARTYINFO;

	MemberVec members;
	GetPlayerList(members);

	if (byCount >= 2)
	{
		end = CSocket::WritePacket(packet.data, "b", byCount);

		for (auto &a : members)
		{
			end = CSocket::WritePacket(end, "dsbbww",
				//end = CSocket::WritePacket(end, "dsbbdw",
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
		end = CSocket::WritePacket(packet.data, "b", 0);
	}

	packet.wSize = end - ((char*)&packet);

	for (auto &a : members)
	{
		a->SendPacket(packet);
		a->m_Access.Release();
	}

	m_mxThis.unlock();
}

