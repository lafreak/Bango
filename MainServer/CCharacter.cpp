#include "CCharacter.h"

int CCharacter::g_nID = 1;

CCharacter::CCharacter(): m_Access()
{
	m_nID = CCharacter::g_nID++;
}