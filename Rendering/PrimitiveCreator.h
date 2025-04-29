#pragma once
#include "ShaderManagerClass.h"

#include "ModelListClass.h"

#include "ModelClass.h"
#include "CubeModel.h"
#include "PyramidModel.h"

class PrimitiveCreator
{
public :
	PrimitiveCreator();
	~PrimitiveCreator();
	bool Initialize(HWND hwnd, ID3D11Device* device);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* ShaderManager, XMMATRIX, XMMATRIX, XMMATRIX);
private:
	ModelListClass* m_ModelList;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
};

