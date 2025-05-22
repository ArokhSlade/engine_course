#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_

#include "SimpleModel.h"
#include "CustomTemplates.h"

class CubeModel : public SimpleModel
{
public:
	CubeModel(ID3D11Device* device)
	{
		Initialize(device);
	}
	int GetIndexCount() override;
	int GetVertexCount() override;

protected:
	void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) override;
};

#endif