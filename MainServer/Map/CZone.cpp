#include "CZone.h"
#include <fstream>

CZone::CZone(int nZoneX, int nZoneY)
{
	m_data = nullptr;

	m_nZoneX = nZoneX;
	m_nZoneY = nZoneY;

	Load();
}

bool CZone::Load()
{
	Destroy();

	char buf[32];
	sprintf(buf, "Maps/n_%03d_%03d.ksm", m_nZoneX, m_nZoneY);

	std::ifstream ksm(buf, std::ios::binary);
	if (!ksm) {
		//printf(KRED "CZone::Load Cannot open KSM [%d,%d]\n" KNRM, m_nZoneX, m_nZoneY);
		return false;
	}

	std::streampos fsize = 0;
	ksm.seekg(0, std::ios::end);
	fsize = ksm.tellg() - fsize;
	ksm.seekg(0, std::ios::beg);
	
	if (fsize != 0x40004) {
		ksm.close();
		printf(KRED "CZone::Load KSM size is wrong [0x%08X]\n" KNRM, (int) fsize);
		return false;
	}

	m_data = new char[256 * 256 * 4];

	ksm.ignore(4);
	ksm.read(m_data, 256 * 256 * 4);
	ksm.close();

	return true;
}

bool CZone::Check(int nX, int nY, BYTE byType)
{
	if (!m_data) return false;

	int nOffsetX = nX - (m_nZoneX * 8192);
	int nOffsetY = nY - (m_nZoneY * 8192);

	if (nOffsetX < 0 || nOffsetX >= 8192 || nOffsetY < 0 || nOffsetY >= 8192)
	{
		printf(KRED "CZone::Check Call to wrong Zone (%d %d)\n" KNRM, nOffsetX, nOffsetY);
		return false;
	}

	int nZoneX = nOffsetX / 32;
	int nZoneY = nOffsetY / 32;

	char* data = m_data + ((nZoneX + nZoneY * 256) * 4);

	switch (byType)
	{
		case ZT_MONSTER:
			return data[0] == 0 && data[1] == 0 && !(data[2] & ZONE_TWOWAY_PORTAL);
		case ZT_SAFEZONE:
			return data[0] != 0 || data[1] != 0 || (data[2] & ZONE_TWOWAY_PORTAL);
		case ZT_CASTLE:
			return data[2] == ZONE_CASTLE;
		case ZT_TOWN:
			return data[2] == ZONE_TOWN;
		case ZT_PKFREE:
			return data[2] == ZONE_PK_FREE;
	}

	return false;
}

void CZone::Destroy()
{
	if (m_data)
		delete[] m_data;
}
