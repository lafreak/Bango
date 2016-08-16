#include "CMap.h"

CTile* CMap::g_Tiles[TILE_LEN][TILE_LEN];

void CMap::LoadMaps()
{
	for (int i = 0; i < TILE_LEN; i++)
		for (int j = 0; j < TILE_LEN; j++)
			CMap::g_Tiles[i][j] = new CTile;
}

CTile* CMap::GetTile(int nTileX, int nTileY)
{
	if (nTileX < 0 || nTileX < 0 || nTileY >= TILE_LEN || nTileY >= TILE_LEN) {
		printf(KRED "CMap::GetTile: Access to bad tile sector: %d %d.\n" KNRM, nTileX, nTileY);
		return NULL;
	}

	return g_Tiles[nTileX][nTileY];
}

void CMap::Add(int nTileX, int nTileY, CCharacter* pCharacter)
{
	auto pTile = GetTile(nTileX, nTileY);
	if (pTile)
		pTile->Add(pCharacter);
}

void CMap::Add(MapInfo mapInfo, CCharacter* pCharacter)
{
	Add(mapInfo.wTileX, mapInfo.wTileY, pCharacter);
}

void CMap::Add(CCharacter* pCharacter)
{
	Add(GetMapInfo(pCharacter->GetX(), pCharacter->GetY()), pCharacter);
}

void CMap::Remove(int nTileX, int nTileY, CCharacter *pCharacter)
{
	auto pTile = GetTile(nTileX, nTileY);
	if (pTile)
		pTile->Remove(pCharacter);
}

void CMap::Remove(MapInfo mapInfo, CCharacter *pCharacter)
{
	Remove(mapInfo.wTileX, mapInfo.wTileY, pCharacter);
}

void CMap::Remove(CCharacter *pCharacter)
{
	Remove(GetMapInfo(pCharacter->GetX(), pCharacter->GetY()), pCharacter);
}

void CMap::GetCharacterListAround(CCharacter *pCharacter, int nDistance, CharacterList& list)
{
	MapInfo m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	for (int i = m.wTileX-1; i <= m.wTileX+1; i++) {
		for (int j = m.wTileY-1; j <= m.wTileY+1; j++) {
			auto pTile = GetTile(i, j);
			if (pTile)
				pTile->GetCharacterListAround(pCharacter, nDistance, list);
		}
	}
}

void CMap::GetPlayerListAround(CCharacter *pCharacter, int nDistance, PlayerList& list)
{
	MapInfo m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	for (int i = m.wTileX-1; i <= m.wTileX+1; i++) {
		for (int j = m.wTileY-1; j <= m.wTileY+1; j++) {
			auto pTile = GetTile(i, j);
			if (pTile)
				pTile->GetPlayerListAround(pCharacter, nDistance, list);
		}
	}
}

MapInfo CMap::GetMapInfo(int nX, int nY)
{
	MapInfo mapInfo;

	mapInfo.wTileX = nX / 1024;
	mapInfo.wTileY = nY / 1024;

	mapInfo.wOffsetX = nX % 1024;
	mapInfo.wOffsetY = nY % 1024;

	return mapInfo;
}

void CMap::SendPacket(CCharacter *pCharacter, Packet& packet)
{
	auto m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	for (int i = m.wTileX-1; i <= m.wTileX+1; i++) {
		for (int j = m.wTileY-1; j <= m.wTileY+1; j++) {
			auto pTile = GetTile(i, j);
			if (pTile)
				pTile->SendPacket(pCharacter, packet);
		}
	}
}