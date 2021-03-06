//Some Keys I changed, CBA changing the names, Not such a big deal. See CPP file for changes OR User Guide

#ifndef _INPUT_H_
#define _INPUT_H_

//Pre-Processing
#define DIRECTINPUT_VERSION 0x0800

//Linker
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class Input
{
	public:
		Input();
		~Input();

		bool Initialize(HINSTANCE, HWND, int, int);
		void Shutdown();
		bool Frame();

		void GetMouseLocation(int&, int&);

		bool IsEscapePressed();
		bool IsLeftPressed();
		bool IsRightPressed();
		bool IsUpPressed();
		bool IsDownPressed();
		bool IsAPressed();
		bool IsZPressed();
		bool IsPgUpPressed();
		bool IsPgDownPressed();

		bool IsTabPressed();

	private:
		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();

		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keyboard;
		IDirectInputDevice8* m_mouse;

		unsigned char m_keyboardState[256];
		DIMOUSESTATE m_mouseState;

		int m_screenWidth, m_screenHeight;
		int m_mouseX, m_mouseY;
};

#endif