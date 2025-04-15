#include "AxisAlignedBoundingBox.h"
#include<limits>

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexList = 0;

}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}

void AxisAlignedBoundingBox::CalculateDimensions()
{
	float currentX, currentY, currentZ;
	auto first = m_vertexList[0];
	m_minX = m_minY = m_minZ = std::numeric_limits<float>::infinity();
	m_maxX = m_maxY = m_maxZ = -std::numeric_limits<float>::infinity();


	for (int i = 0; i < m_vertexCount; ++i)
	{
		currentX = m_vertexList[i].x;
		currentY = m_vertexList[i].y;
		currentZ = m_vertexList[i].z;

		if (currentX > m_maxX) 
		{
			m_maxX = currentX;
		}
		if (currentY > m_maxY)
		{
			m_maxY = currentY;
		}
		if (currentZ > m_maxZ)
		{
			m_maxZ = currentZ;
		}

		if (currentX < m_minX)
		{
			m_minX = currentX;
		}
		if (currentY < m_minY)
		{
			m_minY = currentY;
		}
		if (currentZ < m_minZ)
		{
			m_minZ = currentZ;
		}

		m_posX = m_minX + (m_maxX - m_minX) / 2.f;
		m_posY = m_minY + (m_maxY - m_minY) / 2.f;
		m_posZ = m_minZ + (m_maxZ - m_minZ) / 2.f;
	}
}

bool AxisAlignedBoundingBox::BuildLineBuffers(ID3D11Device* device)
{
	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	int index, vertexCount, indexCount;	
	XMFLOAT4 colorGreen = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	vertexCount = 24;
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

	// Near Bottom
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Near Top
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Near Right
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Far Right
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Far Bottom
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Far Top
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Far Right
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Far Right
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Left Bottom
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Left Top
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Right Bottom
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;
	}

	// Right Top
	{
		vertices[index].position = XMFLOAT3(m_minX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(m_maxX, m_minY, m_minZ);
		vertices[index].color = colorGreen;
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

bool AxisAlignedBoundingBox::Initialize(ID3D11Device* device, VectorType* vertexList, int vertexCount)
{
    m_vertexList = vertexList;
    m_vertexCount = vertexCount;

    CalculateDimensions();

    bool result = BuildLineBuffers(device);
    if (!result)
    {
        return false;
    }

    return true;
}

void AxisAlignedBoundingBox::Shutdown()
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

void AxisAlignedBoundingBox::Render(ID3D11DeviceContext* deviceContext)
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

	// Set the type of primitive that should be rendered from this vertex buffer, in this case LINES.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

int AxisAlignedBoundingBox::GetIndexCount()
{
	return m_indexCount;
}
