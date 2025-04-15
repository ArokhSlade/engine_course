#include "Graphics.h"

Graphics::Graphics()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Position = 0;
	m_Terrain = 0;
	m_Model = 0;
	m_ModelList = 0;
	m_Frustum = 0;
	m_renderCount = m_sphereCount = m_cubeCount = 0;

	m_SphereAABB = m_CubeAABB = m_PyramidAABB = 0;
}

Graphics::~Graphics()
{
}

bool Graphics::Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;

	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if(!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(100.f, 5.0f, 50.f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), "../Rendering/data/seafloor.tga", "../Rendering/data/sphere.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Model object.", L"Error", MB_OK);
		return false;
	}

	m_SphereAABB = new AxisAlignedBoundingBox;
	if (!m_SphereAABB)
	{
		return false;
	}
	result = m_SphereAABB->Initialize(Direct3D->GetDevice(), m_Model->GetVertexList(), m_Model->GetVertexCount());


	// Create cube model
	m_CubeModel = new CubeModel;
	if (!m_CubeModel) {
		return false;
	}

	// Initialize cube model
	result = m_CubeModel->Initialize(Direct3D->GetDevice());
	if (!result) {
		MessageBox(hwnd, L"Could not initialize CubeModel object.", L"Error", MB_OK);
		return false;
	}

	m_CubeAABB = new AxisAlignedBoundingBox;
	if (!m_CubeAABB)
	{
		return false;
	}
	result = m_CubeAABB->Initialize(Direct3D->GetDevice(), m_CubeModel->GetVertexList(), m_CubeModel->GetVertexCount());

	
	m_PyramidModel = new PyramidModel;
	if (!m_PyramidModel) {
		return false;
	}
	result = m_PyramidModel->Initialize(Direct3D->GetDevice());
	if (!result) {
		MessageBox(hwnd, L"Could not initialize PyramidModel object.", L"Error", MB_OK);
		return false;
	}

	m_PyramidAABB = new AxisAlignedBoundingBox;
	if (!m_PyramidAABB)
	{
		return false;
	}
	result = m_PyramidAABB->Initialize(Direct3D->GetDevice(), m_PyramidModel->GetVertexList(), m_PyramidModel->GetVertexCount());

	// Create the model list object.
	m_ModelList = new ModelListClass;
	if (!m_ModelList)
	{
		return false;
	}

	const int sphereCount = 250;
	const int cubeCount = 250;
	const int pyramidCount = 250;
	// Initialize the model list object.
	result = m_ModelList->Initialize(sphereCount, cubeCount, pyramidCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}

	m_Frustum = new Frustum;
	if (!m_Frustum) {
		return false;
	}

	m_Frustum->Initialize(screenDepth);

	// Set the UI to display by default.
	m_displayUI = true;

	return true;
}

void Graphics::Shutdown()
{
	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the terrain object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_CubeModel)
	{
		m_CubeModel->Shutdown();
		delete m_CubeModel;
		m_CubeModel = 0;
	}

	if (m_PyramidModel)
	{
		m_PyramidModel->Shutdown();
		delete m_PyramidModel;
		m_PyramidModel = 0;
	}

	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if(m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}

bool Graphics::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, float frameTime, int fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Do the frame input processing.
	if (Input->IsEscPressed()) {
		return false;
	}
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);


	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), m_pyramidCount, m_cubeCount, m_sphereCount, m_renderCount, fps, posX, posY, posZ, rotX, rotY, rotZ);
	if(!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render(Direct3D, ShaderManager);
	if(!result)
	{
		return false;
	}

	return true;
}


void Graphics::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if(Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the user interface should be displayed or not.
	if (Input->IsF2Toggled())
	{
		m_displayAABBs = !m_displayAABBs;
	}

	return;
}

bool Graphics::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	int modelCount, index;
	float positionX, positionY, positionZ, rotationY, radius;
	XMFLOAT4 color;
	ModelType modelType;
	
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);

	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);
	
	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Render the terrain grid using the color shader.
	m_Terrain->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, 
											  projectionMatrix);
	if(!result)
	{
		return false;
	}

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	m_renderCount = m_sphereCount = m_cubeCount = m_pyramidCount = 0;

	bool isInsideFrustum;
	// Go through all the models and render them only if they can be seen by the camera view.
	for (index = 0; index < modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, modelType, positionX, positionY, positionZ, rotationY, color);

		switch (modelType) {
			break; case ModelType::SPHERE:
				isInsideFrustum = m_Frustum->IsSphereInsideFrustum(positionX, positionY, positionZ, 1.0f);
			break; case ModelType::CUBE:
				isInsideFrustum = m_Frustum->IsCubeInsideFrustum(positionX, positionY, positionZ, 1.0f);
			break; case ModelType::PYRAMID:
				isInsideFrustum = m_Frustum->IsCubeInsideFrustum(positionX, positionY, positionZ, 1.0f);
		}

		if (isInsideFrustum) {
			m_renderCount++;

			// Set the radius of the sphere to 1.0 since this is already known.
			radius = 1.0f;

			// Move the model to the location it should be rendered at.
			worldMatrix = XMMatrixRotationY(rotationY);
			XMMATRIX translationMatrix = XMMatrixTranslation(positionX, positionY, positionZ);
			worldMatrix = XMMatrixMultiply(worldMatrix, translationMatrix);
		
			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			switch (modelType) {
			break; case ModelType::SPHERE:
				m_Model->Render(Direct3D->GetDeviceContext());				
				m_sphereCount++;
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				if (m_displayAABBs)
				{
					m_SphereAABB->Render(Direct3D->GetDeviceContext());
					ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_SphereAABB->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				}
			break; case ModelType::CUBE:
				//m_CubeModel->Rotate(rotationY);
				m_CubeModel->Render(Direct3D->GetDeviceContext());
				m_cubeCount++;
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				if (m_displayAABBs)
				{					
					m_CubeAABB->Render(Direct3D->GetDeviceContext());
					ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_CubeAABB->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				}
			break; case ModelType::PYRAMID:
				m_PyramidModel->Render(Direct3D->GetDeviceContext());
				m_pyramidCount++;
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_PyramidModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				if (m_displayAABBs)
				{
					m_PyramidAABB->Render(Direct3D->GetDeviceContext());
					ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_PyramidAABB->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
				}
			}			
		}


		// Reset to the original world matrix.
		Direct3D->GetWorldMatrix(worldMatrix);
	}
	

	// Render the user interface.
	if(m_displayUI)
	{
		result = m_UserInterface->Render(Direct3D, ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix);
		if(!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}