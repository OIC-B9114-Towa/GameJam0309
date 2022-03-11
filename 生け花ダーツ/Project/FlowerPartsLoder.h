#pragma once
#include "FlowerPartsStatus.h"
#include "InGameData.h"
#include <Mof.h>

class CFlowerPartsLoder
{
private:
	std::vector<PartsSet> m_Set;

	CFlowerPartsLoder() :
		m_Set()	{
		Load();
	}
public:
	static CFlowerPartsLoder& GetInstance()	{
		static CFlowerPartsLoder obj;
		return obj;
	}
	void Load();
	PartsSet GetBoxStatus(FlowerType type);
	PartsSet GetBoxStatus(int type);
	PartsSet GetRandomBoxStatus();
};

