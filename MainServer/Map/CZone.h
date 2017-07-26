#ifndef _CZONE_
#define _CZONE_

#include <minwindef.h>
#include <common.h>

#define KSM_SIZE 256
#define KSM_POINT_SIZE 4

class CZone
{
	char*** m_data;
	int m_nZoneX, m_nZoneY;

	void Destroy();

public:
	CZone(int nZoneX, int nZoneY);
	~CZone() { Destroy(); }

	bool Load();
	
	bool Check(int nX, int nY, BYTE byType);
};

#endif
