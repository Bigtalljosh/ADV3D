// #ifndef and #define are used to prevent double declaration of things like enums and static variables, Not strictly needed but good practice.
#ifndef _SETUP_H_
#define _SETUP_H_

//WIN32_LEAN_AND_MEAN is used in the pre-processing stage to exclude the lesser used headers. Speeds up building. Again not needed but good practice.
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "ApplicationSetup.h"

class Setup
{
	public:
		Setup();
		~Setup();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		bool Frame();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;
		ApplicationSetup* m_Application;
};

//Prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//Globals
static Setup* ApplicationHandle = 0;

#endif