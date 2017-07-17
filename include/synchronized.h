#ifndef _SYNCHRONIZED_
#define _SYNCHRONIZED_

#include <mutex>

template<typename T> struct synchronized
{
private:
	T m_value;
	std::mutex m_mutex;

public:
	synchronized(T val)
	{
		m_value = val;
	}

	synchronized& operator++()
	{
		m_mutex.lock();
		m_value++;
		m_mutex.unlock();
	}

	synchronized& operator--()
	{
		m_mutex.lock();
		m_value--;
		m_mutex.unlock();
	}

	operator T()
	{
		m_mutex.lock();
		T temp = m_value;
		m_mutex.unlock();

		return temp;
	}
	
};

#endif