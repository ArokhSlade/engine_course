#pragma once
#include "D3DClass.h"
#include "ShaderManagerClass.h"

#include "Frustum.h"
#include "ModelListClass.h"
#include "ModelClass.h"
#include "CubeModel.h"
#include "PyramidModel.h"
#include "PinModel.h"
#include "HexPrismModel.h"
#include "CustomStructs.h"

class PrimitiveCreator
{
public :
	bool Initialize(HWND hwnd, D3DClass* Direct3D, PrimitiveCounts modelCounts);
	void Shutdown();
	bool Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, PrimitiveCounts*, 
				XMMATRIX, XMMATRIX, XMMATRIX, Frustum* frustum, bool displayAABBs);
private:	
	ModelListClass* m_ModelList;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
	HexPrismModel* m_HexPrismModel;
	PinModel* m_PinModel;
};

