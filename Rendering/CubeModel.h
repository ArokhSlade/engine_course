#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_

#include "d3d11.h"
#include "CustomStruct.h"

class CubeModel
{

public:
	CubeModel();
	~CubeModel();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);
	void Rotate(VectorType, float);

	int GetIndexCount();
	VectorType*GetVertexList();
	int GetVertexCount();
	
private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	VectorType* m_vertexList;
};

#endif //_CUBEMODEL_H_