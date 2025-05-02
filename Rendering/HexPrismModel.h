#pragma once
#include "SimpleModel.h"
class HexPrismModel : public SimpleModel
{
public:
	virtual int GetIndexCount() override;
	virtual int GetVertexCount() override;

protected:    
    void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) override;
};

