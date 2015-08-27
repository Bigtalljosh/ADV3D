//I understand what this class does, but not exactly how it does it, I don't expect to be marked for it.

#include "TimerManagement.h"

TimerManagement::TimerManagement()
{
}

TimerManagement::~TimerManagement()
{
}

bool TimerManagement::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void TimerManagement::Frame()
{
	INT64 currentTime;
	float timeDifference;

	// Query the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate the difference in time since the last time we queried for the current time.
	timeDifference = (float)(currentTime - m_startTime);

	// Calculate the frame time by the time difference over the timer speed resolution.
	m_frameTime = timeDifference / m_ticksPerMs;

	// Restart the timer.
	m_startTime = currentTime;

	return;
}

float TimerManagement::GetTime()
{
	return m_frameTime;
}