#pragma once
#include "FlowerPartsStatus.h"

class CFlower
{
private:
	int m_PartsCount;
	FlowerPartsStatus m_Parts[30];

	CVector3 m_CentralPos;
	CVector3 m_Pos;
	CVector3 m_Rotate;


public:
	CFlower();
	~CFlower();
	bool Load();
	void Initialize();
	void Update();
	void UpdateDebug();
	void Render();
	void Release();
};

