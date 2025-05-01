#include "SimpleModel.h"

AxisAlignedBoundingBox* SimpleModel::GetAABB()
{
	return m_aabb;
}

bool SimpleModel::IsEmpty()
{
	bool empty = true;
	empty &= m_vertexBuffer == nullptr;
	empty &= m_indexBuffer == nullptr;
	empty &= m_vertexCount == 0;
	empty &= m_indexCount == 0;
	empty &= m_vertexList == nullptr;
	empty &= m_aabb == nullptr;

	return empty;
}

bool SimpleModel::Initialize(ID3D11Device* device, fun_t initVerts)
{
	if (!initVerts) {
		return false;
	}

	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	int index, indexCount;

	XMFLOAT4 colorRed = XMFLOAT4(1, 0, 0, 1);
	XMFLOAT4 colorBlue = XMFLOAT4(0, 0, 1, 1);

	//TODO: fix this
	m_vertexCount = GetVertexCount();
	indexCount = GetIndexCount();
	m_indexCount = indexCount;

	// Create the vertex array.
	vertices = new ColorVertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ColorVertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;

	// Set up the description of the index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;

	// FUN STARTS HERE :)
	// 
	// STRATEGY PATTERN
	initVerts(vertices, indices);

	// FUN ENDS HERE :(

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	m_vertexList = new VectorType[m_vertexCount];
	if (!m_vertexList)
	{
		return false;
	}

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertexList[i].x = vertices[i].position.x;
		m_vertexList[i].y = vertices[i].position.y;
		m_vertexList[i].z = vertices[i].position.z;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	if (!ConstructAndInitialize(m_aabb, device, m_vertexList, m_vertexCount))
	{
		return false;
	}

	return true;
}

void SimpleModel::Shutdown()
{
	ShutdownAndDelete(m_aabb);
	ReleaseAndZero(m_indexBuffer);
	ReleaseAndZero(m_vertexBuffer);
}

void SimpleModel::RenderAABB(ID3D11DeviceContext* deviceContext)
{
	m_aabb->Render(deviceContext);
}

int SimpleModel::GetIndexCount()
{
	return m_indexCount;
}

int SimpleModel::GetVertexCount()
{
	return m_vertexCount;
}

VectorType* SimpleModel::GetVertexList()
{
	return m_vertexList;
}
