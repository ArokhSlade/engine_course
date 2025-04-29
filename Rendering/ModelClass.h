#pragma once
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <fstream>
using namespace std;

#include "TextureClass.h"
#include "CustomStructs.h"

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

public:
	ModelClass();
	~ModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	int GetVertexCount();
	VectorType* GetVertexList();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void ReleaseTexture();

	bool LoadModel(const char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;

	VectorType* m_vertexList;
};

#endif