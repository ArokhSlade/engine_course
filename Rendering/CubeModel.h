#ifndef _CUBEMODEL_H_
#define _CUBEMODEL_H_

#include "SimpleModel.h"
#include "CustomTemplates.h"

class CubeModel : public SimpleModel
{
public:
	virtual int GetIndexCount() override;
	virtual int GetVertexCount() override;

protected:
	void InitializeVertices(ColorVertexType* vertices, unsigned long* indices) override;
};

#endif