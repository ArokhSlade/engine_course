#pragma once
#include "D3DClass.h"
#include "ShaderManagerClass.h"

#include "Frustum.h"
#include "ModelListClass.h"
#include "ModelClass.h"
#include "CubeModel.h"
#include "PyramidModel.h"
#include "ConeModel.h"
#include "HexPrismModel.h"
#include "CustomStructs.h"

class PrimitiveCreator
{
public :
	bool Initialize(HWND hwnd, D3DClass* Direct3D, const PrimitiveCounts& modelCounts);
	void Shutdown();
	bool Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, PrimitiveCounts* renderCounts, 
				XMMATRIX, XMMATRIX, XMMATRIX, Frustum* frustum, bool displayAABBs);
	int GetTotalModelCount();
	const PrimitiveCounts& GetModelCounts();

private:	
	ModelListClass* m_ModelList;

	PrimitiveCounts m_modelCounts;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
	HexPrismModel* m_HexPrismModel;
	ConeModel* m_ConeModel;
};

