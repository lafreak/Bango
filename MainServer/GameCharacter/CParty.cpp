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
	pPlayer->SetPartyInviterID(0);

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
	pPlayer->SetPartyInviterID(0);
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
	Broadcast(S2C_UPDATEPARTY, "dbdd", pPlayer->GetID(), P_CURHP, pPlayer->GetCurHP(), pPlayer->GetMaxHP());
}

void CParty::UpdateMemberLevel(CPlayer * pPlayer)
{
	Broadcast(S2C_UPDATEPARTY, "dbb", pPlayer->GetID(), P_LEVEL, pPlayer->GetLevel());
}

void CParty::TickAll()
{
	g_mxParty.lock();

	for (auto &a : g_mParty)
	{
		a.second->m_Access.Grant();
		a.second->Tick();
		a.second->m_Access.Release();
	}

	g_mxParty.unlock();
}

//Intervall might be too fast.
void CParty::Tick()
{
	SendPositionInfo();
}

void CParty::Broadcast(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;

	Broadcast(packet);
}

void CParty::Broadcast(Packet & packet)
{
	m_mxThis.lock();

	for (auto &a : m_vMembers)
		a->SendPacket(packet);

	m_mxThis.unlock();
}

void CParty::SendPositionInfo()
{
	if (GetSize() < 2)
		return;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_PARTYMEMPOS;

	m_mxThis.lock();

	char* end = CSocket::WritePacket(packet.data, "b", GetSize());

	for (auto &a : m_vMembers)
		end = CSocket::WritePacket(end, "ddd", a->GetID(), a->GetX(), a->GetY());

	m_mxThis.unlock();

	packet.wSize = end - ((char*)&packet);

	Broadcast(packet);
}

void CParty::Teleport(std::vector<int> &vCoords)
{
	m_mxThis.lock();

	for (auto &a : m_vMembers)
		a->Teleport(vCoords);

	m_mxThis.unlock();
}

void CParty::SendPartyInfo()
{
	if (GetSize() < 2)
		return;

	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	packet.byType = S2C_PARTYINFO;

	m_mxThis.lock();

	char* end = CSocket::WritePacket(packet.data, "b", GetSize());

	for (auto &a : m_vMembers)
		end = CSocket::WritePacket(end, "dsbbww", // Inix forgot to change party HP to DWORD
			a->GetID(),
			a->GetName().c_str(),
			a->GetClass(),
			a->GetLevel(),
			a->GetCurHP(),
			a->GetMaxHP());

	m_mxThis.unlock();

	packet.wSize = end - ((char*)&packet);

	Broadcast(packet);
}
