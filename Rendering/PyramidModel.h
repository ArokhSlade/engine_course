#pragma once

#include "d3d11.h"
#include "CustomStruct.h"

class PyramidModel
{

public:
	PyramidModel();
	~PyramidModel();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	VectorType* GetVertexList();
	int GetVertexCount();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	VectorType* m_vertexList;
};
