#include "CCharacter.h"

int CCharacter::g_nID = 1;

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