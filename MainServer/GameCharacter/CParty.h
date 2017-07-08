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

//ADD ITEM DESTRUCTOR ->for when logout, player leaves pt too. etc.
//fix couldnt findparty map error when joining pt after logging in

class CParty
{
private:
	MemberVec m_Members;
	std::mutex m_xMembers;
	int m_nID;

	static int g_nMaxIID;
	static std::map<int, CParty*> g_mParty;
	static std::mutex g_mxParty;
	static std::mutex g_mxMaxIID;


	int NewIID();
	void Add(CParty* pParty);

public:
	Access m_Access;

	CParty(CPlayer* pPlayer, CPlayer* pPlayer2);
	~CParty() {};

	static CParty* FindParty(CPlayer* pPlayer);

	int GetIID() { return m_nID; }
	void Remove(CParty* pParty);
	int GetMemberAmount() { return m_Members.size(); }
	void Discard();
	void AddMember(CPlayer* pPlayer);
	void RemoveMember(CPlayer* pPlayer);
	void UpdatePartyInfo(CPlayer *pPlayer);
	void UpdateParty(CPlayer *pPlayer);
	void SendPartyInfo();
};

typedef std::map<int, CParty*> PartyMap;

#endif