#ifndef _APPLICATIONSETUP_H_
#define _APPLICATIONSETUP_H_

//Globals
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include "Input.h"
#include "D3D.h"
#include "CameraHandle.h"
#include "TerrainHandle.h"
#include "TimerManagement.h"
#include "Position.h"
#include "FPS.h"
#include "CPU.h"
#include "FontShader.h"
#include "TextHandle.h"
#include "LightSettings.h"
#include "ModelHandle.h"
#include "BumpModelHandle.h"
#include "PointLight.h"
#include "SkyDome.h"
#include "SkyDomeShader.h"

#include "Frustum.h"
#include "QuadTree.h"

class ApplicationSetup
{
	public:
		ApplicationSetup();
		~ApplicationSetup();

		bool Initialize(HINSTANCE, HWND, int, int);
		void Shutdown();
		bool Frame();

	private:
		bool HandleInput(float);
		bool RenderGraphics();

		Input* m_Input;
		D3D* m_Direct3D;
		CameraHandle* m_Camera;
		TerrainHandle* m_Terrain;
		TimerManagement* m_Timer;
		Position* m_Position;
		FPS* m_Fps;
		CPU* m_Cpu;
		FontShader* m_FontShader;
		TextHandle* m_Text;
		LightSettings* m_Light;
		SkyDome* m_SkyDome;
		SkyDomeShader* m_SkyDomeShader;
		TerrainShader* m_TerrainShader;

		Frustum* m_Frustum;
		QuadTree* m_QuadTree;

};

#endif