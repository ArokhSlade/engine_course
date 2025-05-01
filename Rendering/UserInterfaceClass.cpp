#include "UserInterfaceClass.h"

bool UserInterfaceClass::Initialize(D3DClass* Direct3D, int screenHeight, int screenWidth, int renderCountStringsCount)
{
	bool result;
	char videoCard[128];
	int videoMemory;
	char videoString[144];
	char memoryString[32];
	char tempString[16];
	int i;

	// Create the first font object.
	m_Font1 = new FontClass;
	if (!m_Font1)
	{
		return false;
	}

	// Initialize the first font object.
	result = m_Font1->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), "../Rendering/data/font01.txt", 
								 "../Rendering/data/font01.tga", 32.0f, 3);
	if (!result)
	{
		return false;
	}


	// Setup the video card strings.
	Direct3D->GetVideoCardInfo(videoCard, videoMemory);
	strcpy_s(videoString, "Video Card: ");
	strcat_s(videoString, videoCard);

	_itoa_s(videoMemory, tempString, 10);

	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");


	m_rowHeight = 20;
	int row = 10;

	////////////////////////////////////////////////////////////////////////////
	// VIDEO & FPS STRINGS
	////////////////////////////////////////////////////////////////////////////

	// Create the text objects for the video strings.
	m_VideoStrings = new TextClass[2];
	if (!m_VideoStrings)
	{
		return false;
	}

	// Initialize the video text strings.
	result = m_VideoStrings[0].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 256, false, m_Font1, 
										  videoString, 10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	row += m_rowHeight;
	result = m_VideoStrings[1].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1, 
										  memoryString, 10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false;
	}



	// Create the text object for the fps string.
	m_FpsString = new TextClass;
	if (!m_FpsString)
	{
		return false;
	}

	row += m_rowHeight;
	m_fpsRow = row;
	// Initialize the fps text string.
	result = m_FpsString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1,
		"Fps: 0", 10, m_fpsRow, 0.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Initial the previous frame fps.
	m_previousFps = -1;


	
	////////////////////////////////////////////////////////////////////////////
	// RENDER COUNT STRINGS
	////////////////////////////////////////////////////////////////////////////

	// Create the text object for the rendercount string.
	m_RenderCountString = new TextClass;
	if (!m_RenderCountString)
	{
		return false;
	}

	row += 2*m_rowHeight;
	m_firstRenderCountRow = row;
	// Initialize the fps text string.
	result = m_RenderCountString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1,
		"Rendercount: 0", 10, m_firstPositionStringRow, 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Create the text object for the render count string.
	m_RenderCountSpheresString = new TextClass;
	if (!m_RenderCountSpheresString)
	{
		return false;
	}
	
	row += m_rowHeight;
	// Initialize the render count text string.
	result = m_RenderCountSpheresString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1,
		"Spheres Count: 0", 10, row, 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Create the text object for the render count string.
	m_RenderCountCubesString = new TextClass;
	if (!m_RenderCountCubesString)
	{
		return false;
	}

	row += m_rowHeight;
	// Initialize the render count text string.
	result = m_RenderCountCubesString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1,
		"Cubes Count: 0", 10, row, 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Create the text object for the render count string.
	m_RenderCountPyramidsString = new TextClass;
	if (!m_RenderCountPyramidsString)
	{
		return false;
	}

	row += m_rowHeight;
	// Initialize the render count text string.
	result = m_RenderCountPyramidsString->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, false, m_Font1,
		"Pyramids Count: 0", 10, row, 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	m_lastRenderCountRow = row;

	////////////////////////////////////////////////////////////////////////////
	// POSITION STRINGS
	////////////////////////////////////////////////////////////////////////////
	// Create the text objects for the position strings.
	m_PositionStrings = new TextClass[6];
	if(!m_PositionStrings)
	{
		return false;
	}

	// Initialize the position text strings.
	row += 2 * m_rowHeight;	
	m_firstPositionStringRow = row;
	result = m_PositionStrings[0].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "X: 0",  10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	row += m_rowHeight;
	result = m_PositionStrings[1].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "Y: 0",  10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	row += m_rowHeight;
	result = m_PositionStrings[2].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "Z: 0",  10, row, 1.0f, 1.0f, 1.0f);  
	if(!result) 
	{ 
		return false; 
	}

	row += m_rowHeight;
	result = m_PositionStrings[3].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "rX: 0", 10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false;
	}

	row += m_rowHeight;
	result = m_PositionStrings[4].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "rY: 0", 10, row, 1.0f, 1.0f, 1.0f);
	if(!result)
	{ 
		return false; 
	}

	row += m_rowHeight;
	result = m_PositionStrings[5].Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), screenWidth, screenHeight, 16, false, m_Font1, 
											 "rZ: 0", 10, row, 1.0f, 1.0f, 1.0f);  
	if(!result) 
	{ 
		return false; 
	}

	// Initialize the previous frame position.
	for(i=0; i<6; i++)
	{
		m_previousPosition[i] = -1;
	}

	return true;
}

