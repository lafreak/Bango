#include "CZone.h"
#include <fstream>

CZone::CZone(int nZoneX, int nZoneY)
{
	m_data = nullptr;

	m_nZoneX = nZoneX;
	m_nZoneY = nZoneY;

	m_nAnchorX = nZoneX * 8192;
	m_nAnchorY = nZoneY * 8192;

	Load();
}

bool CZone::Load()
{
	char buf[20];
	sprintf(buf, "Maps/n_%03d_%03d.ksm", m_nZoneX, m_nZoneY);

	std::ifstream ksm(buf, std::ios::binary);

	if (!ksm) 
		return false;

	ksm.seekg(0, std::ios::end);
	int size = (int) ksm.tellg();
	ksm.seekg(0, std::ios::beg);
	
	if (size != KSM_TOTAL_SIZE) {
		ksm.close();
		printf(KRED "CZone::Load KSM size is wrong [0x%08X]\n" KNRM, size);
		return false;
	}
	
	Destroy();
	m_data = new char[KSM_TOTAL_CELLS_SIZE];

	ksm.ignore(4);
	ksm.read(m_data, KSM_TOTAL_CELLS_SIZE);
	ksm.close();

	return true;
}

bool CZone::Check(int nX, int nY, BYTE byType)
{
	if (!m_data) return false;

	int nOffsetX = (nX - m_nAnchorX) / 32;
	int nOffsetY = (nY - m_nAnchorY) / 32;

	if (nOffsetX < 0 || nOffsetX >= KSM_WIDTH || nOffsetY < 0 || nOffsetY >= KSM_WIDTH)
	{
		printf(KRED "CZone::Check Call to wrong Zone (%d %d)\n" KNRM, nOffsetX, nOffsetY);
		return false;
	}

	char* data = m_data + ((nOffsetX + nOffsetY * KSM_WIDTH) * KSM_CELL_SIZE);

	WORD wMainType =	((WORD*)data)[0];
	WORD wSubType =		((WORD*)data)[1];

	switch (byType)
	{
		case ZT_MONSTER:
			return !wMainType && !(wSubType & ZONE_TWOWAY_PORTAL); //data[0] == 0 && data[1] == 0 && !(data[2] & ZONE_TWOWAY_PORTAL);
		case ZT_SAFEZONE:
			return wMainType || (wSubType & ZONE_TWOWAY_PORTAL);
		case ZT_CASTLE:
			return wSubType == ZONE_CASTLE;
		case ZT_TOWN:
			return wSubType == ZONE_TOWN;
		case ZT_PKFREE:
			return wSubType == ZONE_PK_FREE;
	}

	return false;
}

void CZone::Destroy()
{
	if (m_data)
		delete[] m_data;
}
