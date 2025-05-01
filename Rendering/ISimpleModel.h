#pragma once

#include "CustomStructs.h"
#include "AxisAlignedBoundingBox.h"
#include "d3d11.h"

class ISimpleModel
{
public:
	virtual bool Initialize(ID3D11Device* device)  =0;
	virtual void Shutdown() =0;
	virtual void Render(ID3D11DeviceContext* deviceContext) =0;
	virtual void RenderAABB(ID3D11DeviceContext* deviceContext) =0;

	virtual int GetIndexCount() =0;
	virtual int GetVertexCount() =0;
	virtual VectorType* GetVertexList() =0;
	virtual AxisAlignedBoundingBox* GetAABB() =0;

	virtual bool IsEmpty() =0;


protected:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	VectorType* m_vertexList;

	AxisAlignedBoundingBox* m_aabb;
};