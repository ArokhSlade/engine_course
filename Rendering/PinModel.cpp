#include "PinModel.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

int PinModel::GetIndexCount()
{
    int result = GetVertexCount();
    return result;
}

int PinModel::GetVertexCount()
{
    int result = m_circleSides * 3; // 1 triangle for each "pie" in the base circle
    result += m_circleSides * 3; // 1 triangle per circle edge to connect to apex

    return result;
}

void PinModel::InitializeVertices(ColorVertexType* vertices, unsigned long* indices)
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
    vertices[index].position = {};
    vertices[index+1].position = XMFLOAT3{ cosf(angle), 0.f, sinf(angle) }; 
    vertices[index+2].position = XMFLOAT3{ cosf(nextAngle), 0.f, sinf(nextAngle) };
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = GREEN;    

    for (int i = 0; i < m_indexCount; ++i)
    {
        indices[i] = i;
    }
}
