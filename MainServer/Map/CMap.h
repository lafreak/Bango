#ifndef _CMAP_
#define _CMAP_

#include "CTile.h"

#define TILE_LEN 400
#define MAP_LEN 50

struct MapInfo
{
	WORD wTileX, wTileY;
	WORD wOffsetX, wOffsetY;

	bool equalTile(MapInfo& mapInfo) {
		return mapInfo.wTileX == wTileX && mapInfo.wTileY == wTileY;
	}
};

class CMap
{

public:

	static CTile *g_Tiles[TILE_LEN][TILE_LEN];

	static void LoadMaps();
	static void Add(int nTileX, int nTileY, CCharacter *pCharacter);
	static void Add(MapInfo mapInfo, CCharacter *pCharacter);
	static void Add(CCharacter *pCharacter);
	static void Remove(int nTileX, int nTileY, CCharacter *pCharacter);
	static void Remove(MapInfo mapInfo, CCharacter *pCharacter);
	static void Remove(CCharacter *pCharacter);
	static void SendPacket(CCharacter *pCharacter, Packet& packet);

	// Remember to run m_Access.Release on each used object in the list.
	static void GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list);

	static CTile* GetTile(int nTileX, int nTileY);
	static MapInfo GetMapInfo(int nX, int nY); 
};

#endif