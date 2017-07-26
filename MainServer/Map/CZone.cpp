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

	char* bytes = new char[256 * 256 * 4];

	ksm.ignore(4);
	ksm.read(bytes, 256 * 256 * 4);
	ksm.close();

	m_data = new char**[256];
	for (int i = 0; i < 256; i++)
		m_data[i] = new char*[256];

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			m_data[i][j] = new char[4];

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int k = i + j * 256;
			k *= 4;

			for (int l = 0; l < 4; l++)
				m_data[i][j][l] = bytes[k+l];
		}
	}

	delete[] bytes;

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

	char* data = m_data[nZoneX][nZoneY];

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
	{
		for (int i = 0; i < KSM_SIZE; i++)
		{
			for (int j = 0; j < KSM_SIZE; j++)
				delete[] m_data[i][j];

			delete[] m_data[i];
		}

		delete[] m_data;
	}
}
