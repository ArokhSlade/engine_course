#include <d3d11.h> //HWND

#include "PrimitiveCreator.h"
#include "CustomTemplates.h"



PrimitiveCreator::PrimitiveCreator()
{
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
}

bool PrimitiveCreator::Render()
{
	return true;
}