void UserInterfaceClass::Shutdown()
{
	// Release the position text strings.
	if(m_PositionStrings)
	{
		m_PositionStrings[0].Shutdown();
		m_PositionStrings[1].Shutdown();
		m_PositionStrings[2].Shutdown();
		m_PositionStrings[3].Shutdown();
		m_PositionStrings[4].Shutdown();
		m_PositionStrings[5].Shutdown();

		delete [] m_PositionStrings;
		m_PositionStrings = 0;
	}

	// Release the video card string.
	if(m_VideoStrings)
	{
		m_VideoStrings[0].Shutdown();
		m_VideoStrings[1].Shutdown();

		delete [] m_VideoStrings;
		m_VideoStrings = 0;
	}


	// Release the fps text string.
	if(m_FpsString)
	{
		m_FpsString->Shutdown();
		delete m_FpsString;
		m_FpsString = 0;
	}

	// Release the rendercount text string.
	if (m_RenderCountString)
	{
		m_RenderCountString->Shutdown();
		delete m_RenderCountString;
		m_RenderCountString = 0;
	}

	if (m_RenderCountSpheresString)
	{
		m_RenderCountSpheresString->Shutdown();
		delete m_RenderCountSpheresString;
		m_RenderCountSpheresString = 0;
	}

	if (m_RenderCountCubesString)
	{
		m_RenderCountCubesString->Shutdown();
		delete m_RenderCountCubesString;
		m_RenderCountCubesString = 0;
	}

	if (m_RenderCountPyramidsString)
	{
		m_RenderCountPyramidsString->Shutdown();
		delete m_RenderCountPyramidsString;
		m_RenderCountPyramidsString = 0;
	}

	// Release the font object.
	if(m_Font1)
	{
		m_Font1->Shutdown();
		delete m_Font1;
		m_Font1 = 0;
	}

	return;
}

bool UserInterfaceClass::Frame(ID3D11DeviceContext* deviceContext, const PrimitiveCounts& renderCounts,
								int fps, float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	bool result;

	// Update the fps string.
	result = UpdateFpsString(deviceContext, fps);
	if(!result)
	{
		return false;
	}

	result = UpdateRenderCountString(deviceContext, renderCounts.GetTotalCount());
	if (!result)
	{
		return false;
	}

	result = UpdateRenderCountSpheresString(deviceContext, renderCounts.sphereCount);
	if (!result)
	{
		return false;
	}

	result = UpdateRenderCountCubesString(deviceContext, renderCounts.cubeCount);
	if (!result)
	{
		return false;
	}

	result = UpdateRenderCountPyramidsString(deviceContext, renderCounts.pyramidCount);
	if (!result)
	{
		return false;
	}

	// Update the position strings.
	result = UpdatePositionStrings(deviceContext, posX, posY, posZ, rotX, rotY, rotZ);
	if(!result)
	{
		return false;
	}

	return true;
}

bool UserInterfaceClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix, 
								XMMATRIX orthoMatrix)
{
	int i;

	// Turn off the Z buffer and enable alpha blending to begin 2D rendering.
	Direct3D->TurnZBufferOff();
	Direct3D->EnableAlphaBlending();

	// Render the fps string.
	m_FpsString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());

	m_RenderCountString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	m_RenderCountSpheresString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	m_RenderCountCubesString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	m_RenderCountPyramidsString->Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());

	// Render the video card strings.
	m_VideoStrings[0].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	m_VideoStrings[1].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());

	// Render the position and rotation strings.
	for(i=0; i<6; i++)
	{
		m_PositionStrings[i].Render(Direct3D->GetDeviceContext(), ShaderManager, worldMatrix, viewMatrix, orthoMatrix, m_Font1->GetTexture());
	}

	// Turn off alpha blending now that the text has been rendered.
	Direct3D->DisableAlphaBlending();

	// Turn the Z buffer back on now that the 2D rendering has completed.
	Direct3D->TurnZBufferOn();

	return true;
}

