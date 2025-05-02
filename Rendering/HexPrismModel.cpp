#include "HexPrismModel.h"
#include <array>
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
    XMFLOAT4 BLUE{ 0.f,0.f,1.f,1.f };

    int index = 0;
    //TOP QUAD
    vertices[index].position = { -1.f,1.f,1.f };
    vertices[index+1].position = { 1.f,1.f,1.f };
    vertices[index+2].position = { 1.f,1.f,-1.f };
    vertices[index].color = vertices[index+1].color = vertices[index+2].color = BLUE;
    index += 3;
    vertices[index].position = { 1.f,1.f,-1.f }; 
    vertices[index + 1].position = { -1.f,1.f,-1.f };
    vertices[index + 2].position = { -1.f,1.f,1.f };
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = BLUE;
    index += 3;
    //TOP LEFT TRIANGLE
    vertices[index].position = { -1.f,1.f,1.f };
    vertices[index + 1].position = { -1.f,1.f,-1.f };
    vertices[index + 2].position = { -2.f,1.f,0.f }; 
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = BLUE;
    index += 3;
    //TOP RIGHT TRIANGLE
    vertices[index].position = { 1.f,1.f,-1.f }; 
    vertices[index + 1].position = { 1.f,1.f,1.f };
    vertices[index + 2].position = { 2.f,1.f,0.f };
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = BLUE;
    index += 3;
    //BOTTOM QUAD
    vertices[index].position = { -1.f,-1.f,1.f };
    vertices[index + 1].position = { 1.f,-1.f,-1.f };
    vertices[index + 2].position = { 1.f,-1.f,1.f }; 
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = WHITE;
    index += 3;
    vertices[index].position = { 1.f,-1.f,-1.f };
    vertices[index + 1].position = { -1.f,-1.f,1.f };
    vertices[index + 2].position = { -1.f,-1.f,-1.f }; 
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = WHITE;
    index += 3;
    //BOTTOM LEFT TRIANGLE
    vertices[index].position = { -1.f,-1.f,-1.f }; 
    vertices[index + 1].position = { -1.f,-1.f,1.f };
    vertices[index + 2].position = { -2.f,-1.f,0.f };
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = WHITE;
    index += 3;
    //BOTTOM RIGHT TRIANGLE
    vertices[index].position = { 1.f,-1.f,1.f }; 
    vertices[index + 1].position = { 1.f,-1.f,-1.f };
    vertices[index + 2].position = { 2.f,-1.f,0.f };
    vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = WHITE;
    index += 3;
    //LATERAL PLANES
    
    struct XZ {
        float x, z;
    };
    std::array<XZ,7> xz = {
        XZ{-2.f,0.f},{-1.f,-1.f},{ 1.f,-1.f},
          { 2.f,0.f},{ 1.f, 1.f}, {-1.f,1.f},
          {-2.f,0.f} //duplicate first element to avoid iterating over bounds later
    };

    for (int i = 0; i < 6; ++i) //side index
    {
        //DRAW QUAD
        vertices[index  ].position = { xz[i  ].x,  1.f, xz[i  ].z };
        vertices[index+1].position = { xz[i+1].x,  1.f, xz[i+1].z};
        vertices[index+2].position = { xz[i+1].x, -1.f, xz[i+1].z };

        vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = PURPLE;
        index += 3;

        vertices[index  ].position = { xz[i  ].x,  1.f, xz[i  ].z };
        vertices[index+1].position = { xz[i+1].x, -1.f, xz[i+1].z }; 
        vertices[index+2].position = { xz[i  ].x, -1.f, xz[i  ].z };

        vertices[index].color = vertices[index + 1].color = vertices[index + 2].color = YELLOW;
        index += 3;
    }
        
    for (int i = 0; i < m_indexCount; ++i)
    {
        indices[i] = i;
    }
}
