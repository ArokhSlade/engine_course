#pragma once

#include "CustomStructs.h"
#include "AxisAlignedBoundingBox.h"
#include "d3d11.h"

class SimpleModel
{
public:
	virtual bool Initialize(ID3D11Device* device)  =0;
	virtual void Shutdown() =0;
	virtual void Render(ID3D11DeviceContext* deviceContext) =0;
	
	void RenderAABB(ID3D11DeviceContext* deviceContext);
	int GetIndexCount();
	int GetVertexCount();
	VectorType* GetVertexList();
	AxisAlignedBoundingBox* GetAABB();

	bool IsEmpty();


protected:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	VectorType* m_vertexList;

	AxisAlignedBoundingBox* m_aabb;
};