#ifndef _TIMERMANAGEMENT_H_
#define _TIMERMANAGEMENT_H_

#include <windows.h>

class TimerManagement
{
	public:
		TimerManagement();
		~TimerManagement();

		bool Initialize();
		void Frame();

		float GetTime();

	private:
		INT64 m_frequency;
		float m_ticksPerMs;
		INT64 m_startTime;
		float m_frameTime;
};

#endif