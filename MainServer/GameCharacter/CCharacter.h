#ifndef _CCHARACTER_
#define _CCHARACTER_

#include <string>
#include <mutex>
#include <math.h>
#include <list>
#include <map>
#include <unistd.h>

#include <access.h>

#include <cstdarg>
#include <string.h>

#include <Protocol/Packet.h>
#include <Socket/CSocket.h>

#include <Protocol/MainProtocol.h>

#include <minwindef.h>
#include <common.h>

class CCharacter
{
	std::mutex m_mxThis;

protected:
	int m_nID;

	WORD m_wStrAdd,
		m_wHthAdd,
		m_wIntAdd,
		m_wWisAdd,
		m_wDexAdd;

	DWORD	m_nCurHP;
	WORD	m_wCurMP;

	int m_nX, 
		m_nY, 
		m_nZ;

	BYTE m_byClass;

	WORD m_wHitAdd,
		m_wDodgeAdd;

	DWORD m_dwMaxHPAdd;
	WORD m_wMaxMPAdd;

	WORD m_wMinAttackAdd,
		m_wMaxAttackAdd,
		m_wMinMagicAdd,
		m_wMaxMagicAdd;

	WORD m_wResistFireAdd,
		m_wResistIceAdd,
		m_wResistLitningAdd,
		m_wResistCurseAdd,
		m_wResistPalsyAdd;

	WORD m_wDir;

	__int64 m_n64GState,
	 		m_n64MState,
	 		m_n64GStateEx,
	 		m_n64MStateEx;

	 BYTE m_byKind;
public:

	static int g_nID;
	static std::mutex g_mxID;
	static int NewID();

	CCharacter();

	Access m_Access;

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	int  GetID() const { return m_nID; }
	BYTE GetKind() const { return m_byKind; }
	BYTE GetClass() const { return m_byClass; }
	virtual WORD GetStr() const { return 0; }
	virtual WORD GetHth() const { return 0; }
	virtual WORD GetInt() const { return 0; }
	virtual WORD GetWis() const { return 0; }
	virtual WORD GetAgi() const { return 0; }
	DWORD GetCurHP() const { return m_nCurHP; }
	WORD GetCurMP() const { return m_wCurMP; }
	virtual DWORD GetMaxHP() const { return 0; }
	virtual WORD GetMaxMP() const { return 0; }
	int  GetX() const { return m_nX; }
	int  GetY() const { return m_nY; }
	int  GetZ() const { return m_nZ; }
	WORD GetDir() const { return m_wDir; }
	virtual BYTE GetLevel() const { return 0; }
	virtual WORD GetHit() const { return 0; }
	virtual WORD GetDodge() const { return 0; }
	virtual WORD GetDefense() const { return 0; }
	virtual BYTE GetAbsorb() const { return 0; }
	virtual WORD GetMinAttack() const { return 0; }
	virtual WORD GetMaxAttack() const { return 0; }
	virtual WORD GetMinMagic() const { return 0; }
	virtual WORD GetMaxMagic() const { return 0; }
	virtual WORD GetResist(BYTE byResist) const { return 0; }
	WORD GetAttack() const;
	WORD GetMagic() const;
	virtual bool CanAttack(CCharacter *pTarget) const;
	virtual bool CheckHit(CCharacter *pTarget) const;
	DWORD GetFinalDamage(CCharacter *pAttacker, DWORD dwDamage);
	DWORD GetFatalDamage(DWORD dwFinalDamage, BYTE& byType);

	__int64 GetGState() const { return m_n64GState; }
	__int64 GetMState() const { return m_n64MState; }
	__int64 GetGStateEx() const { return m_n64GStateEx; }
	__int64 GetMStateEx() const { return m_n64MStateEx; }

	void AddGState(__int64 n64GState);
	void AddMState(__int64 n64MState);
	void AddGStateEx(__int64 n64GStateEx);
	void AddMStateEx(__int64 n64MStateEx);
	void SubGState(__int64 n64GState);
	void SubMState(__int64 n64MState);
	void SubGStateEx(__int64 n64GStateEx);
	void SubMStateEx(__int64 n64MStateEx);
	bool IsGState(__int64 n64GState);
	bool IsMState(__int64 n64MState);
	bool IsGStateEx(__int64 n64GStateEx);
	bool IsMStateEx(__int64 n64MStateEx);

	virtual Packet GenerateCreatePacket(bool bHero = false);
	virtual Packet GeneratePetPacket();
	virtual Packet GenerateDeletePacket();
	virtual Packet GenerateMovePacket(BYTE byType, char byX, char byY, char byZ = 0);

	virtual void SendPacket(Packet& packet) {}

	virtual void Tick() {}

	bool WriteInSight(BYTE byType, ...);

	void SendPacketInSight(Packet& packet);

	void SetDirection(int nX, int nY);
	void SetDirection(CCharacter* pCharacter) { SetDirection(pCharacter->GetX() - GetX(), pCharacter->GetY() - GetY()); }

	bool IsNormal() const { return GetCurHP() > 0; }

	virtual void Damage(CCharacter *pAttacker, DWORD& dwDamage, BYTE& byType) {}
	virtual void Die() {}

	BYTE GetMoveAction(CCharacter *pCharacter, char byX, char byY);
	int  GetDistance(CCharacter *pCharacter);
};

typedef std::map<int, CCharacter*> CharacterMap;
typedef std::list<CCharacter*> CharacterList;


#endif
