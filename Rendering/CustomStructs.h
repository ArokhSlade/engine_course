#pragma once

#include <directxmath.h>
using namespace DirectX;

struct VectorType
{
	float x, y, z;
};

struct VertexPositionType
{
	XMFLOAT3 position;
};

struct ColorVertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct ColorBufferType
{
	XMFLOAT4 apexColor;
	XMFLOAT4 centerColor;
};

struct PrimitiveCounts {
	int sphereCount, cubeCount, pyramidCount, pinCount, hexPrismCount;

	int GetTotalCount() const {
		int total = 0;

		total += sphereCount;
		total += cubeCount;
		total += pyramidCount;
		total += pinCount;
		total += hexPrismCount;

		return total;
	}
};