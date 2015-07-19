#pragma once
#include "Vertex.h"
#include "inc/DirectXTemplatePCH.h"
#include "Material.h"
#include <vector>
class Cube
{
public:
	Cube();
	Cube(const FLOAT width, const FLOAT height, const FLOAT depth, const DirectX::XMFLOAT3& position, const Material& material);
	~Cube();

FLOAT getWidth();
	void setWidth(const FLOAT value);

	FLOAT getHeight();
	void setHeight(const FLOAT value);

	 FLOAT getDepth();
	void setDepth(const FLOAT value);

	const DirectX::XMFLOAT3& getPosition();
	void setPosition(const DirectX::XMFLOAT3& value);

	const Material& getMaterial();
	void setMaterial(const Material& value);

	const std::vector<Vertex>& getEdges();

private:
	std::vector<Vertex> m_edges;
	FLOAT m_width;
	FLOAT m_height;
	FLOAT m_depth;
	DirectX::XMFLOAT3 m_position;
	Material m_material;

	std::vector<WORD> g_indicies;
	DirectX::XMMATRIX m_WorldMatrix;

};

