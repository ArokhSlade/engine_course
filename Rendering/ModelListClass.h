#pragma once
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

#include <stdlib.h>
#include <time.h>
#include <directxmath.h>
#include "CustomEnum.h"
#include "CustomStruct.h"

using namespace DirectX;

class ModelListClass
{
private:
	struct ModelInfoType
	{
		XMFLOAT4 color;
		VectorType posA, posB;
		PrimitiveType modelType;
		float ratio;
		bool movingBackward;
		float rotationY;
		float scale;
	};

public:
	ModelListClass();
	~ModelListClass();

	bool Initialize(int,int,int, int, int, int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, PrimitiveType&, float&, float&, float&, float&, float&, XMFLOAT4&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

#endif