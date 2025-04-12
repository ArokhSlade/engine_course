#include "CubeModel.h"

CubeModel::CubeModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

}

CubeModel::~CubeModel()
{
}

bool CubeModel::Initialize(ID3D11Device* device)
{
	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	int index, vertexCount, indexCount;
	XMFLOAT4 colorRed = XMFLOAT4(1.f,0.f,0.f,1.f);
	XMFLOAT4 colorBlue = XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	vertexCount = 36;
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

	// Bottom
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;
	}

	// Top
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;
	}

	// Front
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;
	}

	// Back
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;
	}

	// Left
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;
	}

	// Right
	{
		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
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

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void CubeModel::Shutdown()
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

	return;
}

void CubeModel::Render(ID3D11DeviceContext* deviceContext)
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

int CubeModel::GetIndexCount()
{
	return m_indexCount;
}
