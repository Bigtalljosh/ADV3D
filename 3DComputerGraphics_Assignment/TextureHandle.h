#ifndef _TEXTUREHANDLE_H_
#define _TEXTUREHANDLE_H_

#include <d3d11.h>
#include <d3dx11tex.h>

class TextureHandle
{
	public:
		TextureHandle();
		~TextureHandle();

		bool Initialize(ID3D11Device*, WCHAR*);
		void Shutdown();

		ID3D11ShaderResourceView* GetTexture();

	private:
		ID3D11ShaderResourceView* m_texture;
};

#endif