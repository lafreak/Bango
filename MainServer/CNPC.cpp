#include <Socket/CSocket.h>

#include "CNPC.h"
#include "Map/CMap.h"

#include <TinyXML2/tinyxml2.h>

CNPC::CNPC(NPC_DESC& desc): CCharacter()
{
	m_wIndex = desc.wIndex;

	m_nShape = desc.nShape;
	m_nHtml = desc.nHtml;

	m_nX = desc.nX;
	m_nY = desc.nY;
	m_nZ = desc.nZ;

	SetDirection(desc.nDirX, desc.nDirY);
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

Packet CNPC::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

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

	XMLElement *pNPC = pRoot->FirstChildElement("npc");

	while (pNPC != NULL)
	{
		NPC_DESC desc;
		memset(&desc, 0, sizeof(NPC_DESC));

		desc.wIndex = pNPC->IntAttribute("index");
		desc.nShape = pNPC->IntAttribute("shape");
		desc.nHtml = pNPC->IntAttribute("html");
		desc.nX = pNPC->IntAttribute("x");
		desc.nY = pNPC->IntAttribute("y");
		desc.nZ = pNPC->IntAttribute("z");
		desc.nDirX = pNPC->IntAttribute("dirx");
		desc.nDirY = pNPC->IntAttribute("diry");

		auto pNPCEx = new CNPC(desc);
		CMap::Add(CMap::GetMapInfo(desc.nX, desc.nY), pNPCEx);

		pNPC = pNPC->NextSiblingElement("npc");
	}

	return true;
}