#ifndef _AXISALIGNEDBOUNDINGBOX_H_
#define _AXISALIGNEDBOUNDINGBOX_H_

#include "CustomStructs.h"
#include "d3d11.h"

class AxisAlignedBoundingBox
{
public:
	AxisAlignedBoundingBox();
	~AxisAlignedBoundingBox();

	bool Initialize(ID3D11Device* device, VectorType* vertexList, int vertexCount);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();

private:
	void CalculateDimensions();
	bool BuildLineBuffers(ID3D11Device* device);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;

	float m_maxX, m_maxY, m_maxZ;
	float m_minX, m_minY, m_minZ;

	float m_posX, m_posY, m_posZ;

	VectorType* m_vertexList;
};

#endif