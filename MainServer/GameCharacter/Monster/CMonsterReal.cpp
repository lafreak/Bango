#include "CMonsterReal.h"

void CMonsterReal::Die()
{
	AddGState(CGS_KO);
	SetTarget(NULL);
	SetAIS(AIS_DEAD);
	WriteInSight(S2C_ACTION, "db", GetID(), AT_DIE);
}
