#ifndef _LIGHTSHADER_H_
#define _LIGHTSHADER_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class LightShader
{
	public:
		LightShader();
		~LightShader();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, 
				D3DXVECTOR3, D3DXVECTOR4, float);

	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		struct CameraBufferType
		{
			D3DXVECTOR3 cameraPosition;
			float padding;// 'padding' is used in order to keep the structure a multiple of 16. Otherwise the Create Buffer method will fail duee to using SizeOf(XXX);.
		};

		struct LightBufferType
		{
			D3DXVECTOR4 ambientColor;
			D3DXVECTOR4 diffuseColor;
			D3DXVECTOR3 lightDirection;
			float specularPower;
			D3DXVECTOR4 specularColor;
		};

		bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
		void ShutdownShader();
		void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
		bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
							 D3DXVECTOR3, D3DXVECTOR4, float);
		void RenderShader(ID3D11DeviceContext*, int);

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11SamplerState* m_sampleState;
		ID3D11Buffer* m_matrixBuffer;
		ID3D11Buffer* m_cameraBuffer;
		ID3D11Buffer* m_lightBuffer;
};

#endif