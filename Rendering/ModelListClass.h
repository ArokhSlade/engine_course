#pragma once
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

#include "CustomEnums.h"
#include "CustomStructs.h"

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
	bool Initialize(const PrimitiveCounts&);
	void Shutdown();

	int GetTotalModelCount();
	const PrimitiveCounts& GetModelCounts();
	void GetData(int, float&, float&, float&, XMFLOAT4&, PrimitiveType& type);

private:	
	PrimitiveCounts m_modelCounts;
	ModelInfoType* m_ModelInfoList;

};

#endif