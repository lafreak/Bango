#include "CParty.h"

PartyMap CParty::g_mParty;
std::mutex CParty::g_mxParty;

int CParty::g_nMaxID = 1;
std::mutex CParty::g_mxMaxID;

CParty::CParty(CPlayer* pLeader, CPlayer* pPlayer)
{
	m_vMembers.push_back(pLeader);
	m_vMembers.push_back(pPlayer);

	m_nID = CParty::NewID();

	pLeader->Lock();
	pPlayer->Lock();

	pLeader->SetPartyID(m_nID);
	pPlayer->SetPartyID(m_nID);

	pLeader->Unlock();
	pPlayer->Unlock();

	CParty::Add(this);

	m_Access.Grant();

	SendPartyInfo();
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

	g_mxParty.unlock();
}

void CParty::Remove(CParty* pParty)
{
	g_mxParty.lock();

	PartyMap::iterator it = g_mParty.find(pParty->GetID());
	if (it != g_mParty.end())
		g_mParty.erase(it);

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

	SendPartyInfo();
}

void CParty::RemoveMember(CPlayer* pPlayer)
{
	m_mxThis.lock();

	auto it = std::find(m_vMembers.begin(), m_vMembers.end(), pPlayer);
	if (it != m_vMembers.end())
		m_vMembers.erase(it);

	pPlayer->Lock();
	pPlayer->SetPartyID(0);
	pPlayer->Write(S2C_PARTYINFO, "b", 0);
	pPlayer->Unlock();

	m_mxThis.unlock();

	SendPartyInfo();
}

void CParty::AddPending(int nID)
{
	 m_mxPending.lock();

	 m_vPending.push_back(nID);

	 m_mxPending.unlock();
}

void CParty::RemovePending(int nID)
{
	m_mxPending.lock();
	
	auto it = std::find(m_vPending.begin(), m_vPending.end(), nID);
	if (it != m_vPending.end())
		m_vPending.erase(it);

	m_mxPending.unlock();
}

bool CParty::FindPending(int nID)
{
	bool rtn = false;
	m_mxPending.lock();

	auto it = std::find(m_vPending.begin(), m_vPending.end(), nID);
	if (it != m_vPending.end())
		rtn = true;

	m_mxPending.unlock();

	return rtn;
}

bool CParty::IsHead(CPlayer *pPlayer)
{
	m_mxThis.lock();

	bool bIsHead = m_vMembers.size() > 0 && m_vMembers[0]->GetID() == pPlayer->GetID();

	m_mxThis.unlock();

	return bIsHead;
}

void CParty::Discard()
{
	m_vMembers[0]->m_Access.Grant();
	RemoveMember(m_vMembers[0]);
	m_vMembers[0]->m_Access.Release();
}

CParty* CParty::FindParty(int nID)
{
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

void CParty::UpdateMemberHP(CPlayer* pPlayer)
{
	m_mxThis.lock();

	/*
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
	*/

	PlayerVector members;
	GetPlayerList(members);

	for (auto &m : members)
	{
		m->Write(S2C_UPDATEPARTY, "dbdd", pPlayer->GetPID(), P_CURHP, pPlayer->GetCurHP(), pPlayer->GetMaxHP());
		m->m_Access.Release();
	}

	m_mxThis.unlock();
}

void CParty::UpdateMemberLevel(CPlayer * pPlayer)
{
	m_mxThis.lock();

	PlayerVector members;
	GetPlayerList(members);

	for (auto &m : members)
	{
		m->Write(S2C_UPDATEPARTY, "dbb", pPlayer->GetPID(), P_LEVEL, pPlayer->GetLevel());
		m->m_Access.Release();
	}

	m_mxThis.unlock();
}

void CParty::GetPlayerList(PlayerVector& list)
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

	int byCount = GetMemberAmount();
	char* end;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_PARTYINFO;

	PlayerVector members;
	GetPlayerList(members);

	if (byCount >= 2)
	{
		end = CSocket::WritePacket(packet.data, "b", byCount);

		for (auto &a : members)
		{
			end = CSocket::WritePacket(end, "dsbbww",
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

void CParty::ProcessMsg(char * szName, char * szMsg)
{
	m_mxThis.lock();

	PlayerVector members;
	GetPlayerList(members);

	for (auto &a : members)
	{
		a->Write(S2C_CHATTING, "ss", szName, szMsg);
		a->m_Access.Release();
	}

	m_mxThis.unlock();
}

