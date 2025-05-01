#include "SimpleModel.h"

AxisAlignedBoundingBox* SimpleModel::GetAABB()
{
	return m_aabb;
}

bool SimpleModel::IsEmpty()
{
	bool empty = true;
	empty &= m_vertexBuffer == nullptr;
	empty &= m_indexBuffer == nullptr;
	empty &= m_vertexCount == 0;
	empty &= m_indexCount == 0;
	empty &= m_vertexList == nullptr;
	empty &= m_aabb == nullptr;

	return empty;
}

void SimpleModel::RenderAABB(ID3D11DeviceContext* deviceContext)
{
	m_aabb->Render(deviceContext);
}

int SimpleModel::GetIndexCount()
{
	return m_indexCount;
}

int SimpleModel::GetVertexCount()
{
	return m_vertexCount;
}

VectorType* SimpleModel::GetVertexList()
{
	return m_vertexList;
}
