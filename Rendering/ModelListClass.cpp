#include "ModelListClass.h"
#include "CustomTemplates.h"
#include "CustomEnums.h"
#include <stdexcept>

bool ModelListClass::Initialize(const PrimitiveCounts& modelCounts)
{
	// Create a list array of the model information.	
	int totalModelCount = modelCounts.GetTotalCount();
	m_ModelInfoList = new ModelInfoType[totalModelCount];
	if (!m_ModelInfoList)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	int total_index = 0;

	for (int primTypeIdx = 0; primTypeIdx < static_cast<int>(PrimitiveType::PRIMITIVES_COUNT); ++primTypeIdx) {
		float red, green, blue;
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		//TODO(Gerald): brittle code, relies on modelCounts being structured like an array of ints
		for (int curPrimIdx = 0; curPrimIdx < reinterpret_cast<const int*>(&modelCounts)[primTypeIdx]; ++curPrimIdx)
		{
			//DEBUG CHECK
			if (total_index >= totalModelCount) {
				throw std::runtime_error("error: index exceeded model count");
			}

			m_ModelInfoList[total_index].color = XMFLOAT4(red, green, blue, 1.0f);

			m_ModelInfoList[total_index].positionX = (float)rand() / 100;
			m_ModelInfoList[total_index].positionY = (float)rand() / 100;
			m_ModelInfoList[total_index].positionZ = (float)rand() / 100;

			m_ModelInfoList[total_index].type = static_cast < PrimitiveType>(primTypeIdx);

			total_index++;
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

void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, XMFLOAT4& color, PrimitiveType& type)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;

	type = m_ModelInfoList[index].type;
}