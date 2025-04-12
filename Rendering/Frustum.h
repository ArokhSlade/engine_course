#include <DirectXMath.h>
using namespace DirectX;

class Frustum
{
public:
	Frustum();
	
	void Initialize(float screenDepth);
	void ConstructFrustum(XMMATRIX projectionMatrix, XMMATRIX viewMatrix);

	bool IsSphereInsideFrustum(float x, float y, float z, float radius);

private:
	float m_screenDepth;
	float m_planes[6][4];
};

