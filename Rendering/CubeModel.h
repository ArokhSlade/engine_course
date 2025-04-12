#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_




#include "d3d11.h"

class CubeModel
{

public:
	CubeModel();
	~CubeModel();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	
private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
};

#endif //_CUBEMODEL_H_