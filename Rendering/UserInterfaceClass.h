#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_

#include "TextClass.h"

class UserInterfaceClass
{
public:
	UserInterfaceClass();
	~UserInterfaceClass();

	bool Initialize(D3DClass*, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int renderCount, int renderCountSpheres, int renderCountCubes, int renderCountPyramids, 
		int, float, float, float, float, float, float);
	bool Render(D3DClass*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, float, float, float, float, float, float);

	bool UpdateRenderCountString(ID3D11DeviceContext*, int renderCount);
	bool UpdateRenderCountSpheresString(ID3D11DeviceContext* deviceContext, int renderCountSpheres);
	bool UpdateRenderCountCubesString(ID3D11DeviceContext* deviceContext, int renderCountCubes);
	bool UpdateRenderCountPyramidsString(ID3D11DeviceContext* deviceContext, int renderCountPyramids);

private:
	FontClass* m_Font1;
	TextClass *m_FpsString, *m_VideoStrings, *m_PositionStrings;

	TextClass* m_RenderCountString;
	TextClass* m_RenderCountSpheresString;
	TextClass* m_RenderCountCubesString;
	TextClass* m_RenderCountPyramidsString;

	int m_previousFps;
	int m_previousPosition[6];
};

#endif