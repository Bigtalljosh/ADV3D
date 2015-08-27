#ifndef _FONTHANDLE_H_
#define _FONTHANDLE_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureHandle.h"

class FontHandle
{
	public:
		FontHandle();
		~FontHandle();

		bool Initialize(ID3D11Device*, char*, WCHAR*);
		void Shutdown();

		ID3D11ShaderResourceView* GetTexture();

		void BuildVertexArray(void*, char*, float, float);

	private:
		struct FontType
		{
			float left, right;
			int size;
		};

		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		bool LoadFontData(char*);
		void ReleaseFontData();
		bool LoadTexture(ID3D11Device*, WCHAR*);
		void ReleaseTexture();

		FontType* m_Font;
		TextureHandle* m_Texture;
};

#endif