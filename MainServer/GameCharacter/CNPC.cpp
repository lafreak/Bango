#include <Socket/CSocket.h>

#include "CNPC.h"
#include "../Map/CMap.h"

#include <TinyXML2/tinyxml2.h>

NPCMap CNPC::g_mNPC;
std::mutex CNPC::g_mxNPC;

CNPC::CNPC(NPC_DESC& desc): CCharacter()
{
	m_wIndex = desc.wIndex;

	m_nShape = desc.nShape;
	m_nHtml = desc.nHtml;

	m_nX = desc.nX;
	m_nY = desc.nY;
	m_nZ = desc.nZ;

	SetDirection(desc.nDirX - desc.nX, desc.nDirY - desc.nY);

	m_byKind = CK_NPC;
}

Packet CNPC::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	DWORD dwFlagItem=0;
	
	packet.byType = S2C_CREATENPC;

	char *end = CSocket::WritePacket(packet.data, "dwbdddwId", 
		m_nID, m_wIndex, m_nShape, m_nX, m_nY, m_nZ, m_wDir, m_n64GState, dwFlagItem);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

Packet CNPC::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = S2C_REMOVENPC;

	char *end = CSocket::WritePacket(packet.data, "d", m_nID);

	packet.wSize = end - ((char*)&packet);

	return packet;
}

bool CNPC::LoadNPC()
{
	using namespace tinyxml2;

	XMLDocument doc;

	if (doc.LoadFile("Config/InitNPC.xml") != XML_SUCCESS) {
		printf(KRED "Cannot open InitNPC.xml. (%s)\n" KNRM, doc.ErrorName());
		return false;
	}

	XMLElement *pRoot = doc.RootElement();
	if (!pRoot) {
		printf("Cannot find root element inside InitNPC.xml.\n");
		return false;
	}

	XMLElement *pNPCInfo = pRoot->FirstChildElement("npc");

	while (pNPCInfo != NULL)
	{
		NPC_DESC desc;
		memset(&desc, 0, sizeof(NPC_DESC));

		desc.wIndex = pNPCInfo->IntAttribute("index");
		desc.nShape = pNPCInfo->IntAttribute("shape");
		desc.nHtml = pNPCInfo->IntAttribute("html");
		desc.nX = pNPCInfo->IntAttribute("x");
		desc.nY = pNPCInfo->IntAttribute("y");
		desc.nZ = pNPCInfo->IntAttribute("z");
		desc.nDirX = pNPCInfo->IntAttribute("dirx");
		desc.nDirY = pNPCInfo->IntAttribute("diry");

		auto pNPC = new CNPC(desc);
		CMap::Add(pNPC);
		CNPC::Add(pNPC);

		pNPCInfo = pNPCInfo->NextSiblingElement("npc");
	}

	return true;
}

void CNPC::UnloadNPC()
{
	g_mxNPC.lock();

	for (auto& a: g_mNPC)
		delete a.second;

	g_mNPC.clear();

	g_mxNPC.unlock();
}

void CNPC::Add(CNPC* pNPC)
{
	g_mxNPC.lock();

	if (g_mNPC.find(pNPC->GetID()) == g_mNPC.end())
		g_mNPC[pNPC->GetID()] = pNPC;

	g_mxNPC.unlock();
}

void CNPC::Remove(CNPC* pNPC)
{
	g_mxNPC.lock();

	NPCMap::iterator it = g_mNPC.find(pNPC->GetID());
	if (it != g_mNPC.end())
		g_mNPC.erase(it);

	g_mxNPC.unlock();
}

CNPC* CNPC::FindNPC(int nID)
{
	CNPC *pNPC=NULL;

	g_mxNPC.lock();

	if (g_mNPC.find(nID) != g_mNPC.end()) {
		pNPC = g_mNPC[nID];
		pNPC->m_Access.Grant();
	}

	g_mxNPC.unlock();

	return pNPC;
}
