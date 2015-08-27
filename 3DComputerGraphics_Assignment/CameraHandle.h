#ifndef _CAMERAHANDLE_H_
#define _CAMERAHANDLE_H_

#include <d3dx10math.h>

class CameraHandle
{
	public:
		CameraHandle();
		~CameraHandle();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		D3DXVECTOR3 GetPosition();
		D3DXVECTOR3 GetRotation();

		void Render();
		void GetViewMatrix(D3DXMATRIX&);

	private:
		float m_positionX, m_positionY, m_positionZ;
		float m_rotationX, m_rotationY, m_rotationZ;
		D3DXMATRIX m_viewMatrix;
};

#endif