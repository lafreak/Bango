#include "CMonsterReal.h"

void CMonsterReal::Die()
{
	AddGState(CGS_KO);
	SetTarget(NULL);
	SetTimer(std::bind(&CMonster::OnRemove, this), 0);
	WriteInSight(S2C_ACTION, "db", GetID(), AT_DIE);
}
