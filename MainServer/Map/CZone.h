#ifndef _CZONE_
#define _CZONE_

#include <minwindef.h>
#include <common.h>

#define KSM_WIDTH 256
#define KSM_CELL_SIZE 4
#define KSM_HEADER_SIZE 4
#define KSM_TOTAL_CELLS_SIZE (KSM_WIDTH * KSM_WIDTH * KSM_CELL_SIZE)
#define KSM_TOTAL_SIZE (KSM_TOTAL_CELLS_SIZE + KSM_HEADER_SIZE)

/**
	Represents square zone of 8192x8192 cells.
	Encapsulates one .KSM (Kal Server Map) file per instance.
*/
class CZone
{
	char* m_data;
	int m_nZoneX, m_nZoneY;
	int m_nAnchorX, m_nAnchorY;

	void Destroy();

public:

	/**
		Declares zone X & Y for further loading from file: n_00X_00Y.ksm.
		\param nZoneX X zone coordinate (WorldX / 8192).
		\param nZoneY Y zone coordinate (WorldY / 8192).

	*/
	CZone(int nZoneX, int nZoneY);

	/**
		Destructor that deallocates .KSM data if exists.
	*/
	~CZone() { Destroy(); }

	/**
		Loads data from .KSM file.
		Deallocates previous data if any.
		NOT thread-safe, so do not reload after server start.
		\return false if file does not exist or file size mismatches, true otherwise
	*/
	bool Load();
	
	/**
		Tests certain cell (X, Y) for zone type.
		Available tests:
		- ZT_MONSTER: area free for monsters for walk and chase;
		- ZT_SAFEZONE: area with entry prohibition for monsters;
		- ZT_CASTLE: castle siege area;
		- ZT_TOWN: city/town area;
		- ZT_PKFREE: area with entry prohibition for assasins.
		\return false if prohibited, true otherwise
	*/
	bool Check(int nX, int nY, BYTE byType);
};

#endif
