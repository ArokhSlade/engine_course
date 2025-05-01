#pragma once

#include "d3d11.h"

#include "CustomStructs.h"
#include "AxisAlignedBoundingBox.h"
#include "CustomTemplates.h"

class SimpleModel
{
public:
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext* deviceContext) =0;
	
	void RenderAABB(ID3D11DeviceContext* deviceContext);
	virtual int GetIndexCount();
	virtual int GetVertexCount();
	VectorType* GetVertexList();
	AxisAlignedBoundingBox* GetAABB();

	bool IsEmpty();


protected:
	virtual void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) {};

	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	VectorType* m_vertexList;

	AxisAlignedBoundingBox* m_aabb;


public:
	using fun_t = void (*)(ColorVertexType* vertices, unsigned long* indices);

	virtual bool Initialize(ID3D11Device* device);
};