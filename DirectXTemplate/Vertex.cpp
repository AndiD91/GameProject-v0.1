#include "DirectXTemplatePCH.h"
#include "Vertex.h"


Vertex::Vertex()
	:m_position(DirectX::XMFLOAT3(0,0,0)),
	 m_color(DirectX::XMFLOAT3(0, 0, 0))
{
}

Vertex::Vertex(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& color)
{
	m_position = position;
	m_color = color;
}

Vertex::~Vertex()
{
}

const DirectX::XMFLOAT3& Vertex::getColor()
{
	return m_color;
}
void Vertex::setColor(const DirectX::XMFLOAT3& color)
{
	m_color = color;
}

const DirectX::XMFLOAT3& Vertex::getPosition()
{
	return m_position;
}
void Vertex::setPosition(const DirectX::XMFLOAT3& position)
{
	m_position = position;
}