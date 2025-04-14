#include "ModelListClass.h"

ModelListClass::ModelListClass()
{
	m_ModelInfoList = 0;
}

ModelListClass::~ModelListClass()
{
}

bool ModelListClass::Initialize(int numSpheres, int numCubes, int numPyramids)
{
	float red, green, blue;


	// Store the number of models.
	m_modelCount = numSpheres + numCubes + numPyramids;

	// Create a list array of the model information.
	m_ModelInfoList = new ModelInfoType[m_modelCount];
	if (!m_ModelInfoList)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	int modelCounts[3] = { numSpheres, numCubes, numPyramids };

	// Go through all the models and randomly generate the model color and position.
	for (int modelTypeIndex = 0 ; modelTypeIndex < static_cast<int>(ModelType::ENUM_SIZE) ; modelTypeIndex++)
	{
		for (int modelIndex = 0 ; modelIndex < modelCounts[modelIndex]; modelIndex++)
		{
			m_ModelInfoList[modelIndex].modelType = static_cast<ModelType>(modelTypeIndex);

			// Generate a random color for the model.
			red = (float)rand() / RAND_MAX;
			green = (float)rand() / RAND_MAX;
			blue = (float)rand() / RAND_MAX;

			m_ModelInfoList[modelIndex].color = XMFLOAT4(red, green, blue, 1.0f);

			// Generate a random position in front of the viewer for the mode.
			m_ModelInfoList[modelIndex].positionX = (float)rand() / RAND_MAX * 100.f;
			m_ModelInfoList[modelIndex].positionY = (float)rand() / RAND_MAX * 100.f;
			m_ModelInfoList[modelIndex].positionZ = (float)rand() / RAND_MAX * 100.f;
		}
	}

	return true;
}


void ModelListClass::Shutdown()
{
	// Release the model information list.
	if (m_ModelInfoList)
	{
		delete[] m_ModelInfoList;
		m_ModelInfoList = 0;
	}

	return;
}


int ModelListClass::GetModelCount()
{
	return m_modelCount;
}


void ModelListClass::GetData(int index, ModelType& modelType, float& positionX, float& positionY, float& positionZ, XMFLOAT4& color)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;

	modelType = m_ModelInfoList[index].modelType;
	return;
}