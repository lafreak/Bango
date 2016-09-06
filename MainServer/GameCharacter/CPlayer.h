
#ifndef _CPLAYER_
#define _CPLAYER_

#include <string>
#include <cstring>
#include <cstdlib>

#include <string.h>

#include "CCharacter.h"
#include "../Item/CItem.h"
#include "CMonster.h"

#define GEAR_NUM 22
#define GEAR_VISIBLE_NUM 8

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

	int m_nOnTeleportX;
	int m_nOnTeleportY;

	__int64 m_n64WearState;

	int m_Gear[GEAR_NUM];
	WORD m_GearIndex[GEAR_VISIBLE_NUM];
	BYTE m_byTrigramLevel;

	BYTE m_byShortcutState;

	ItemMap m_mItem;
	std::mutex m_mxItem;

public:
	CPlayer(int nCID, D2S_LOADPLAYER_DESC& desc);
	~CPlayer();

	static std::map<int, CPlayer*> g_mPlayer;
	static std::mutex g_mxPlayer;

	static void Add(CPlayer *pPlayer);
	static void Remove(CPlayer *pPlayer);

	// Remember to call m_Access.Release() after usage
	static CPlayer* FindPlayer(int nID);
	static CPlayer* FindPlayerByName(char *szName);

	int  GetAID() const { return m_nAID; }
	int  GetPID() const { return m_nPID; }
	int  GetCID() const { return m_nCID; }
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
	BYTE GetTrigramLevel() const { return m_byTrigramLevel; }

	int  GetGear(BYTE byType) const { return m_Gear[byType]; }
	void OnPutOnGear(CItem *pItem);
	void OnPutOffGear(CItem *pItem);


	bool IsWState(__int64 n64WState) const { return m_n64WearState & (1 << n64WState); }
	//bool IsAnyTrigramState() const { return IsWState(WS_TRIGRAM1) || IsWState(WS_TRIGRAM2) || IsWState(WS_TRIGRAM3) || IsWState(WS_TRIGRAM4) || IsWState(WS_TRIGRAM5) || IsWState(WS_TRIGRAM6) || IsWState(WS_TRIGRAM7) || IsWState(WS_TRIGRAM8); }
	bool IsAnyTrigramState() const { return m_n64WearState & (((__int64)0xFF) << WS_TRIGRAM1); }
	bool IsAllTrigramState() const { return (BYTE)(m_n64WearState >> WS_TRIGRAM1) == 0xFF; }
	void AddWState(__int64 n64WState) { m_n64WearState |= (1 << n64WState); }
	void SubWState(__int64 n64WState) { m_n64WearState &= ~(1 << n64WState); }

	WORD GetReqPU(BYTE *byStats);

	static bool WriteAll(BYTE byType, ...);
    
	bool Write(BYTE byType, ...);

	void SendPacket(Packet& packet);

	Packet GenerateCreatePacket(bool bHero=false);
	Packet GeneratePetPacket();
	Packet GenerateDeletePacket();
	Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ);

	void Process(Packet packet);

	void OnLoadPlayer();
	void OnLoadItems(char *p);
	void GameStart();
	void GameRestart();
	bool CanMove();
	void OnMove(char byX, char byY, char byZ, char byType);
	void Rest(BYTE byType);
	void ProcessMsg(char* szMsg);
	void ChatCommand(char* szCommand);
	void UpdateProperty(BYTE byProperty, __int64 n64Amount);
	void Teleport(int nX, int , int nZ=0);
	void OnTeleport(BYTE byAnswer, int nZ);
	void InsertItem(WORD wIndex, int nNum=1, BYTE byLogType=TL_CREATE, bool bOwn=false, bool bForceSingular=false, BYTE byPrefix=0, BYTE byXAttack=0, BYTE byXMagic=0, BYTE byXHit=0, BYTE byEBlow=0, int nInfo=0, BYTE byXDodge=0, BYTE byXDefense=0, FUSION_DESC* pFuse=NULL, BYTE byShot=0, WORD wPerforation=0, int nGongLeft=0, int nGongRight=0);
	bool MergeItem(WORD wIndex, int nNum, BYTE byLogType=TL_CREATE, bool bOwn=false);
	bool UseItem(CItem *pItem);
	void PutOnItem(CItem *pItem);
	void PutOffItem(CItem *pItem);
	void Tick();

	// Remember not to call m_Access.Release if method returns false.
	bool RemoveItem(CItem *pItem, int nNum=0, BYTE byLogType=TL_DELETE);

	void RemoveItem(WORD wIndex, int nNum=0, BYTE byLogType=TL_DELETE);
	void SaveAllProperty();

	// Item Map
	void IntoInven(CItem* pItem);
	void OutofInven(CItem* pItem);
	void EmptyInven();

	// Remember to call m_Access.Release() on found item.
	CItem* FindItem(WORD wIndex, BYTE byOwn=IFO_ANY);
	CItem* FindItemByIID(int nIID);
};

typedef std::map<int, CPlayer*> PlayerMap;
typedef std::list<CPlayer*> PlayerList;

#endif