#include "CCharacter.h"

int CCharacter::g_nID = 1;

CCharacter::CCharacter(): m_Access()
{
	m_nID = CCharacter::g_nID++;
}

void CCharacter::AddGState(__int64 n64GState)
{
	Lock();
	m_n64GState |= n64GState;
	Unlock();
}

void CCharacter::AddMState(__int64 n64MState)
{
	Lock();
	m_n64MState |= n64MState;
	Unlock();
}

void CCharacter::AddGStateEx(__int64 n64GStateEx)
{
	Lock();
	m_n64GStateEx |= n64GStateEx;
	Unlock();
}

void CCharacter::AddMStateEx(__int64 n64MStateEx)
{
	Lock();
	m_n64MStateEx |= n64MStateEx;
	Unlock();
}

void CCharacter::SubGState(__int64 n64GState)
{
	Lock();
	m_n64GState &= ~n64GState;
	Unlock();
}

void CCharacter::SubMState(__int64 n64MState)
{
	Lock();
	m_n64MState &= ~n64MState;
	Unlock();
}

void CCharacter::SubGStateEx(__int64 n64GStateEx)
{
	Lock();
	m_n64GStateEx &= ~n64GStateEx;
	Unlock();
}

void CCharacter::SubMStateEx(__int64 n64MStateEx)
{
	Lock();
	m_n64MStateEx &= ~n64MStateEx;
	Unlock();
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