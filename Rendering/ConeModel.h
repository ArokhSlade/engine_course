#pragma once
#include "SimpleModel.h"
class ConeModel : public SimpleModel
{
public:
	int GetIndexCount() override;
	int GetVertexCount() override;

protected:
	void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) override;
private: 
	int m_circleSides = 32;
};

