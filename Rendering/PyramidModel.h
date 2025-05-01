#ifndef _PYRAMIDMODEL_H_
#define _PYRAMIDMODEL_H_

#include <stdlib.h>
#include <time.h>

#include "SimpleModel.h"

class PyramidModel : public SimpleModel
{
public:
	bool Initialize(ID3D11Device* device, fun_t initVerts = nullptr) override;
	void Render(ID3D11DeviceContext* deviceContext) override;
	void Shutdown() override;
};

#endif