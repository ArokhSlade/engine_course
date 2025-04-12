#include "Frustum.h"

Frustum::Frustum() {}

void Frustum::Initialize(float screenDepth)
{
	m_screenDepth = screenDepth;
}

void ConstructFrustum(XMMATRIX projectionMatrix, XMMATRIX viewMatrix) 
{
	XMFLOAT4X4 proMatrix; //projectionMatrix in another format
	XMFLOAT4X4 frustumMatrix;
	float zMin, zMax;

	XMMATRIX finalMatrix;

	XMStoreFloat4x4(&proMatrix, projectionMatrix);




	projectionMatrix = XMLoadFloat4x4(&proMatrix);
	finalMatrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

	XMStoreFloat4x4(&frustumMatrix, finalMatrix);
	// near plane

	// far plane

	// left plane

	// right plane

	// bottom plane

	// top plane

	// normalize planes

}

bool IsSphereInsideFrustum(float x, float y, float z, float radius) 
{

}