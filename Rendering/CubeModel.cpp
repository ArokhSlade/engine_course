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

int CubeModel::GetVertexCount()
{
	return 36;
}

int CubeModel::GetIndexCount()
{
	return 36;
}
