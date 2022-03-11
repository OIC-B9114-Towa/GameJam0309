#pragma once
#include "Flower.h"

class CTarget
{
private:
	CVector3 m_Pos;
	CVector3 m_Scale;
	CVector3 m_Rotate;

	bool m_bLeftMove;
	bool m_bMove;

public:
	CTarget();
	~CTarget();

	void Initialize();
	void Update();
	void UpdateDebug();
	void Collision(CFlower& flower);
	void Render();
	void RenderDebug();
	void Release();
};

