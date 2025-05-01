#include "CubeModel.h"


void CubeModel::InitializeVertices(ColorVertexType* vertices, unsigned long* indices)
{
	XMFLOAT4 colorRed = XMFLOAT4(1, 0, 0, 1);
	XMFLOAT4 colorBlue = XMFLOAT4(0, 0, 1, 1);
	int index = 0;

	// Bottom
	{
		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = XMFLOAT3(1, -1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(1, -1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

	}

	// Top
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(1, 1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;
	}

	// Front
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, 1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;
	}

	// Back
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;
	}

	// Left
	{
		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, -1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(-1, 1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;
	}

	// Right
	{
		vertices[index].position = DirectX::XMFLOAT3(1, 1, -1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = colorRed;
		indices[index] = index;
		index++;

		//

		vertices[index].position = DirectX::XMFLOAT3(1, -1, 1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, -1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;

		vertices[index].position = DirectX::XMFLOAT3(1, 1, -1);
		vertices[index].color = colorBlue;
		indices[index] = index;
		index++;
	}
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


int CubeModel::GetVertexCount()
{
	return 36;
}

int CubeModel::GetIndexCount()
{
	return 36;
}
