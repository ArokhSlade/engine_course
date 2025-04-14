#pragma once

#include "d3d11.h"
#include "CustomStruct.h"
class AxisAlignedBoundingBox
{
public:
	AxisAlignedBoundingBox();
	~AxisAlignedBoundingBox();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();

private: 
	void CalculateDimesions();
	bool BuildLineBuffers(ID3D11Device* Device);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;

	float m_maxX, m_maxY, m_minZ;
	float m_minX, m_minY, m_minZ;

	float m_posX, m_posY, m_posZ;
};