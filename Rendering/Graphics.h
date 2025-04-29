#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "D3DClass.h"
#include "InputClass.h"
#include "ShaderManagerClass.h"
#include "TimerClass.h"
#include "UserInterfaceClass.h"
#include "CameraClass.h"
#include "PositionClass.h"
#include "TerrainClass.h"

#include "Frustum.h"
#include "PrimitiveCreator.h"

#include "ModelListClass.h"

#include "ModelClass.h"
#include "CubeModel.h"
#include "PyramidModel.h"

#include "AxisAlignedBoundingBox.h"

#include "SkyDome.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*);

private:
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	PositionClass* m_Position;
	TerrainClass* m_Terrain;
	
	bool m_displayUI;
	bool m_displayAABBs;

	PrimitiveCreator* m_PrimitiveCreator;
	Frustum* m_Frustum;

	ModelListClass* m_ModelList;

	ModelClass* m_SphereModel;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;

	AxisAlignedBoundingBox* m_aabbSphere;
	AxisAlignedBoundingBox* m_aabbCube;
	AxisAlignedBoundingBox* m_aabbPyramid;

	int m_renderCountSpheres;
	int m_renderCountCubes;
	int m_renderCountPyramids;

	SkyDome* m_skyDome;
};

#endif