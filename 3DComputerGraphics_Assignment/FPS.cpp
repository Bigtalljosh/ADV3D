//I understand what this class does, but not exactly how it does it, I don't expect to be marked for it.
#include "FPS.h"

FPS::FPS()
{
}

FPS::~FPS()
{
}

void FPS::Initialize()
{
	// Initialize the counters and the start time.
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	
	return;
}

void FPS::Frame()
{
	m_count++;

	// If one second has passed then update the frame per second speed.
	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTime = timeGetTime();
	}
}

int FPS::GetFps()
{
	return m_fps;
}