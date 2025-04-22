#include "DiamondModel.h"
#include "CustomConstants.h"



DiamondModel::DiamondModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

DiamondModel::~DiamondModel()
{
}

bool DiamondModel::Initialize(ID3D11Device* device)
{
	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	int index, vertexCount, indexCount;


	vertexCount = 3 * (4 + 4); //2 * 4 triangles
	m_vertexCount = vertexCount;
	indexCount = vertexCount;
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

	index = 0;


	//PARMID
	// Front
	{
		vertices[index].position = XMFLOAT3(0, 2, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}

	// Back
	{
		vertices[index].position = XMFLOAT3(0, 2, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}

	// Left
	{
		vertices[index].position = XMFLOAT3(0, 2, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}

	// Right
	{
		vertices[index].position = XMFLOAT3(0, 2, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}

	//Bottom Pyramid
	// Front
	{
		vertices[index].position = XMFLOAT3(0, -1, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;


		vertices[index].position = XMFLOAT3(-1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

	}

	// Back
	{
		vertices[index].position = XMFLOAT3(0, -1, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;	

		vertices[index].position = XMFLOAT3(-1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}


	// Left
	{
		vertices[index].position = XMFLOAT3(0, -1, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}

	// Right
	{
		vertices[index].position = XMFLOAT3(0, -1, 0);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, -1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, 1, 1);
		vertices[index].color = COLOR_RED;
		indices[index] = index;
		index++;
	}


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
	for (int vertex_index = 0; vertex_index < m_vertexCount; ++vertex_index) {
		m_vertexList[vertex_index].x = vertices[vertex_index].position.x;
		m_vertexList[vertex_index].y = vertices[vertex_index].position.y;
		m_vertexList[vertex_index].z = vertices[vertex_index].position.z;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void DiamondModel::Shutdown()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	if (m_vertexList)
	{
		delete[] m_vertexList;
		m_vertexList = 0;
	}

	return;
}

void DiamondModel::Render(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(ColorVertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

int DiamondModel::GetIndexCount()
{
	return m_indexCount;
}

VectorType* DiamondModel::GetVertexList()
{
	return m_vertexList;
}

int DiamondModel::GetVertexCount()
{
	return m_vertexCount;
}