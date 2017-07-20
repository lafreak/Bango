#include "CItemGeneral.h"

#include "../GameCharacter/CPlayer.h"

bool CItemGeneral::Use(CPlayer *pPlayer)
{
	if (!CanUse(pPlayer))
		return false;

	return true;
}
