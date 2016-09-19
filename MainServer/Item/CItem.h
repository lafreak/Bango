#ifndef _CITEM_
#define _CITEM_

#include <map>
#include <unistd.h>
#include <mutex>
#include <list>

#include <access.h>

#include <Protocol/Packet.h>
#include <Socket/CSocket.h>

#include "../Macro/CMacroDB.h"

class CPlayer;

class CItem
{
	DWORD m_timer;
	int m_nGState;

	int m_nX, 
	    m_nY;

protected:
	ITEMINFO_DESC m_desc;
	CItemInfo* m_pMacro;

	std::mutex m_mxThis;

public:

	static int g_nMaxIID;
	static std::mutex g_mxMaxIID;
	static int NewIID();

	Access m_Access;

	static void Add(CItem * pItem);
	static void Remove(CItem * pItem);

	static std::map<int, CItem*> g_mItem;
	static std::mutex g_mxItem;

	void SetGState(int nGState) { m_nGState = nGState; }
	int GetState() const { return m_nGState; }

	CItem(ITEMINFO_DESC& desc, CItemInfo *pMacro);
	~CItem();
    
    DWORD GetTimer() const { return m_timer; }
    void SetTimer() { m_timer = GetTickCount(); }

	int GetIID() const { return m_desc.nIID; }
	int GetInfo() const { return m_desc.nInfo; }
	int GetNum() const { return m_desc.nNum; }
	void SetNum(int nNum) { m_desc.nNum = nNum; }
	WORD GetIndex() const { return m_desc.wIndex; }
	BYTE GetLevel() const { return m_pMacro->m_byLevel; }
	BYTE GetClass() const { return m_pMacro->m_byClass; }
	BYTE GetSubClass() const { return m_pMacro->m_bySubClass; }

	CItemInfo* GetMacro() const { return m_pMacro; }
	ITEMINFO_DESC GetDesc() { return m_desc;}

	bool IsState(int nState) { return m_desc.nInfo & nState; }
	void AddState(int nState) { m_desc.nInfo |= nState; }
	void SubState(int nState) { m_desc.nInfo &= ~nState; }

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	virtual bool Use(CPlayer *pPlayer) { return false; }
	virtual void PutOn(CPlayer *pPlayer) {}
	virtual void PutOff(CPlayer *pPlayer) {}

	bool CanUse(CPlayer *pPlayer);
	bool CanTrash(CPlayer *pPlayer);

	int  GetX() { return m_nX; }
    int  GetY() { return m_nY; }

	void SetX(int nX) { m_nX = nX; }
	void SetY(int nY) { m_nY = nY; }

	static CItem* CreateItem(ITEMINFO_DESC& desc);
	static CItem* CreateItem(CItem * pItem, int count, int x, int y);	
	static CItem* FindItemByIID(int nIID);

	Packet GenerateCreatePacket();
    Packet GenerateDeletePacket();

    BYTE GetMoveAction(CItem* pItem, char byX, char byY);

	void Tick();
};

typedef std::map<int, CItem*> ItemMap;
typedef std::list<CItem*> ItemList;

#endif