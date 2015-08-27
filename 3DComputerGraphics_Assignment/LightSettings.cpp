#include "LightSettings.h"

LightSettings::LightSettings()
{
}

LightSettings::~LightSettings()
{
}

void LightSettings::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightSettings::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightSettings::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}

void LightSettings::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightSettings::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

D3DXVECTOR4 LightSettings::GetAmbientColor()
{
	return m_ambientColor;
}

D3DXVECTOR4 LightSettings::GetDiffuseColor()
{
	return m_diffuseColor;
}

D3DXVECTOR3 LightSettings::GetDirection()
{
	return m_direction;
}

D3DXVECTOR4 LightSettings::GetSpecularColor()
{
	return m_specularColor;
}

float LightSettings::GetSpecularPower()
{
	return m_specularPower;
}

void LightSettings::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR4(x, y, z, 1.0f);
	return;
}

D3DXVECTOR4 LightSettings::GetPosition()
{
	return m_position;
}
