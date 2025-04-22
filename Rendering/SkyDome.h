#ifndef _SKYDOME_H_
#define _SKYDOME_H_

#include <fstream>
using namespace std;

#include <d3d11.h>
#include "CustomStruct.h"


class SkyDome
{

public:
	SkyDome();
	~SkyDome();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);
		
	int GetIndexCount();
	XMFLOAT4 GetApexColor();

private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	
	XMFLOAT4 m_apexColor;
	XMFLOAT4 m_centerColor;

	ModelType* m_model;
};

#endif // _SKYDOME_H_