#include "ModelListClass.h"
#include "CustomMath.h"
#include "D3DClass.h"

ModelListClass::ModelListClass()
{
	m_ModelInfoList = 0;
}

ModelListClass::~ModelListClass()
{
}

bool ModelListClass::Initialize(int numSpheres, int numCubes, int numPyramids, int cylinderCount, int houseCount, int diamondCount)
{
	float red, green, blue;


	// Store the number of models.
	m_modelCount = numSpheres + numCubes + numPyramids + cylinderCount + houseCount + diamondCount;

	// Create a list array of the model information.
	m_ModelInfoList = new ModelInfoType[m_modelCount];
	if (!m_ModelInfoList)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	const int modelTypeCount = static_cast<int>(PrimitiveType::ENUM_SIZE);
	int modelCounts[modelTypeCount] = { numSpheres, numCubes, numPyramids, cylinderCount, houseCount, diamondCount};
	// Go through all the models and randomly generate the model color and position.
	int totalModelIndex = 0;
	for (int i_modelTypeIndex = 0 ; i_modelTypeIndex < modelTypeCount ; i_modelTypeIndex++)
	{
		for (int j_modelIndex = 0 ; j_modelIndex < modelCounts[i_modelTypeIndex]; j_modelIndex++, totalModelIndex++)
		{
			if (totalModelIndex > m_modelCount) {
				return false;
			}

			auto& currentModel = m_ModelInfoList[totalModelIndex];
			currentModel.modelType = static_cast<PrimitiveType>(i_modelTypeIndex);

			// Generate a random color for the model.
			red = (float)rand() / RAND_MAX;
			green = (float)rand() / RAND_MAX;
			blue = (float)rand() / RAND_MAX;

			currentModel.color = XMFLOAT4(red, green, blue, 1.0f);

			// Generate a random position in front of the viewer for the mode.
			currentModel.posA.x = (float)rand() / RAND_MAX * 100.f;
			currentModel.posA.y = (float)rand() / RAND_MAX * 100.f;
			currentModel.posA.z = (float)rand() / RAND_MAX * 100.f;

			currentModel.posB.x = (float)rand() / RAND_MAX * 100.f;
			currentModel.posB.y = (float)rand() / RAND_MAX * 100.f;
			currentModel.posB.z = (float)rand() / RAND_MAX * 100.f;

			currentModel.ratio = .5f;
			currentModel.movingBackward = false;

			currentModel.rotationY = 0.f;
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


void ModelListClass::GetData(int index, PrimitiveType& modelType, float& positionX, float& positionY, float& positionZ, float& rotationY, XMFLOAT4& color)
{
	auto& model = m_ModelInfoList[index];

	const float speed = 1.f;

	//TODO(Gerald) get actual frame time
	float secondsPerFrame = 1.f / 60.f;
	model.ratio += speed * secondsPerFrame * (model.movingBackward ? -1.f : 1.f);
	if (model.ratio > 1.f || model.ratio < 0.f) {
		model.movingBackward = !model.movingBackward;
	}
	model.ratio = clamp(model.ratio, 0.f, 1.f);

	positionX = lerp(model.posA.x, model.posB.x, model.ratio);
	positionY = lerp(model.posA.y, model.posB.y, model.ratio);
	positionZ = lerp(model.posA.z, model.posB.z, model.ratio);

	color = m_ModelInfoList[index].color;

	modelType = m_ModelInfoList[index].modelType;
		
	model.rotationY += 360.f * secondsPerFrame;
	if (model.rotationY > 360.f) model.rotationY -= 360.f;
	rotationY = model.rotationY;

	return;
}