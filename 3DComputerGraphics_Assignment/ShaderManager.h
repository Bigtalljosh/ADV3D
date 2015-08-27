#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include "D3D.h"

#include "TextureShader.h"
#include "LightShader.h"
#include "BumpMapShader.h"
#include "TerrainShader.h"

class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool RenderTextureShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);

		bool RenderLightShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, 
				D3DXVECTOR3, D3DXVECTOR4, float);

		bool RenderBumpMapShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, 
					 ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4);

		bool RenderTerrainShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3,	ID3D11ShaderResourceView*);

	private:
		TextureShader* m_TextureShader;
		LightShader* m_LightShader;
		BumpMapShader* m_BumpMapShader;
		TerrainShader* m_TerrainShader;
};

#endif