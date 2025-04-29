#pragma once

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
	bool Render();
private:
	ModelListClass* m_ModelList;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
};

