#pragma once
#include "FlowerPartsStatus.h"

class CFlower
{
private:
	int m_PartsCount;
	FlowerPartsStatus m_Parts[30];

public:
	CFlower();
	~CFlower();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void Release();
};

