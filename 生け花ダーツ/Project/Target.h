#pragma once
#include "Flower.h"

typedef struct tag_TargetStatus
{
	int Score;
	CVector3 Pos;
	CVector3 Scale;
	bool bxMove;
	bool byMove;
	bool bzMove;

	tag_TargetStatus() :
		Score(100),
		Pos(0,0,0),
		Scale(0,0,0),
		bxMove(false),
		byMove(false),
		bzMove(false)
	{

	}

}TargetStatus;

class CTarget
{
private:
	CVector3 m_Rotate;

	TargetStatus m_Status;

	bool m_bMove;

	bool m_bXPlusMove;
	bool m_bYPlusMove;
	bool m_bZPlusMove;

	void Move(bool bcan, bool& bmove, float& pos);
public:
	CTarget();
	~CTarget();

	void Initialize(TargetStatus st);
	void Update();
	void UpdateDebug();
	bool Collision(CFlower& flower, int no);
	void Render();
	void RenderDebug();
	void Release();

	CVector3 GetPos() { return m_Status.Pos; }
	int GetScore() { return m_Status.Score; }
};

