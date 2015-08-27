#include "ShaderManager.h"

ShaderManager::ShaderManager()
{	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
	m_TerrainShader = 0;
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;
	//Create the texture shader
	try
	{
		m_TextureShader = new TextureShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create Texture Shader", L"Error", MB_OK);
		return false;
	}

	//Init the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the light shader
	try
	{
		m_LightShader = new LightShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create Light Shader", L"Error", MB_OK);
		return false;
	}

	//Init the light shader
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the bump map shader
	try
	{
		m_BumpMapShader = new BumpMapShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create BumpMap Shader", L"Error", MB_OK);
		return false;
	}
	//Init the bump map shader
	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	//Create Terrain Shader
	try
	{
		m_TerrainShader = new TerrainShader;
	}
	catch(std::bad_alloc)
	{
		MessageBox(hwnd, L"Could not create Terrain Shader", L"Error", MB_OK);
		return false;
	}
	//Init the terrain shader
	result = m_TerrainShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Terrain shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	//Release the terrain Shader
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	return;
}

bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
					     ID3D11ShaderResourceView* texture)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor,
							  D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor, cameraPosition, 
				       specularColor, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
					     ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 lightDirection, 
					     D3DXVECTOR4 diffuse)
{
	bool result;


	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 lightDirection, 
								ID3D11ShaderResourceView* texture)
{
	bool result;
	// Set the shader parameters that it will use for rendering.
	//result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, ambientColor, diffuseColor, lightDirection,texture);
	if(!result)
	{
		return false;
	}

	return true;
}