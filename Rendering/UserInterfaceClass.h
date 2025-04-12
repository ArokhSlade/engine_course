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

	bool Frame(ID3D11DeviceContext*, int, int, int, int, float, float, float, float, float, float);
	bool Render(D3DClass*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateRenderCountString(ID3D11DeviceContext*, int, int);
	bool UpdateSphereCountString(ID3D11DeviceContext*, int);
	bool UpdateCubeCountString(ID3D11DeviceContext*, int);
	bool UpdateFpsString(ID3D11DeviceContext*, int, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, int, float, float, float, float, float, float);

private:
	FontClass* m_Font1;
	TextClass* m_FpsString, * m_VideoStrings, * m_PositionStrings, * m_RenderCountString,
		*m_SphereCountString, *m_CubeCountString;
	int m_previousFps;
	int m_previousPosition[6];
};

#endif