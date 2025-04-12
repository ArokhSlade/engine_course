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