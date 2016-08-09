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

void CMap::Remove(int nTileX, int nTileY, int nID)
{
	auto pTile = GetTile(nTileX, nTileY);
	if (pTile)
		pTile->Remove(nID);
}

void CMap::Remove(MapInfo mapInfo, int nID)
{
	Remove(mapInfo.wTileX, mapInfo.wTileY, nID);
}

MapInfo CMap::GetMapInfo(int nX, int nY)
{
	MapInfo mapInfo;

	mapInfo.wTileX = nX / 1024;//(nX - (mapInfo.byMapX << 13)) >> 10;
	mapInfo.wTileY = nY / 1024;//(nY - (mapInfo.byMapY << 13)) >> 10;

	mapInfo.wOffsetX = nX % 1024;//nX - ((mapInfo.byMapX << 13) + (mapInfo.byTileX >> 10));
	mapInfo.wOffsetY = nY % 1024;//nY - ((mapInfo.byMapY << 13) + (mapInfo.byTileY >> 10));

	return mapInfo;
}

void CMap::SendPacket(int nX, int nY, Packet& packet)
{
	auto m = GetMapInfo(nX, nY);

	CTile *pTile=NULL;

	// Main
	pTile = GetTile(m.wTileX, m.wTileY);
	if (pTile)
		pTile->SendPacket(nX, nY, packet);

	// Right
	if (m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Left
	if (m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Top
	if (m.wOffsetY < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Bottom
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Upper-right
	if (m.wOffsetY < MAX_PLAYER_SIGHT && m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Upper-left
	if (m.wOffsetY < MAX_PLAYER_SIGHT && m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Bottom-right
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT && m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}

	// Bottom-left
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT && m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(nX, nY, packet);
	}
}

void CMap::SendPacket(CCharacter *pCharacter, Packet& packet)
{
	auto m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	CTile *pTile=NULL;

	// Main
	pTile = GetTile(m.wTileX, m.wTileY);
	if (pTile)
		pTile->SendPacket(pCharacter, packet);

	// Right
	if (m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Left
	if (m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Top
	if (m.wOffsetY < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Bottom
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Upper-right
	if (m.wOffsetY < MAX_PLAYER_SIGHT && m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Upper-left
	if (m.wOffsetY < MAX_PLAYER_SIGHT && m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY-1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Bottom-right
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT && m.wOffsetX > 1024 - MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX+1, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}

	// Bottom-left
	if (m.wOffsetY > 1024 - MAX_PLAYER_SIGHT && m.wOffsetX < MAX_PLAYER_SIGHT) {
		pTile = GetTile(m.wTileX-1, m.wTileY+1);
		if (pTile)
			pTile->SendPacket(pCharacter, packet);
	}
}