#include "CMonsterMaguni.h"

void CMonsterMaguni::Die()
{
	AddGState(CGS_KNEE);
	SetTarget(NULL);
	SetTimer(std::bind(&CMonster::OnRemove, this), 10000);
	WriteInSight(S2C_ACTION, "db", GetID(), AT_KNEE);
}

