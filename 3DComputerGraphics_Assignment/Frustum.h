#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

#include <d3dx10math.h>

class Frustum
{
	public:
		Frustum();
		~Frustum();

		void ConstructFrustum(float, D3DXMATRIX, D3DXMATRIX);

		bool CheckPoint(float, float, float);
		bool CheckCube(float, float, float, float);
		bool CheckSphere(float, float, float, float);
		bool CheckRectangle(float, float, float, float, float, float);

	private:
		D3DXPLANE m_planes[6];
};

#endif