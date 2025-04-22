#pragma once

#include <directxmath.h>
using namespace DirectX;

struct VectorType
{
	float x, y, z;
};

struct VertexPositionType //DirectX expects values to be wrapped in a struct
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