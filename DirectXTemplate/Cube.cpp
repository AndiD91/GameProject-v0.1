#include "DirectXTemplatePCH.h"
#include "Cube.h"


Cube::Cube(): 
	m_width(0),
	m_height(0),
	m_depth(0),
	m_position(0),
	m_material()
{
}
Cube::Cube(const FLOAT width, const FLOAT height, const FLOAT depth, const DirectX::XMFLOAT3& position, const Material& material)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_position = position;
	m_material = material;
}

Cube::~Cube()
{
}


FLOAT Cube::getWidth()
{
	return m_width;
}
void Cube::setWidth(const FLOAT value)
{
	m_width = value;
}

FLOAT Cube::getHeight()
{
	return m_height;
}
void Cube::setHeight(const FLOAT value)
{
	m_height = value;
}

FLOAT Cube::getDepth()
{
	return m_depth;
}
void Cube::setDepth(const FLOAT value)
{
	m_depth = value;
}

const DirectX::XMFLOAT3& Cube::getPosition()
{
	return m_position;
}
void Cube::setPosition(const DirectX::XMFLOAT3& value)
{
	m_position = value;
}

const Material& Cube::getMaterial()
{
	return m_material;
}
void Cube::setMaterial(const Material& value)
{
	m_material = value;
}

const std::vector<Vertex>& Cube::getEdges()
{
	return m_edges;
}