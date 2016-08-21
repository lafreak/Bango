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

	CItem(ITEMINFO_DESC& desc);
	~CItem();

	int GetIID() { return m_desc.nIID; }
	int GetInfo() { return m_desc.nInfo; }
	int GetNum() { return m_desc.nNum; }
	void SetNum(int nNum) { m_desc.nNum = nNum; }
	WORD GetIndex() { return m_desc.wIndex; }

	void Lock() { m_mxThis.lock(); }
	void Unlock() { m_mxThis.unlock(); }

	virtual bool Use(CPlayer *pPlayer) = 0;

	bool CanUse(CPlayer *pPlayer);

	static CItem* CreateItem(ITEMINFO_DESC& desc);
};

typedef std::map<int, CItem*> ItemMap;

#endif