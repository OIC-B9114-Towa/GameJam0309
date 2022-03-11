#pragma once
#include "FlowerPartsStatus.h"

typedef struct tag_PartsSet
{
	int Count;
	FlowerPartsStatus Parts[30];

	tag_PartsSet():
		Count(0),
		Parts()	{
	}
}PartsSet;

class CFlower
{
private:
	CCamera	m_Camera;
	float m_CameraAngle;

	CVector3 m_vPos;
	CVector3 m_vTrans;

	PartsSet m_Parts;

	CVector3 m_CentralPos;
	CVector3 m_Pos;
	CVector3 m_Rotate;
	float m_MoveZ;

	int m_MaxLife;
	int m_Life;


	bool m_bFire;

	void InitializeParts();
	void InitializePos();

	void UpdateCamera();

public:
	CFlower();
	~CFlower();
	bool Load();
	void Initialize();
	void Update();
	void Fire();
	void Hit();
	void UpdateDebug();
	void Render();
	void RenderDebug();
	void Release();

	void SetCameraEnable();

	bool GetFire() { return m_bFire; }

	PartsSet GetParts() { return m_Parts; }
	CVector3 GetPos() { return m_Pos; }
};

