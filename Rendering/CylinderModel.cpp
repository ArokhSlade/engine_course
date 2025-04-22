#include "CylinderModel.h"
#include "CustomConstants.h"

CylinderModel::CylinderModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

CylinderModel::~CylinderModel()
{
}

bool CylinderModel::Initialize(ID3D11Device* device)
{
	ColorVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	int index, vertexCount, indexCount;
	
	const int circleVertexCount = 32;

	
	vertexCount = 32*2 + 32*2; //32 triangles top & bottom + 32 quads
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

	float phi = 0.f;
	float nextPhi = 0.f;

	float x;
	float y;
	float nextX;
	float nextZ;

	const float angle_segment = XM_2PI / circleVertexCount;
	// Bottom
	{
		phi = XM_2PI;
		nextPhi = phi - angle_segment;

		//TODO(Gerald):last vertex separately
		for ( int i =  0; i < circleVertexCount; ++i) 
		{
			float x = cos(phi);
			float z = sin(phi);
			float nextX = cos(phi);
			float nextZ = sin(phi);

			vertices[index].position = XMFLOAT3(0, -1, 0);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(x, -1, z);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(nextX, -1, nextZ);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			phi = nextPhi;
			nextPhi -= angle_segment; //alternatively, swap order of vertices and do minus
		}
	}



	// Top
	{
		phi = 0.f;
		nextPhi = phi + angle_segment;

		//TODO(Gerald):last vertex separately
		for (int i = 0; i < circleVertexCount; ++i)
		{
			float x = cos(phi);
			float z = sin(phi);
			float nextX = cos(phi);
			float nextZ = sin(phi);

			vertices[index].position = XMFLOAT3(0, 1.f, 0);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(x, 1.f, z);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(nextX, 1.f, nextZ);
			vertices[index].color = COLOR_YELLOW;
			indices[index] = index;
			index++;

			phi = nextPhi;
			nextPhi += angle_segment; 
		}
	}

	{
		phi = 0.f;
		nextPhi = phi + angle_segment;

		//TODO(Gerald):last vertex separately
		for (int i = 0; i < circleVertexCount; ++i)
		{
			float x = cos(phi);
			float z = sin(phi);
			float nextX = cos(phi);
			float nextZ = sin(phi);

			//top triangle
			vertices[index].position = XMFLOAT3(x, 1.f, z);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(nextX, -1.f, nextZ);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(nextX, 1.f, nextZ);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;

			//bottom triangle
			vertices[index].position = XMFLOAT3(x, 1.f, z);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(x, -1.f, z);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;

			vertices[index].position = XMFLOAT3(nextX, -1.f, nextZ);
			vertices[index].color = COLOR_RED;
			indices[index] = index;
			index++;


			phi = nextPhi;
			nextPhi += angle_segment;
		}
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

void CylinderModel::Shutdown()
{
}

void CylinderModel::Render(ID3D11DeviceContext* deviceContext)
{
}

int CylinderModel::GetIndexCount()
{
	return 0;
}

VectorType* CylinderModel::GetVertexList()
{
	return nullptr;
}

int CylinderModel::GetVertexCount()
{
	return 0;
}
