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
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(ColorVertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case LINES.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

int AxisAlignedBoundingBox::GetIndexCount()
{
	return m_indexCount;
}
