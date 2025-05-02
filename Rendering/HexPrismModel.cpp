#include "HexPrismModel.h"

int HexPrismModel::GetIndexCount()
{
    int result = GetVertexCount();
    return result;
}

int HexPrismModel::GetVertexCount()
{
    int vertexCount = (6 * 2 * 3); // 6 lateral quads
    vertexCount += (2 * 3) + (3 * 2); // 1 quad + 2 triangles top
    vertexCount += (2 * 3) + (3 * 2); // 1 quad + 2 triangles bottom
    return vertexCount;
}

void HexPrismModel::InitializeVertices(ColorVertexType* vertices, unsigned long* indices)
{
    XMFLOAT4 YELLOW {1.f,1.f,0.f,1.f};
    XMFLOAT4 PURPLE{ 1.f,0.f,1.f,1.f };
    XMFLOAT4 WHITE{ 1.f,1.f,1.f,1.f };

    int index = 0;
    vertices[index].position = { -1.f,1.f,1.f };
    vertices[index+1].position = { 1.f,1.f,1.f };
    vertices[index+2].position = { 1.f,1.f,-1.f };
    vertices[index].color = vertices[index+1].color = vertices[index+2].color = WHITE;

    index += 3;
        
    for (int i = 0; i < m_indexCount; ++i)
    {
        indices[i] = i;
    }
}
