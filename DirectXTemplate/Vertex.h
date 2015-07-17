#pragma once
#include "inc/DirectXTemplatePCH.h"
class Vertex
{
public:
	Vertex();
	Vertex(const DirectX::XMFLOAT3& position,const DirectX::XMFLOAT3& color);
	~Vertex();

	const DirectX::XMFLOAT3& getColor();
	void setColor(const DirectX::XMFLOAT3& color);

	const DirectX::XMFLOAT3& getPosition();
	void setPosition(const DirectX::XMFLOAT3& position);
private:
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_color;
};

