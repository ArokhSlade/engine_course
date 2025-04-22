#pragma once

#include <directxmath.h>
using namespace DirectX;

struct VectorType
{
	float x, y, z;
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