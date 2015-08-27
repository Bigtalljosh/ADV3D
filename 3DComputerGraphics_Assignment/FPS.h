#ifndef _FPS_H_
#define _FPS_H_

//Linker
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class FPS
{
	public:
		FPS();
		~FPS();

		void Initialize();
		void Frame();
		int GetFps();

	private:
		int m_fps, m_count;
		unsigned long m_startTime;
};

#endif