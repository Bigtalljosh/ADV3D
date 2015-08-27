//NOTES
/* For some reason screen is just black.
I do not know why.

*/

#include "ApplicationSetup.h"

ApplicationSetup::ApplicationSetup()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_TerrainShader = 0;
	m_Light = 0;
	m_Frustum = 0;
	m_QuadTree = 0;

	m_SkyDome = 0;
	m_SkyDomeShader = 0;
}

ApplicationSetup::~ApplicationSetup()
{
}

bool ApplicationSetup::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;

#pragma region Input
	//Creates the input object to handle keyboard input
	try
	{
		m_Input = new Input;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the Input object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Input object.", L"Error", MB_OK);
		return false;
	}

#pragma endregion Manages keyboard input

#pragma region D3D
	//Creates the Direct3D object.
	try
	{
		m_Direct3D = new D3D;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the D3D object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize D3D object", L"Error", MB_OK);
		return false;
	}
#pragma endregion set up D3D device

#pragma region Camera
	//Create the camera
	try
	{
		m_Camera = new CameraHandle;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create CameraHandle object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	//Camera Starting Position
	cameraX = 80.0f;
	cameraY = 15.0f;
	cameraZ = -7.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

#pragma endregion Set up camera
	
#pragma region SkyDome
	// Create the sky dome object.
	try
	{
		m_SkyDome = new SkyDome;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the skydome object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_Direct3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	try
	{
		m_SkyDomeShader = new SkyDomeShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the skydome.", L"Error", MB_OK);
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}
#pragma endregion Need to delete shader

#pragma region Terrain
	// Create the terrain object.
	try
	{
		m_Terrain = new TerrainHandle;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create TerrainHandle object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "heightmap05.bmp", L"RockTexture.dds");  //RockTexture
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	try
	{
		m_TerrainShader = new TerrainShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create terrain shader", L"Error", MB_OK);
		return false;
	}

	try
	{
		m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not init terrain shader", L"Error", MB_OK);
	}

#pragma endregion Handles terrain generation & shader

#pragma region Timer

	// Create the timer object.
	try
	{
		m_Timer = new TimerManagement;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the TimerManagement object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TimerManagement object.", L"Error", MB_OK);
		return false;
	}
#pragma endregion Timer is used by CPU and FPS in order to display the FPS and CPU usage

#pragma region Position
	//Create the position object.
	try
	{
		m_Position = new Position;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the position object.", L"Error", MB_OK);
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);
#pragma endregion Position is used as the player 

#pragma region FPS
	//Create FPS
	try
	{
		m_Fps = new FPS;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not initialize the FPS object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();
#pragma endregion FPS displays the Frames Per Second, Dependent on Timer

#pragma region CPU
	// Create the cpu object.
	try
	{
		m_Cpu = new CPU;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the CPU object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();
#pragma endregion CPU displays the CPU usage, Dependent on Timer

#pragma region TextandFont

	//Create fontShader
	try
	{
		m_FontShader = new FontShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the FontShader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	try
	{
		m_Text = new TextHandle;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the TextHandle object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}
#pragma endregion These two objects create the fontshader to draw the text and the Text object to draw to screen

#pragma region VideoCardInfo
	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}
#pragma endregion Gets the GPU info to display

#pragma region Lights
	//Setup lighting objects
	try
	{
		m_Light = new LightSettings;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not initialize the lightSettings object.", L"Error", MB_OK);
		return false;
	}

	//init light object
	m_Light->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetDiffuseColor(1.0f,1.0f,1.0f,1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, 0.0f);
	m_Light->SetPosition(75.0f,30.0f,10.0f);
	m_Light->SetSpecularColor(1.0f,0.0f,1.0f,1.0f);
	m_Light->SetSpecularPower(0.9);

#pragma endregion Set up lights

#pragma region Frustum
	//Creates the Direct3D object.
	try
	{
		m_Frustum  = new Frustum;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the Frustum object.", L"Error", MB_OK);
		return false;
	}

#pragma endregion set up Frustum

#pragma region QuadTree
	//Create QuadTree Object
	try
	{
		m_QuadTree = new QuadTree;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create the QuadTree Object", L"Error", MB_OK);
		return false;
	}
	try
	{
		result = m_QuadTree->Initialize(m_Terrain, m_Direct3D->GetDevice());
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not init the Quad Tree object", L"ERROR", MB_OK);
		return false;
	}

#pragma endregion //Set Up QuadTree

	return true;
}

void ApplicationSetup::Shutdown()
{

	// Release the quad tree object.
	if(m_QuadTree)
	{
		m_QuadTree->Shutdown();
		delete m_QuadTree;
		m_QuadTree = 0;
	}

	// Release the frustum object.
	if(m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the sky dome shader object
	if(m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	//Sky Dome
	if(m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	//Lights
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	//Text
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	//Font Shader
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	//CPU
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	//FPS
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	//Pos
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	//Timer
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	//Terrain
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	//Camera
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//D3D
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	//Keyboard
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}

bool ApplicationSetup::Frame()
{
	bool result, foundHeight;
	D3DXVECTOR3 position;
	float height;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	//Process Input
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	//Quit Program
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	//Update Timer stats
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	//FPS
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
	//CPU
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Get the current position of the camera.
	position = m_Camera->GetPosition();

	// Get the height of the triangle that is directly underneath the given camera position.
	foundHeight =  m_QuadTree->GetHeightAtPosition(position.x, position.z, height);
	if(foundHeight)
	{
		// If there was a triangle under the camera then position the camera just above it by two units.
		m_Camera->SetPosition(position.x, height + 2.0f, position.z);
	}

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	return result;
}

bool ApplicationSetup::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	//toggle wire
	keyDown = m_Input->IsTabPressed();
	m_Direct3D->ToggleWireFrame();

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	return true;
}

bool ApplicationSetup::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;

	//ClearScene
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

#pragma region

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling.
	m_Direct3D->TurnOffCulling();

	// Turn off the Z buffer.
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Turn back face culling back on.
	m_Direct3D->TurnOnCulling();

	// Turn the Z buffer back on.
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

#pragma endregion skydome


	//Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	//Set the terrain shader parameters that it will use for rendering.
	result = m_TerrainShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), 
						      m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture());
	if(!result)
	{
		return false;
	}

	//Render the terrain using the quad tree and terrain shader.
	m_QuadTree->Render(m_Frustum, m_Direct3D->GetDeviceContext(), m_TerrainShader);

	// Set the number of rendered terrain triangles since some were culled.
	result = m_Text->SetRenderCount(m_QuadTree->GetDrawCount(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
#pragma region Text Render
	m_Direct3D->ToggleWireFrame();

	//stop rotation of text
	D3DXMatrixRotationY(&worldMatrix, 0.0f);

	//Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();
		
	//Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();

	//Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	m_Direct3D->ToggleWireFrame();

#pragma endregion
	

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}