#include "ConeModel.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

int ConeModel::GetIndexCount()
{
    int result = GetVertexCount();
    return result;
}

int ConeModel::GetVertexCount()
{
    int result = m_circleSides * 3; // 1 triangle for each "pie" in the base circle
    result += m_circleSides * 3; // 1 triangle per circle edge to connect to apex

    return result;
}

void ConeModel::InitializeVertices(ColorVertexType* vertices, unsigned long* indices)
{
    int index = 0;
    XMFLOAT4 RED{1.f,0.f,0.f,1.f};
    XMFLOAT4 GREEN{0.f,1.f,0.f,1.f};

    XMFLOAT3 apex{ 0.f,2.f, 0.f };
    
    float angle = 0.f;
    float angleSegment = 2 * PI / m_circleSides;
    float nextAngle = angle + angleSegment;

    using std::cos;
    using std::sinf;

    //BASE
    int vertIdx = 0;
    for (int sideIdx = 0; sideIdx < m_circleSides; sideIdx++)
    {
        vertices[vertIdx].position = {};
        vertices[vertIdx +1].position = XMFLOAT3{ cosf(angle), 0.f, sinf(angle) };
        vertices[vertIdx +2].position = XMFLOAT3{ cosf(nextAngle), 0.f, sinf(nextAngle) };
        vertices[vertIdx].color = vertices[vertIdx + 1].color = vertices[vertIdx + 2].color = GREEN;
        angle = nextAngle;
        nextAngle += angleSegment;
        vertIdx +=3;
    }

    angle = 0.f;
    nextAngle = angle + angleSegment;
    //TOP
    for (int sideIdx = 0; sideIdx < m_circleSides; sideIdx++)
    {
        vertices[vertIdx].position = apex;
        vertices[vertIdx + 1].position = XMFLOAT3{ cosf(nextAngle), 0.f, sinf(nextAngle) }; 
        vertices[vertIdx + 2].position = XMFLOAT3{ cosf(angle), 0.f, sinf(angle) };
        vertices[vertIdx].color = vertices[vertIdx + 1].color = vertices[vertIdx + 2].color = RED;
        angle = nextAngle;
        nextAngle += angleSegment;
        vertIdx += 3;
    }

    for (int i = 0; i < m_indexCount; ++i)
    {
        indices[i] = i;
    }
}
