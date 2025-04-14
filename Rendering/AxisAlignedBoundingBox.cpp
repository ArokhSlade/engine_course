#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}

void AxisAlignedBoundingBox::CalculateDimensions()
{
}

bool AxisAlignedBoundingBox::BuildLineBuffers(ID3D11Device* Device)
{
    
}

bool AxisAlignedBoundingBox::Initialize(ID3D11Device* device, VectorType* vertexList, int vertexCount)
{
    m_vertexList = vertexList;
    m_vertexCount = vertexCount;

    CalculateDimensions();

    bool result = BuildLineBuffers(device);
    if (!result)
    {
        return false;
    }

    return true;
}

void AxisAlignedBoundingBox::Shutdown()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void AxisAlignedBoundingBox::Render(ID3D11DeviceContext* deviceContext)
{
}

int AxisAlignedBoundingBox::GetIndexCount()
{
    return 0;
}
