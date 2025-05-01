#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_

#include "SimpleModel.h"
#include "CustomTemplates.h"

class CubeModel : public SimpleModel
{
public:
	bool Initialize(ID3D11Device* device) override;
	void Shutdown() override;
	void Render(ID3D11DeviceContext* deviceContext) override;
};

#endif