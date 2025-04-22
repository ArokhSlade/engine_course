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
#include "ModelClass.h"
#include "ModelListClass.h"
#include "Frustum.h"
#include "CubeModel.h"
#include "PyramidModel.h"
#include "AxisAlignedBoundingBox.h"
#include "SkyDome.h"
#include "CylinderModel.h"

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
	ModelClass* m_Model;
	ModelListClass* m_ModelList;	
	bool m_displayUI;

	Frustum* m_Frustum;
	CubeModel* m_CubeModel;
	PyramidModel* m_PyramidModel;
	CylinderModel* m_CylinderModel;

	AxisAlignedBoundingBox* m_SphereAABB, *m_CubeAABB, *m_PyramidAABB, *m_CylinderAABB;
	bool m_displayAABBs;

	int m_renderCount, m_sphereCount, m_cubeCount, m_pyramidCount, m_cylinderCount, m_houseCount, m_diamondCount;

	SkyDome* m_skyDome;
};

#endif