bool UserInterfaceClass::UpdateFpsString(ID3D11DeviceContext* deviceContext, int fps)
{
	char tempString[16];
	char finalString[16];
	float red, green, blue;
	bool result;

	// Check if the fps from the previous frame was the same, if so don't need to update the text string.
	if(m_previousFps == fps)
	{
		return true;
	}

	// Store the fps for checking next frame.
	m_previousFps = fps;

	// Truncate the fps to below 100,000.
	if(fps > 99999)
	{
		fps = 99999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(finalString, "Fps: ");
	strcat_s(finalString, tempString);

	// If fps is 60 or above set the fps color to green.
	if(fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if(fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if(fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = m_FpsString->UpdateSentence(deviceContext, m_Font1, finalString, 10, m_fpsRow, red, green, blue);
	if(!result)
	{
		return false;
	}

	return true;
}

bool UserInterfaceClass::UpdateRenderCountString(ID3D11DeviceContext* deviceContext, int renderCount)
{
	char tempString[32];
	char finalString[32];
	bool result;

	// Convert the fps integer to string format.
	_itoa_s(renderCount, tempString, 10);

	// Setup the fps string.
	strcpy_s(finalString, "RenderCount: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_RenderCountString->UpdateSentence(deviceContext, m_Font1, finalString, 10, m_firstRenderCountRow, 0, 1, 0);
	if (!result)
	{
		return false;
	}

	return true;
}

int UserInterfaceClass::GetRenderCountStringRow(PrimitiveType primitiveType)
{
	int result = m_firstRenderCountRow + (1 + static_cast<int>(primitiveType)) * m_rowHeight;
	return result;
}

bool UserInterfaceClass::UpdateRenderCountSpheresString(ID3D11DeviceContext* deviceContext, int renderCountSpheres)
{
	char tempString[32];
	char finalString[32];
	bool result;

	// Convert the rendercount integer to string format.
	_itoa_s(renderCountSpheres, tempString, 10);

	// Setup the rendercount string.
	strcpy_s(finalString, "Spheres Count: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	int row = GetRenderCountStringRow(PrimitiveType::Sphere);
	result = m_RenderCountSpheresString->UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}

bool UserInterfaceClass::UpdateRenderCountCubesString(ID3D11DeviceContext* deviceContext, int renderCountCubes)
{
	char tempString[32];
	char finalString[32];
	bool result;

	// Convert the rendercount integer to string format.
	_itoa_s(renderCountCubes, tempString, 10);

	// Setup the rendercount string.
	strcpy_s(finalString, "Cubes Count: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	int row = GetRenderCountStringRow(PrimitiveType::Cube);
	result = m_RenderCountCubesString->UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}

bool UserInterfaceClass::UpdateRenderCountPyramidsString(ID3D11DeviceContext* deviceContext, int renderCountPyramids)
{
	char tempString[32];
	char finalString[32];
	bool result;

	// Convert the rendercount integer to string format.
	_itoa_s(renderCountPyramids, tempString, 10);

	// Setup the rendercount string.
	strcpy_s(finalString, "Pyramids Count: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	int row = GetRenderCountStringRow(PrimitiveType::Pyramid);
	result = m_RenderCountPyramidsString->UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	return true;
}

bool UserInterfaceClass::UpdatePositionStrings(ID3D11DeviceContext* deviceContext, float posX, float posY, float posZ, 
											   float rotX, float rotY, float rotZ)
{
	int positionX, positionY, positionZ, rotationX, rotationY, rotationZ;
	char tempString[16];
	char finalString[16];
	bool result;


	// Convert the float values to integers.
	positionX = (int)posX;
	positionY = (int)posY;
	positionZ = (int)posZ;
	rotationX = (int)rotX;
	rotationY = (int)rotY;
	rotationZ = (int)rotZ;

	// Update the position strings if the value has changed since the last frame.
	int row = m_firstPositionStringRow;
	if(positionX != m_previousPosition[0])
	{
		m_previousPosition[0] = positionX;
		_itoa_s(positionX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);

		result = m_PositionStrings[0].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f); 
		if(!result) { return false; }
	}

	row += m_rowHeight;
	if(positionY != m_previousPosition[1])
	{
		m_previousPosition[1] = positionY;
		_itoa_s(positionY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[1].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
		if(!result) { return false; }
	}

	row += m_rowHeight;
	if(positionZ != m_previousPosition[2])
	{
		m_previousPosition[2] = positionZ;
		_itoa_s(positionZ, tempString, 10);
		strcpy_s(finalString, "Z: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[2].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f); 
		if(!result) { return false; }
	}

	row += 2 * m_rowHeight;
	if(rotationX != m_previousPosition[3])
	{
		m_previousPosition[3] = rotationX;
		_itoa_s(rotationX, tempString, 10);
		strcpy_s(finalString, "rX: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[3].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
		if(!result) { return false; }
	}

	row += m_rowHeight;
	if(rotationY != m_previousPosition[4])
	{
		m_previousPosition[4] = rotationY;
		_itoa_s(rotationY, tempString, 10);
		strcpy_s(finalString, "rY: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[4].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
		if(!result) { return false; }
	}

	row += m_rowHeight;
	if(rotationZ != m_previousPosition[5])
	{
		m_previousPosition[5] = rotationZ;
		_itoa_s(rotationZ, tempString, 10);
		strcpy_s(finalString, "rZ: ");
		strcat_s(finalString, tempString);
		result = m_PositionStrings[5].UpdateSentence(deviceContext, m_Font1, finalString, 10, row, 1.0f, 1.0f, 1.0f);
		if(!result) { return false; }
	}

	return true;
}