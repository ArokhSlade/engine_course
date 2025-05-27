#pragma once

#include "d3d11.h"

#include "CustomStructs.h"
#include "AxisAlignedBoundingBox.h"
#include "CustomTemplates.h"

class SimpleModel
{
public:
	SimpleModel(ID3D11Device* device, bool* succeeded);
	SimpleModel();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* deviceContext);
	void RenderAABB(ID3D11DeviceContext* deviceContext);
	void Shutdown();
	
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
	
};