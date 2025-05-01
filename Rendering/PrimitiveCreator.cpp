#include <d3d11.h> //HWND

#include "PrimitiveCreator.h"
#include "CustomTemplates.h"
#include "CustomEnums.h"
#include "CustomMacros.h"



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

bool PrimitiveCreator::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, PrimitiveCounts* renderCounts, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, Frustum* frustum, bool displayAABBs)
{
	ID3D11DeviceContext* deviceContext = Direct3D->GetDeviceContext();
	// Get the number of models that will be rendered.
	int modelCount = m_ModelList->GetModelCount();

	*renderCounts = {};

	bool isInsideFrustum;

	float positionX, positionY, positionZ;
	XMFLOAT4 color;
	PrimitiveType primitiveType;
	float radius;

	// Helper function to render any model
	// Put the model vertex and index buffers on the graphics pipeline 
	// to prepare them for drawing.
	auto RenderColorShaderFtor = [=, deviceContext = Direct3D->GetDeviceContext()](auto* model, auto worldMatrix) {
		model->Render(deviceContext);
		ShaderManager->RenderColorShader(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
		};

	// Go through all the models and render them only if they can be seen by the camera view.
	for (int index = 0; index < modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, positionX, positionY, positionZ, color, primitiveType);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;

		switch (primitiveType)
		{
		case PrimitiveType::Sphere:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

				RenderColorShaderFtor(m_SphereModel, worldMatrix);

				if (displayAABBs)
				{
					RenderColorShaderFtor(m_SphereModel->GetAABB(), worldMatrix);
				}

				renderCounts->sphereCount++;
			}
			break;
		case PrimitiveType::Cube:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

				RenderColorShaderFtor(m_CubeModel, worldMatrix);

				if (displayAABBs)
				{
					RenderColorShaderFtor(m_CubeModel->GetAABB(), worldMatrix);
				}

				renderCounts->cubeCount++;
			}
			break;
		case PrimitiveType::Pyramid:
			isInsideFrustum = frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, radius);
			if (isInsideFrustum)
			{
				// Move the model to the location it should be rendered at.
				worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);							

				RenderColorShaderFtor(m_PyramidModel, worldMatrix);

				if (displayAABBs)
				{
					RenderColorShaderFtor(m_PyramidModel->GetAABB(), worldMatrix);
				}

				renderCounts->pyramidCount++;
			}
			break;
		}

		// Reset to the original world matrix.
		Direct3D->GetWorldMatrix(worldMatrix);
	}

	

	return true;
}
