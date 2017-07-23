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

	m_wStrAdd = 0,
	m_wHthAdd = 0,
	m_wIntAdd = 0,
	m_wWisAdd = 0,
	m_wDexAdd = 0;

	m_wHitAdd = 0;
	m_wDodgeAdd = 0;

	m_dwMaxHPAdd = 0;
	m_wMaxMPAdd = 0;

	m_wMinAttackAdd = 0;
	m_wMaxAttackAdd = 0;
	m_wMinMagicAdd = 0;
	m_wMaxMagicAdd = 0;

	m_wResistFireAdd = 0;
	m_wResistIceAdd = 0;
	m_wResistLitningAdd = 0;
	m_wResistCurseAdd = 0;
	m_wResistPalsyAdd = 0;
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

WORD CCharacter::GetAttack() const
{
	WORD wMinAttack = GetMinAttack();
	WORD wMaxAttack = GetMaxAttack();
	return wMinAttack + (rand() % (wMaxAttack+1 - wMinAttack));
}

WORD CCharacter::GetMagic() const
{
	WORD wMinMagic = GetMinMagic();
	WORD wMaxMagic = GetMaxMagic();
	return wMinMagic + (rand() % (wMaxMagic+1 - wMinMagic));
}

bool CCharacter::CanAttack(CCharacter * pTarget) const
{
	if (!IsNormal())
		return false;

	if (!pTarget->IsNormal())
		return false;

	return true;
}

bool CCharacter::CheckHit(CCharacter * pTarget, int nAdd) const
{
	int nLevelDiff = (int) GetLevel() - (int) pTarget->GetLevel();
	
	if (nLevelDiff > 100)
		nLevelDiff = 100;
	else if (nLevelDiff < -100)
		nLevelDiff = -100;
	
	int nLevelOTP = g_nAddOTPLv[abs(nLevelDiff)];
	nLevelOTP = nLevelDiff < 0 ? -nLevelOTP : nLevelOTP;

	int nTotalHitPoint = GetHit() - pTarget->GetDodge() + nLevelOTP + nAdd;

	if (nTotalHitPoint > 41)
		nTotalHitPoint = 41;
	else if (nTotalHitPoint < -41)
		nTotalHitPoint = -41;

	int nChance = 0;
	if (nTotalHitPoint < 0)
		nChance = 100 - g_nHitChance[abs(nTotalHitPoint)];
	else
		nChance = g_nHitChance[nTotalHitPoint];

	return nChance >= (rand() % 100 + 1);
}

DWORD CCharacter::GetFinalDamage(CCharacter * pAttacker, DWORD dwDamage)
{
	int byLevelDiff = (int) pAttacker->GetLevel() - (int) GetLevel();

	int nDamage = (int) dwDamage + byLevelDiff * abs(byLevelDiff) / 4;

	if (nDamage < 0)
		nDamage = 0;

	return (DWORD) nDamage;
}

DWORD CCharacter::GetFatalDamage(DWORD dwFinalDamage, BYTE& byType)
{
	DWORD dwFatalDamage = 0;

	if (dwFatalDamage > 0)
		byType |= ATF_CRITICAL;

	return dwFinalDamage + dwFatalDamage; // Not implemented
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

Packet CCharacter::GenerateCreatePacket(bool bHero)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	return packet;
}

Packet CCharacter::GeneratePetPacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	return packet;
}

Packet CCharacter::GenerateDeletePacket()
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	return packet;
}

Packet CCharacter::GenerateMovePacket(BYTE byType, char byX, char byY, char byZ)
{
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	return packet;
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

int CCharacter::GetDistance(CCharacter *pCharacter) const
{
	return (int) sqrt(pow(m_nX - pCharacter->GetX(), 2) + pow(m_nY - pCharacter->GetY(), 2));
}
