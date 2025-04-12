#include "Frustum.h"

Frustum::Frustum() {}

void Frustum::Initialize(float screenDepth)
{
	m_screenDepth = screenDepth;
}

void Frustum::ConstructFrustum(XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	XMFLOAT4X4 proMatrix; //projectionMatrix in another format
	XMFLOAT4X4 frustumMatrix;
	float zMin, zMax;

	XMMATRIX finalMatrix;

	XMStoreFloat4x4(&proMatrix, projectionMatrix);

	// reverse projection matrix
	zMin = -proMatrix._43 / proMatrix._33; // get near plane distance
	zMax = m_screenDepth / (m_screenDepth - zMin); // get near plane distance
	proMatrix._33 = zMax;
	proMatrix._43 = -zMax * zMin;



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

bool Frustum::IsSphereInsideFrustum(float x, float y, float z, float radius)
{

}