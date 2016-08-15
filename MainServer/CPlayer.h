
#ifndef _CPLAYER_
#define _CPLAYER_

#include <string>
#include <cstring>

#include <string.h>

#include "CCharacter.h"


class CPlayer: public CCharacter
{
	int m_nCID;

	int m_nAID;
	int m_nPID;
	WORD m_wPUPoint, 
		 m_wSUPoint;
	WORD m_wContribute;
	int m_nAnger;
	__int64 m_n64Exp;

	BYTE m_byGrade;
	std::string m_szGuildName;
	BYTE m_byGRole;

	std::string m_szName;
	BYTE m_byJob;
	BYTE m_byFace,
	 	 m_byHair;
	std::string m_szGuildClass;
	int m_nGID;
	BYTE m_byFlag;
	int m_nFlagItem;
	int m_nHonorGrade;
	int m_nHonorOption;

public:
	CPlayer(int nCID, D2S_LOADPLAYER_DESC desc);
	~CPlayer();

	static WORD g_wDebugItems[4][8];

	int  GetAID() const { return m_nAID; }
	int  GetPID() const { return m_nPID; }
	WORD GetPUPoint() const { return m_wPUPoint; }
	WORD GetSUPoint() const { return m_wSUPoint; }
	WORD GetContribute() const { return m_wContribute; }
	int  GetAnger() const { return m_nAnger; }
	__int64 GetExp() const { return m_n64Exp; }
	BYTE GetGrade() const { return m_byGrade; }
	std::string GetGuildName() const { return m_szGuildName; }
	std::string GetGuildClass() const { return m_szGuildClass; }
	int  GetGID() const { return m_nGID; }
	BYTE GetGRole() const { return m_byGRole; }
	std::string GetName() const { return m_szName; }
	BYTE GetSpecialty() const { return m_byJob; }
	BYTE GetHair() const { return m_byHair; }
	BYTE GetFace() const { return m_byFace; }
	BYTE GetFlag() const { return m_byFlag; }
	int  GetFlagItem() const { return m_nFlagItem; }
	int  GetHonorGrade() const { return m_nHonorGrade; }
	int  GetHonorOption() const { return m_nHonorOption; }

	WORD GetReqPU(BYTE *byStats);

	bool Write(BYTE byType, ...);
	bool WriteInSight(BYTE byType, ...);
	void SendPacket(Packet& packet);
	void SendPacketInSight(Packet& packet);

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	void Process(Packet packet);

	void OnLoadPlayer();
	void GameStart();
	void GameRestart();
	bool CanMove();
	void OnMove(char byX, char byY, char byZ, char byType);
	void Rest(BYTE byType);
	void ProcessMsg(char* szMsg);
	void ChatCommand(char* szCommand);
	void UpdateProperty(BYTE byProperty, __int64 n64Amount);
};

#endif