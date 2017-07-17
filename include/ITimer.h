#ifndef _ITIMER_
#define _ITIMER_

#include <functional>
#include <iostream>
#include <minwindef.h>

class ITimer
{
	DWORD m_dwTime;
	std::function<void()> m_fnAction;

public:
	void SetTimer(std::function<void()> fnAction, DWORD dwTime)
	{
		m_dwTime = GetTickCount() + dwTime;
		m_fnAction = fnAction;
	}

	void ExecuteTimer()
	{
		DWORD dwNow = GetTickCount();
		if (m_dwTime && m_dwTime < dwNow)
		{
			m_dwTime = 0;
			m_fnAction();
		}
	}
};

#endif
