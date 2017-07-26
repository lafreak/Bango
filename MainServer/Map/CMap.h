#ifndef _CMAP_
#define _CMAP_

#include "CTile.h"
#include "CZone.h"

#define TILE_LEN 400
#define ZONE_LEN 50

struct MapInfo
{
	WORD wTileX, wTileY;
	WORD wOffsetX, wOffsetY;
	WORD wZoneX, wZoneY;

	bool equalTile(MapInfo& mapInfo) {
		return mapInfo.wTileX == wTileX && mapInfo.wTileY == wTileY;
	}

	bool equalZone(MapInfo& mapInfo) {
		return mapInfo.wZoneX == wZoneX && mapInfo.wZoneY == wZoneY;
	}
};

class CMap
{

public:

	static CTile *g_Tiles[TILE_LEN][TILE_LEN];
	static CZone *g_Zones[ZONE_LEN][ZONE_LEN];

	static void LoadMaps();
	static void UnloadMaps();
	static void Add(int nTileX, int nTileY, CCharacter *pCharacter);
	static void Add(MapInfo mapInfo, CCharacter *pCharacter);
	static void Add(CCharacter *pCharacter);
	static void Remove(int nTileX, int nTileY, CCharacter *pCharacter);
	static void Remove(MapInfo mapInfo, CCharacter *pCharacter);
	static void Remove(CCharacter *pCharacter);
	static void SendPacket(CCharacter *pCharacter, Packet& packet);

	// Remember to run m_Access.Release on each used object in the list.
	static void GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list);
	static void GetPlayerListAround(CCharacter *pCharacter, int nDistance, PlayerList& list);
	static void GetMonsterListAround(CCharacter *pCharacter, int nDistance, MonsterList& list);
	static CPlayer* GetClosestNormalPlayer(CCharacter *pCharacter, int nDistance);

	static CTile* GetTile(int nTileX, int nTileY);
	static CZone* GetZone(int nZoneX, int nZoneY);
	static MapInfo GetMapInfo(int nX, int nY); 

	static bool CheckZone(int nX, int nY, BYTE byType);
	static bool CheckZone(CCharacter *pCharacter, BYTE byType);
};

#endif
