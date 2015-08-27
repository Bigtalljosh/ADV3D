#include "TextureHandle.h"

TextureHandle::TextureHandle()
{
	m_texture = 0;
}

TextureHandle::~TextureHandle()
{
}

bool TextureHandle::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureHandle::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureHandle::GetTexture()
{
	return m_texture;
}