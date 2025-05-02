#include "Graphics.h"
#include "CustomTemplates.h"
#include "CustomMacros.h"
#include "CustomEnums.h"

bool Graphics::Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;
	ID3D11Device* device = Direct3D->GetDevice();

	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if(!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.

	int renderCountStringsCount = static_cast<int>(PrimitiveType::PRIMITIVES_COUNT) + 1;
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth, renderCountStringsCount);
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
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	if (!ConstructAndInitialize(m_Terrain, device))
	{ 
		SHOW_INIT_ERROR_IN_HWND("TerrainClass object");
		return false; 
	}

	PrimitiveCounts modelCounts{
		1, 1, 1, 500, 500,
	};
	if (!ConstructAndInitialize(m_PrimitiveCreator, hwnd, Direct3D, modelCounts))
	{
		SHOW_INIT_ERROR_IN_HWND("PrimitiveCreator");
		return false;
	}

	if (!ConstructAndInitialize(m_Frustum, screenDepth))
	{
		SHOW_INIT_ERROR_IN_HWND("Frustum");
		return false;
	}

	if (!ConstructAndInitialize(m_SkyDome, device))
	{
		SHOW_INIT_ERROR_IN_HWND("Frustum");
		return false;
	}
	
	// Set the UI to display by default.
	m_displayUI = true;

	m_displayAABBs = false;

	return true;
}

void Graphics::Shutdown()
{
	ShutdownAndDelete(m_SkyDome);
	ShutdownAndDelete(m_Terrain);	
	ShutdownAndDelete(m_PrimitiveCreator);

	DeleteAndZero(m_Position);
	DeleteAndZero(m_Camera);

	ShutdownAndDelete(m_UserInterface);

	return;
}

bool Graphics::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, float frameTime, int fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Do the frame input processing.
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), m_renderCounts,
									fps, posX, posY, posZ, rotX, rotY, rotZ);	
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
	float positionX, positionY, positionZ, radius;
	XMFLOAT4 color;
	PrimitiveType primitiveType;

	ID3D11DeviceContext* deviceContext = Direct3D->GetDeviceContext();

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


	// skydome start

	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	XMFLOAT3 cameraPosition = m_Camera->GetPosition();
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	m_SkyDome->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderSkyDomeShader(Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(),
												worldMatrix, viewMatrix, projectionMatrix, 
												m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result)
	{
		return false;
	}

	Direct3D->GetWorldMatrix(worldMatrix);
	
	Direct3D->TurnZBufferOn();
	Direct3D->TurnOnCulling();
	
	// skydome end

	// Render the terrain grid using the color shader.
	m_Terrain->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, 
											  projectionMatrix);
	if(!result)
	{
		return false;
	}

	m_PrimitiveCreator->Render(Direct3D, ShaderManager, &m_renderCounts, worldMatrix, viewMatrix, projectionMatrix, m_Frustum, m_displayAABBs);
	
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