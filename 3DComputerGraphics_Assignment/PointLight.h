#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include <d3dx10math.h>

class PointLight
{
	public:
		PointLight();
		~PointLight();

		void SetDiffuseColor(float, float, float, float);
		void SetPosition(float, float, float);

		D3DXVECTOR4 GetDiffuseColor();
		D3DXVECTOR4 GetPosition();

	private:
		D3DXVECTOR4 m_diffuseColor;
		D3DXVECTOR4 m_position;
};

#endif