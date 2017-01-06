#ifndef _C_PARTY_
#define _C_PARTY_

#include <map>
#include <unistd.h>
#include <mutex>
#include <list>

#include <vector>

#include <access.h>

#include <Protocol/Packet.h>
#include <Socket/CSocket.h>

#include <cstring>
#include <cstdlib>

#include <string.h>

#include <algorithm>

#include <access.h>

#include "CPlayer.h"

typedef std::vector<CPlayer*> MemberVec;

class CPlayer;

//ADD ITEM DESTRUCTOR ->for when logout, player leaves pt too. etc.
//fix couldnt findparty map error when joining pt after logging in

class CParty
{
	MemberVec m_vec;
	std::mutex m_xvec;

	int m_nID;

public:

	Access m_Access;

	static int g_nMaxIID;
	static std::mutex g_mxMaxIID;
	static int NewIID();

	int GetIID() { return m_nID; }

	MemberVec GetVec() { return m_vec; }

	static std::map<int, CParty*> g_mParty;
	static std::mutex g_mxParty;

	CParty(CPlayer* pPlayer, CPlayer* pPlayer2);

	static void JoinParty(CPlayer* pPlayer);
	static bool FindPartyMember(CPlayer* pPlayer);
	
	static CParty* FindParty(CPlayer* pPlayer);

	// WriteParty(const char* szName, const char* szTemp);

	void AddMember(CPlayer* pPlayer);
	void RemoveMember(CPlayer* pPlayer);

	static void UpdateParty(CPlayer *pPlayer);
	void UpdatePartyInfo(CPlayer *pPlayer);

	void SendPartyInfo();

	void Add(CParty* pParty);
	void Remove(CParty* pParty);

};

typedef std::map<int, CParty*> PartyMap;

#endif