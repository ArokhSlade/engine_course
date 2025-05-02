#pragma once
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

#include "CustomEnums.h"

#include <stdlib.h>
#include <time.h>
#include <directxmath.h>
using namespace DirectX;

class ModelListClass
{
private:
	struct ModelInfoType
	{
		PrimitiveType type;
		XMFLOAT4 color;
		float positionX, positionY, positionZ;
	};

public:
	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, XMFLOAT4&, PrimitiveType& type);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

#endif