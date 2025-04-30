#include "PyramidModel.h"
#include <stdexcept>

AxisAlignedBoundingBox* PyramidModel::GetAABB()
{
	return m_aabb;
}

bool PyramidModel::IsEmpty() 
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

bool PyramidModel::Initialize(ID3D11Device* device)
{
	if (!IsEmpty())
	{
		throw std::runtime_error("pyramid not zero-initialized\n");
	}

	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	int index, vertexCount, indexCount;

	srand((unsigned int)time(NULL));

	XMFLOAT4 color1 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color2 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color3 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color4 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);

	vertexCount = 18;
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

	// START

	index = 0;

	// bottom
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = color1;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = color1;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = color1;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = color2;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = color2;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = color2;
		indices[index] = index;
		index++;
	}

	// Front
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = color1;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(0, 1, 0);
		vertices[index].color = color1;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = color1;
		indices[index] = index;
		index++;
	}

	// Back
	{
		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = color2;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(0, 1, 0);
		vertices[index].color = color2;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = color2;
		indices[index] = index;
		index++;
	}

	// Left
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = color3;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(0, 1, 0);
		vertices[index].color = color3;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = color3;
		indices[index] = index;
		index++;
	}

	// Right
	{
		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = color4;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(0, 1, 0);
		vertices[index].color = color4;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = color4;
		indices[index] = index;
		index++;
	}
	// END

	// Create the vertex buffer.
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

	return true;
}

void PyramidModel::Shutdown()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

void PyramidModel::Render(ID3D11DeviceContext* deviceContext)
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

int PyramidModel::GetIndexCount()
{
	return m_indexCount;
}

int PyramidModel::GetVertexCount()
{
	return m_vertexCount;
}

VectorType* PyramidModel::GetVertexList()
{
	return m_vertexList;
}
