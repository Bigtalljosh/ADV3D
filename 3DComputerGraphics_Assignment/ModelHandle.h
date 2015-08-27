#ifndef _MODELHANDLE_H_
#define _MODELHANDLE_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureHandle.h"

class ModelHandle
{
	public:
		ModelHandle();
		~ModelHandle();

		bool Initialize(ID3D11Device*, char*, WCHAR*);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		int GetIndexCount();
		ID3D11ShaderResourceView* GetTexture();

	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
		};

		struct ModelType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
		};

		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);
		bool LoadTexture(ID3D11Device*, WCHAR*);
		void ReleaseTexture();
		bool LoadModel(char*);
		void ReleaseModel();

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;
		TextureHandle* m_Texture;
		ModelType* m_model;
};

#endif