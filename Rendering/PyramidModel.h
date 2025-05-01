#ifndef _PYRAMIDMODEL_H_
#define _PYRAMIDMODEL_H_

#include <stdlib.h>
#include <time.h>

#include "SimpleModel.h"

class PyramidModel : public SimpleModel
{
public:
	void Render(ID3D11DeviceContext* deviceContext) override;

	virtual int GetIndexCount() override;
	virtual int GetVertexCount() override;

protected: 
	void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) override;
};

#endif