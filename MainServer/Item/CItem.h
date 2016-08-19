#ifndef _CITEM_
#define _CITEM_

#include <map>

#include <minwindef.h>
#include <common.h>

#include "../Macro/CMacroDB.h"

class CItem
{
protected:
	int m_nIID;
	int m_nInfo;

	BYTE m_byKind;

public:
	static int g_nMaxIID;

	int GetIID() { return m_nIID; }
	int GetInfo() { return m_nInfo; }
	BYTE GetKind() { return m_byKind; }
};

typedef std::map<int, CItem*> ItemMap;

#endif