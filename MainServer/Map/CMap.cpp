#include "CMap.h"

CTile* CMap::g_Tiles[TILE_LEN][TILE_LEN];
CZone* CMap::g_Zones[ZONE_LEN][ZONE_LEN];

void CMap::LoadMaps()
{
	for (int i = 0; i < TILE_LEN; i++)
		for (int j = 0; j < TILE_LEN; j++)
			CMap::g_Tiles[i][j] = new CTile;

	for (int i = 0; i < ZONE_LEN; i++)
		for (int j = 0; j < ZONE_LEN; j++)
			CMap::g_Zones[i][j] = new CZone(i, j);
}

void CMap::UnloadMaps()
{
	for (int i = 0; i < TILE_LEN; i++)
		for (int j = 0; j < TILE_LEN; j++)
			delete CMap::g_Tiles[i][j];

	for (int i = 0; i < ZONE_LEN; i++)
		for (int j = 0; j < ZONE_LEN; j++)
			delete CMap::g_Zones[i][j];
}

CTile* CMap::GetTile(int nTileX, int nTileY)
{
	if (nTileX < 0 || nTileX < 0 || nTileY >= TILE_LEN || nTileY >= TILE_LEN) {
		printf(KRED "CMap::GetTile: Access to bad tile sector: %d %d.\n" KNRM, nTileX, nTileY);
		return NULL;
	}

	return g_Tiles[nTileX][nTileY];
}

CZone * CMap::GetZone(int nZoneX, int nZoneY)
{
	if (nZoneX < 0 || nZoneX < 0 || nZoneY >= ZONE_LEN || nZoneY >= ZONE_LEN) {
		printf(KRED "CMap::GetZone: Access to bad zone sector: %d %d.\n" KNRM, nZoneX, nZoneY);
		return NULL;
	}

	return g_Zones[nZoneX][nZoneY];
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

void CMap::GetMonsterListAround(CCharacter *pCharacter, int nDistance, MonsterList& list)
{
	MapInfo m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	for (int i = m.wTileX-1; i <= m.wTileX+1; i++) {
		for (int j = m.wTileY-1; j <= m.wTileY+1; j++) {
			auto pTile = GetTile(i, j);
			if (pTile)
				pTile->GetMonsterListAround(pCharacter, nDistance, list);
		}
	}
}

CPlayer* CMap::GetClosestNormalPlayer(CCharacter *pCharacter, int nDistance)
{
	MapInfo m = GetMapInfo(pCharacter->GetX(), pCharacter->GetY());

	PlayerList list;
	GetPlayerListAround(pCharacter, nDistance, list);

	CPlayer *pPlayer=NULL;
	int nCurDist = -1;

	for (PlayerList::iterator it = list.begin(); it != list.end(); it++)
	{
		if (!(*it)->IsNormal()) 
		{
			(*it)->m_Access.Release();
			continue;
		}

		int nDist = pCharacter->GetDistance(*it);

		if (nCurDist == -1)
		{
			pPlayer = (*it);
			nCurDist = nDist;
			continue;
		}

		if (pCharacter->GetDistance(*it) < nCurDist) 
		{
			pPlayer->m_Access.Release();
			pPlayer = (*it);
			nCurDist = nDist;
			continue;
		}

		(*it)->m_Access.Release();
	}

	return pPlayer;
}

MapInfo CMap::GetMapInfo(int nX, int nY)
{
	MapInfo mapInfo;

	mapInfo.wTileX = nX / 1024;
	mapInfo.wTileY = nY / 1024;

	mapInfo.wOffsetX = nX % 1024;
	mapInfo.wOffsetY = nY % 1024;

	mapInfo.wZoneX = nX / 8192;
	mapInfo.wZoneY = nY / 8192;

	return mapInfo;
}

bool CMap::CheckZone(int nX, int nY, BYTE byType)
{
	auto m = GetMapInfo(nX, nY);

	auto pZone = GetZone(m.wZoneX, m.wZoneY);
	if (!pZone) 
		return false;

	return pZone->Check(nX, nY, byType);
}

bool CMap::CheckZone(CCharacter * pCharacter, BYTE byType)
{
	return CheckZone(pCharacter->GetX(), pCharacter->GetY(), byType);
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
