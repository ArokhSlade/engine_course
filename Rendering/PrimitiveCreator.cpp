#include <d3d11.h> //HWND

#include "PrimitiveCreator.h"
#include "CustomTemplates.h"



PrimitiveCreator::PrimitiveCreator()
{
	m_Frustum = nullptr;
	m_ModelList = nullptr;
	m_CubeModel = nullptr;
	m_PyramidModel = nullptr;
	m_SphereModel = nullptr;
}

PrimitiveCreator::~PrimitiveCreator()
{

}

bool PrimitiveCreator::Initialize(HWND hwnd, ID3D11Device* device)
{
	bool result = true;

	if (!ConstructAndInitialize(hwnd, m_CubeModel, device))
	{ return false; }

	return true;
}

void PrimitiveCreator::Shutdown()
{
	ShutdownAndDelete(m_CubeModel);
}

bool PrimitiveCreator::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	m_CubeModel->Render(deviceContext);
	ShaderManager->RenderColorShader(deviceContext, m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

	return true;
}
