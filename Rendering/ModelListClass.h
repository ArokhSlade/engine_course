#pragma once
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

#include <stdlib.h>
#include <time.h>
#include <directxmath.h>
using namespace DirectX;

enum class ModelType {
	INVALID = -1,
	SPHERE,
	CUBE,
	PYRAMID,
	ENUM_SIZE
};

class ModelListClass
{
private:
	struct ModelInfoType
	{
		XMFLOAT4 color;
		float positionX, positionY, positionZ;
		ModelType modelType;
	};

public:
	ModelListClass();
	~ModelListClass();

	bool Initialize(int,int,int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, ModelType&, float&, float&, float&, XMFLOAT4&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

#endif