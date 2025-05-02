#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_

#include "TextClass.h"
#include "CustomStructs.h"
#include "CustomEnums.h"

class UserInterfaceClass
{
public:

	bool Initialize(D3DClass*, int, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, const PrimitiveCounts& renderCounts,
		int, float, float, float, float, float, float);
	bool Render(D3DClass*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, float, float, float, float, float, float);


	int GetRenderCountStringRow(PrimitiveType primitiveType);
	bool UpdateRenderCountString(ID3D11DeviceContext*, int renderCount);
	bool UpdateRenderCountSpheresString(ID3D11DeviceContext* deviceContext, int renderCountSpheres);
	bool UpdateRenderCountCubesString(ID3D11DeviceContext* deviceContext, int renderCountCubes);
	bool UpdateRenderCountPyramidsString(ID3D11DeviceContext* deviceContext, int renderCountPyramids);
	bool UpdateRenderCountConesString(ID3D11DeviceContext* deviceContext, int renderCountCones);
	bool UpdateRenderCountHexPrismsString(ID3D11DeviceContext* deviceContext, int renderCountHexPrisms);

private:
	FontClass* m_Font1;
	TextClass *m_FpsString, *m_VideoStrings, *m_PositionStrings;

	TextClass* m_RenderCountString;
	TextClass* m_RenderCountSpheresString;
	TextClass* m_RenderCountCubesString;
	TextClass* m_RenderCountPyramidsString;
	TextClass* m_RenderCountConesString;
	TextClass* m_RenderCountHexPrismString;

	int m_previousFps;
	int m_previousPosition[6];

	int m_rowHeight;
	int m_fpsRow;
	int m_firstRenderCountRow, m_lastRenderCountRow;
	int m_firstPositionStringRow;

};

#endif