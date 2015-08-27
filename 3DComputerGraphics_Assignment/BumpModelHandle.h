#ifndef _BUMPMODELHANDLE_H_
#define _BUMPMODELHANDLE_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureHandle.h"

class BumpModelHandle
{
	public:
		BumpModelHandle();
		~BumpModelHandle();

		bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		int GetIndexCount();
		ID3D11ShaderResourceView* GetColorTexture();
		ID3D11ShaderResourceView* GetNormalMapTexture();

	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
			D3DXVECTOR3 tangent;
			D3DXVECTOR3 binormal;
		};

		struct ModelType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
			float tx, ty, tz;
			float bx, by, bz;
		};

		struct TempVertexType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
		};

		struct VectorType
		{
			float x, y, z;
		};

		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);

		bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
		void ReleaseTextures();

		bool LoadModel(char*);
		void ReleaseModel();

		void CalculateModelVectors();
		void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;
		ModelType* m_model;
		TextureHandle* m_ColorTexture;
		TextureHandle* m_NormalMapTexture;
};

#endif