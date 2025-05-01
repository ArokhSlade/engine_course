#include "PyramidModel.h"
#include "CustomTemplates.h"
#include <stdexcept> //for debug throw statement



void PyramidModel::InitializeVertices(ColorVertexType* vertices, unsigned long* indices)
{
	// START

	int index = 0;

	XMFLOAT4 color1 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color2 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color3 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);
	XMFLOAT4 color4 = XMFLOAT4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.f);

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


int PyramidModel::GetVertexCount()
{
	return 18;
}



int PyramidModel::GetIndexCount()
{
	return 18;
}

