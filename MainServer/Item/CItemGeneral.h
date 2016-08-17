#ifndef _CITEMGENERAL_
#define _CITEMGENERAL_

#include "CItem.h"

class CItemGeneral: public CItem
{
	int m_nNum;

public:
	CItemGeneral(D2S_ITEMINFO_DESC& desc);

	int GetNum() { return m_nNum; }
};

#endif