#ifndef _CITEM_
#define _CITEM_

#include <map>
#include <unistd.h>
#include <mutex>

#include <minwindef.h>
#include <common.h>

#include <access.h>

#include "../Macro/CMacroDB.h"

class CPlayer;

class CItem
{
protected:
	ITEMINFO_DESC m_desc;
	CItemInfo* m_pMacro;

	std::mutex m_mxThis;

public:
	static int g_nMaxIID;
	static std::mutex g_mxMaxIID;
	static int NewIID();

	Access m_Access;

	CItem(ITEMINFO_DESC& desc, CItemInfo *pMacro);
	~CItem();

	int GetIID() const { return m_desc.nIID; }
	int GetInfo() const { return m_desc.nInfo; }
	int GetNum() const { return m_desc.nNum; }
	void SetNum(int nNum) { m_desc.nNum = nNum; }
	WORD GetIndex() const { return m_desc.wIndex; }
	BYTE GetLevel() const { return m_pMacro->m_byLevel; }
	BYTE GetClass() const { return m_pMacro->m_byClass; }
	BYTE GetSubClass() const { return m_pMacro->m_bySubClass; }

	CItemInfo* GetMacro() const { return m_pMacro; }

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

	static CItem* CreateItem(ITEMINFO_DESC& desc);
};

typedef std::map<int, CItem*> ItemMap;

#endif
