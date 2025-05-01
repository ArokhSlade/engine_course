#pragma once
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <fstream>
using namespace std;

#include "TextureClass.h"
#include "CustomStructs.h"
#include "AxisAlignedBoundingBox.h"
#include "CustomTemplates.h"

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
	void Render(ID3D11DeviceContext*);
	void RenderAABB(ID3D11DeviceContext* deviceContext);
	void Shutdown();

	int GetIndexCount();
	int GetVertexCount();
	VectorType* GetVertexList();
	ID3D11ShaderResourceView* GetTexture();

	AxisAlignedBoundingBox* GetAABB();

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
	ModelType* m_Model;

	VectorType* m_vertexList;

	AxisAlignedBoundingBox* m_aabb;
};

#endif