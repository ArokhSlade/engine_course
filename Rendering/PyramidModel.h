#ifndef _PYRAMIDMODEL_H_
#define _PYRAMIDMODEL_H_

#include <stdlib.h>
#include <time.h>

#include "CustomStructs.h"
#include "d3d11.h"

class PyramidModel
{
public:
	PyramidModel();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	int GetVertexCount();
	VectorType* GetVertexList();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;

	VectorType* m_vertexList;
};

#endif