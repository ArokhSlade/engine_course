#ifndef _PYRAMIDMODEL_H_
#define _PYRAMIDMODEL_H_

#include <stdlib.h>
#include <time.h>

#include "SimpleModel.h"

class PyramidModel : public SimpleModel
{
public:

	bool Initialize(ID3D11Device* device) override;
	void Shutdown() override;
	void Render(ID3D11DeviceContext* deviceContext) override;
};

#endif