#include "CCharacter.h"

int CCharacter::g_nID = 1;

WORD CCharacter::GetMaxHP() const
{
	return ((m_byLevel >= 96 ? 195 : 
			(m_byLevel >= 91 ? 141.8147 : 
			(m_byLevel >= 86 ? 111.426 : 
			(m_byLevel >= 81 ? 91.758 : 
			(m_byLevel >= 76 ? 78 : 
			(m_byLevel >= 72 ? 67.8162 : 
								52 )))))) * m_byLevel / 3) + 115 + 2 * m_wHth * m_wHth / g_denoHP[m_byClass];
}

WORD CCharacter::GetMaxMP() const
{
	return ((m_byLevel >= 96 ? 20 : 
			(m_byLevel >= 91 ? 18 : 
			(m_byLevel >= 86 ? 16 : 
			(m_byLevel >= 81 ? 14 : 
			(m_byLevel >= 76 ? 12 : 
			(m_byLevel >= 72 ? 10 : 
								8 )))))) * m_byLevel) + 140 + m_wWis + 2 * m_wWis * m_wWis / g_denoMP[m_byClass];
}

WORD CCharacter::GetHit() const
{
	return m_wDex / 8 + 15 * m_wStr / 54;
}

WORD CCharacter::GetDodge() const
{
	return m_wDex / 3;
}

WORD CCharacter::GetMinAttack() const
{
	return 1 + ((11 * m_wStr - 80) / 30) + ((m_wDex - 5) / 11) + (7 * m_byLevel / 10);
}

WORD CCharacter::GetMaxAttack() const
{
	return ((8 * m_wStr - 25) / 15) + (18 * m_wDex / 77) + m_byLevel;
}

WORD CCharacter::GetMinMagic() const
{
	return (7 * m_wInt - 20) / 12;
}

WORD CCharacter::GetMaxMagic() const
{
	return 7 * m_wInt / 12;
}

WORD CCharacter::GetResist(BYTE byResist) const
{
	switch (byResist)
	{
		case RT_FIRE:
		case RT_ICE:
		case RT_LITNING:
			return m_wInt / 9;
		case RT_PALSY:
			return m_wHth / 9;
		case RT_CURSE:
		default:
			return m_wWis / 9;
	}
}

CCharacter::CCharacter(): m_Access()
{
	m_nID = CCharacter::g_nID++;
}

void CCharacter::AddGState(__int64 n64GState)
{
	m_n64GState |= n64GState;
}

void CCharacter::AddMState(__int64 n64MState)
{
	m_n64MState |= n64MState;
}

void CCharacter::AddGStateEx(__int64 n64GStateEx)
{
	m_n64GStateEx |= n64GStateEx;
}

void CCharacter::AddMStateEx(__int64 n64MStateEx)
{
	m_n64MStateEx |= n64MStateEx;
}

void CCharacter::SubGState(__int64 n64GState)
{
	m_n64GState &= ~n64GState;
}

void CCharacter::SubMState(__int64 n64MState)
{
	m_n64MState &= ~n64MState;
}

void CCharacter::SubGStateEx(__int64 n64GStateEx)
{
	m_n64GStateEx &= ~n64GStateEx;
}

void CCharacter::SubMStateEx(__int64 n64MStateEx)
{
	m_n64MStateEx &= ~n64MStateEx;
}

bool CCharacter::IsGState(__int64 n64GState)
{
	return m_n64GState & n64GState;
}

bool CCharacter::IsMState(__int64 n64MState)
{
	return m_n64MState & n64MState;
}

bool CCharacter::IsGStateEx(__int64 n64GStateEx)
{
	return m_n64GStateEx & n64GStateEx;
}

bool CCharacter::IsMStateEx(__int64 n64MStateEx)
{
	return m_n64MStateEx & n64MStateEx;
}

void CCharacter::SetDirection(int nX, int nY)
{
	if (!nX && !nY) return;

	float absX = abs(nX);
	float absY = abs(nY);

	if (absX >= absY && absX > 127)
	{
		nY = 127 * nY / absX;
		nX = (((nX <= 0) - 1) & 0xFE) - 127;
	}
	else if (absX < absY && absY > 127)
	{
		nX = 127 * nX / absY;
		nY = (((nY <= 0) - 1) & 0xFE) - 127;
	}

	m_wDir = nY + ((nX << 8) & 0xFF00);
}

BYTE CCharacter::GetMoveAction(CCharacter *pCharacter, char byX, char byY)
{
	float fDistanceCur = sqrt(pow(m_nX - byX - pCharacter->GetX(), 2) + pow(m_nY - byY - pCharacter->GetY(), 2));
	float fDistanceDest = sqrt(pow(m_nX - pCharacter->GetX(), 2) + pow(m_nY - pCharacter->GetY(), 2));

	if (fDistanceCur <= MAX_PLAYER_SIGHT && fDistanceDest <= MAX_PLAYER_SIGHT)
		return MV_AC_MOVE;

	if (fDistanceCur > MAX_PLAYER_SIGHT && fDistanceDest <= MAX_PLAYER_SIGHT)
		return MV_AC_CREATE;

	if (fDistanceCur <= MAX_PLAYER_SIGHT && fDistanceDest > MAX_PLAYER_SIGHT)
		return MV_AC_DELETE;

	return MV_AC_NONE;
}

int CCharacter::GetDistance(CCharacter *pCharacter)
{
	return (int)sqrt(pow(m_nX - pCharacter->GetX(), 2) + pow(m_nY - pCharacter->GetY(), 2));
}