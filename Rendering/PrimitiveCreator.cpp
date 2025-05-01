#include <d3d11.h> //HWND

#include "PrimitiveCreator.h"
#include "CustomTemplates.h"
#include "CustomEnums.h"
#include "CustomMacros.h"



PrimitiveCreator::PrimitiveCreator()
	:m_ModelList{nullptr}
	,m_CubeModel{nullptr}
	,m_PyramidModel{nullptr}
	,m_SphereModel{nullptr}
{
}


PrimitiveCreator::~PrimitiveCreator()
{

}

bool PrimitiveCreator::Initialize(HWND hwnd, D3DClass* Direct3D, int modelCount)
{
	bool result = true;
	ID3D11Device* device = Direct3D->GetDevice();
	ID3D11DeviceContext* deviceContext = Direct3D->GetDeviceContext();

	if (!ConstructAndInitialize(m_ModelList, modelCount))
	{
		SHOW_INIT_ERROR_IN_HWND("ModelList");
		return false;
	}

	if (!ConstructAndInitialize(m_SphereModel, device, deviceContext,
		"../Rendering/data/seafloor.tga", "../Rendering/data/sphere.txt"))
	{
		SHOW_INIT_ERROR_IN_HWND("SphereModel");
		return false;
	}

	if (!ConstructAndInitialize(m_CubeModel, device))
	{
		SHOW_INIT_ERROR_IN_HWND("CubeModel");
		return false; 
	}

	if (!ConstructAndInitialize(m_PyramidModel, device))
	{
		SHOW_INIT_ERROR_IN_HWND("PyramidModel");
		return false;
	}

	return true;
}

void PrimitiveCreator::Shutdown()
{
	ShutdownAndDelete(m_PyramidModel);
	ShutdownAndDelete(m_CubeModel);
	ShutdownAndDelete(m_SphereModel);
	ShutdownAndDelete(m_ModelList);
}

bool PrimitiveCreator::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, Frustum* frustum, bool displayAABBs)
{
	ID3D11DeviceContext* deviceContext = Direct3D->GetDeviceContext();
	// Get the number of models that will be rendered.
	int modelCount = m_ModelList->GetModelCount();

	int renderCountSpheres = 0;
	int renderCountCubes = 0;
	int renderCountPyramids = 0;

	bool isInsideFrustum;

	float positionX, positionY, positionZ;
	XMFLOAT4 color;
	PrimitiveType primitiveType;
	float radius;

	// Go through all the models and render them only if they can be seen by the camera view.
	for (int index = 0; index < modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, positionX, positionY, positionZ, color, primitiveType);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;

		switch (primitiveType)
		{
		case Sphere:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

				// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
				m_SphereModel->Render(Direct3D->GetDeviceContext());
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

				//if (displayAABBs)
				//{
				//	m_aabbSphere->Render(Direct3D->GetDeviceContext());
				//	ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_aabbSphere->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				//}

				renderCountSpheres++;
			}
			break;
		case Cube:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);
								
				// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
				m_CubeModel->Render(Direct3D->GetDeviceContext());
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

				//if (displayAABBs)
				//{
				//	m_aabbCube->Render(Direct3D->GetDeviceContext());
				//	ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_aabbCube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				//}

				renderCountCubes++;
			}
			break;
		case Pyramid:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

				// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
				m_PyramidModel->Render(Direct3D->GetDeviceContext());
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_PyramidModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

				//if (m_displayAABBs)
				//{
				//	m_aabbPyramid->Render(Direct3D->GetDeviceContext());
				//	ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_aabbPyramid->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				//}

				renderCountPyramids++;
			}
			break;
		}



		// Reset to the original world matrix.
		Direct3D->GetWorldMatrix(worldMatrix);
	}

	

	return true;
}
