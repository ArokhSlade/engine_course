#include "Frustum.h"

Frustum::Frustum() {}

void Frustum::Initialize(float screenDepth)
{
	m_screenDepth = screenDepth;
}

void Frustum::ConstructFrustum(XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	XMFLOAT4X4 proMatrix, frustumMatrix;
	float zMin, zMax;
	XMMATRIX finalMatrix;

	XMStoreFloat4x4(&proMatrix, projectionMatrix);

	// reverse projection matrix
	zMin = -proMatrix._43 / proMatrix._33;
	zMax = m_screenDepth / (m_screenDepth - zMin);
	proMatrix._33 = zMax;
	proMatrix._43 = -zMax * zMin;

	projectionMatrix = XMLoadFloat4x4(&proMatrix);
	finalMatrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

	XMStoreFloat4x4(&frustumMatrix, finalMatrix);

	// near plane
	m_planes[0][0] = frustumMatrix._14 + frustumMatrix._13;
	m_planes[0][1] = frustumMatrix._24 + frustumMatrix._23;
	m_planes[0][2] = frustumMatrix._34 + frustumMatrix._33;
	m_planes[0][3] = frustumMatrix._44 + frustumMatrix._43;

	// far plane
	m_planes[1][0] = frustumMatrix._14 - frustumMatrix._13;
	m_planes[1][1] = frustumMatrix._24 - frustumMatrix._23;
	m_planes[1][2] = frustumMatrix._34 - frustumMatrix._33;
	m_planes[1][3] = frustumMatrix._44 - frustumMatrix._43;

	// left plane
	m_planes[2][0] = frustumMatrix._14 + frustumMatrix._11;
	m_planes[2][1] = frustumMatrix._24 + frustumMatrix._21;
	m_planes[2][2] = frustumMatrix._34 + frustumMatrix._31;
	m_planes[2][3] = frustumMatrix._44 + frustumMatrix._41;

	// right plane
	m_planes[3][0] = frustumMatrix._14 - frustumMatrix._11;
	m_planes[3][1] = frustumMatrix._24 - frustumMatrix._21;
	m_planes[3][2] = frustumMatrix._34 - frustumMatrix._31;
	m_planes[3][3] = frustumMatrix._44 - frustumMatrix._41;

	// bottom plane
	m_planes[4][0] = frustumMatrix._14 + frustumMatrix._12;
	m_planes[4][1] = frustumMatrix._24 + frustumMatrix._22;
	m_planes[4][2] = frustumMatrix._34 + frustumMatrix._32;
	m_planes[4][3] = frustumMatrix._44 + frustumMatrix._42;

	// top plane
	m_planes[5][0] = frustumMatrix._14 - frustumMatrix._12;
	m_planes[5][1] = frustumMatrix._24 - frustumMatrix._22;
	m_planes[5][2] = frustumMatrix._34 - frustumMatrix._32;
	m_planes[5][3] = frustumMatrix._44 - frustumMatrix._42;



	// normalize planes
	// Wie Normalisiert man einen Vector?
	// ->teilen durch seine länge
	// Was ist die Länge eines Vectors?
	// length = sqrtf(x * x + y * y + z * z)

	float length;
	for (int i = 0; i < 6; i++)
	{
		length = sqrtf(	(m_planes[i][0] * m_planes[i][0]) +
						(m_planes[i][1] * m_planes[i][1]) +
						(m_planes[i][2] * m_planes[i][2]));
	
		m_planes[i][0] /= length;
		m_planes[i][1] /= length;
		m_planes[i][2] /= length;
		m_planes[i][3] /= length;
	}
}

bool Frustum::IsSphereInsideFrustum(float x, float y, float z, float radius)
{
	float dotProduct;
	for (int i = 0; i < 6; i++)
	{
		dotProduct = (	(m_planes[i][0] * x) +
						(m_planes[i][1] * y) +
						(m_planes[i][2] * z) +
						m_planes[i][3]);
		// 0 is on plane
		// > 0 is inside
		// < 0 is outside
		if (dotProduct < -radius) 
		{
			return false;
		}
	}

	return true;
}

bool Frustum::IsCubeInsideFrustum(float x, float y, float z, float edgeLength)
{
	int i;
	float dotProduct;
	float halfEdgeLength = edgeLength / 2;

	for (i = 0; i < 6; i++)
	{
		dotProduct = ((m_planes[i][0] * (x - halfEdgeLength)) +
			(m_planes[i][1] * (y - halfEdgeLength)) +
			(m_planes[i][2] * (z - halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x - halfEdgeLength)) +
			(m_planes[i][1] * (y - halfEdgeLength)) +
			(m_planes[i][2] * (z + halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x + halfEdgeLength)) +
			(m_planes[i][1] * (y - halfEdgeLength)) +
			(m_planes[i][2] * (z - halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x + halfEdgeLength)) +
			(m_planes[i][1] * (y - halfEdgeLength)) +
			(m_planes[i][2] * (z + halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x - halfEdgeLength)) +
			(m_planes[i][1] * (y + halfEdgeLength)) +
			(m_planes[i][2] * (z - halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x - halfEdgeLength)) +
			(m_planes[i][1] * (y + halfEdgeLength)) +
			(m_planes[i][2] * (z + halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x + halfEdgeLength)) +
			(m_planes[i][1] * (y + halfEdgeLength)) +
			(m_planes[i][2] * (z - halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		dotProduct = ((m_planes[i][0] * (x + halfEdgeLength)) +
			(m_planes[i][1] * (y + halfEdgeLength)) +
			(m_planes[i][2] * (z + halfEdgeLength)) +
			m_planes[i][3]);

		if (dotProduct > 0)
		{
			continue;
		}

		return false;
	}

	return true;
}
