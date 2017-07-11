#include "CCharacter.h"

#include "../Map/CMap.h"

int CCharacter::g_nID = 1;
std::mutex CCharacter::g_mxID;

CCharacter::CCharacter(): m_Access()
{
	m_nID = NewID();//CCharacter::g_nID++;

	m_n64GState = 0;
	m_n64MState = 0;
	m_n64GStateEx = 0;
	m_n64MStateEx = 0;
}

int CCharacter::NewID()
{
	g_mxID.lock();

	int nID = g_nID++;
	
	g_mxID.unlock();

	return nID;
}

bool CCharacter::WriteInSight(BYTE byType, ...)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));

	packet.byType = byType;

	va_list va;
	va_start(va, byType);

	char* end = CSocket::WriteV(packet.data, va);

	va_end(va);

	packet.wSize = end - (char*)&packet;
	CMap::SendPacket(this, packet);

	return true;
}

void CCharacter::SendPacketInSight(Packet& packet)
{
	if (packet.wSize > 0)
		CMap::SendPacket(this, packet);
}

DWORD CCharacter::GetMaxHP() const
{
	return ((GetLevel() >= 96 ? 195 :
			(GetLevel() >= 91 ? 141.8147 :
			(GetLevel() >= 86 ? 111.426 :
			(GetLevel() >= 81 ? 91.758 :
			(GetLevel() >= 76 ? 78 :
			(GetLevel() >= 72 ? 67.8162 :
								52 )))))) * GetLevel() / 3) + 115 + 2 * GetHth() * GetHth() / g_denoHP[m_byClass];
}

WORD CCharacter::GetMaxMP() const
{
	return ((GetLevel() >= 96 ? 20 :
			(GetLevel() >= 91 ? 18 :
			(GetLevel() >= 86 ? 16 :
			(GetLevel() >= 81 ? 14 :
			(GetLevel() >= 76 ? 12 :
			(GetLevel() >= 72 ? 10 :
								8 )))))) * GetLevel()) + 140 + GetWis() + 2 * GetWis() * GetWis() / g_denoMP[m_byClass];
}

WORD CCharacter::GetHit() const
{
	return GetAgi() / 8 + 15 * GetStr() / 54;
}

WORD CCharacter::GetDodge() const
{
	return GetAgi() / 3;
}

WORD CCharacter::GetMinAttack() const
{
	return 1 + ((11 * GetStr() - 80) / 30) + ((GetAgi() - 5) / 11) + (7 * GetLevel() / 10);
}

WORD CCharacter::GetMaxAttack() const
{
	return ((8 * GetStr() - 25) / 15) + (18 * GetAgi() / 77) + GetLevel();
}

WORD CCharacter::GetMinMagic() const
{
	return (7 * GetInt() - 20) / 12 + GetWis() / 7;
}

WORD CCharacter::GetMaxMagic() const
{
	return 7 * GetInt() / 12 + 14 * GetWis() / 45;
}

WORD CCharacter::GetResist(BYTE byResist) const
{
	switch (byResist)
	{
		case RT_FIRE:
		case RT_ICE:
		case RT_LITNING:
			return GetInt() / 9;
		case RT_PALSY:
			return GetHth() / 9;
		case RT_CURSE:
			return GetWis() / 9;
	}
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
	return (int) sqrt(pow(m_nX - pCharacter->GetX(), 2) + pow(m_nY - pCharacter->GetY(), 2));
}
