#pragma once
#include "D3DClass.h"
#include "ShaderManagerClass.h"

#include "Frustum.h"
#include "ModelListClass.h"
#include "ModelClass.h"
#include "CubeModel.h"
#include "PyramidModel.h"

class PrimitiveCreator
{
public :
	bool Initialize(HWND hwnd, D3DClass* Direct3D, int modelCount);
	void Shutdown();
	bool Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, XMMATRIX, XMMATRIX, XMMATRIX, Frustum* frustum, bool displayAABBs);
private:	
	ModelListClass* m_ModelList;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
};

