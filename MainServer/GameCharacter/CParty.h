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
	int m_nID;

	MemberVec m_vMembers;
	std::mutex m_mxThis;

	static std::map<int, CParty*> g_mParty;
	static std::mutex g_mxParty;

	static int g_nMaxID;
	static std::mutex g_mxMaxID;


	static int NewID();
	static void Add(CParty* pParty);
	static void Remove(CParty* pParty);

	void GetPlayerList(MemberVec& list);

public:
	Access m_Access;

	CParty(CPlayer* pPlayer, CPlayer* pPlayer2);
	~CParty();

	static CParty* FindParty(int nID);

	int GetID() const { return m_nID; }
	int GetMemberAmount() const { return m_vMembers.size(); }
	void Discard();
	void AddMember(CPlayer* pPlayer);
	void RemoveMember(CPlayer* pPlayer);
	void UpdateMemberHP(CPlayer *pPlayer);
	void UpdateMemberLevel(CPlayer *pPlayer);
	//void UpdateParty(CPlayer *pPlayer);
	void SendPartyInfo();
};

typedef std::map<int, CParty*> PartyMap;

#endif