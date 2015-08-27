#ifndef _CPU_H_
#define _CPU_H_

//Linker
#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class CPU
{
	public:
		CPU();
		~CPU();

		void Initialize();
		void Shutdown();
		void Frame();
		int GetCpuPercentage();

	private:
		bool m_canReadCpu;
		HQUERY m_queryHandle;
		HCOUNTER m_counterHandle;
		unsigned long m_lastSampleTime;
		long m_cpuUsage;
};

#endif