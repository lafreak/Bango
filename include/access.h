#ifndef _ACCESS_
#define _ACCESS_

#include <cstdio>
#include <synchronized.h>
#include <minwindef.h>

class Access
{
private:
	synchronized<int> m_nAccess;

public:
	Access(): m_nAccess(0) {}

	bool IsBusy() 
	{
		if (m_nAccess > 0) 
			return true;
		return false;
	}

	void Grant() 
	{ 
		++m_nAccess; 
	}

	void Release() 
	{
		if (!IsBusy()) {
			printf(KRED "Trying to release non busy Access.\n" KNRM);
			return;
		}
		
		--m_nAccess;
	}
};

#endif