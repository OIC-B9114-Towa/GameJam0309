#pragma once
#include "FlowerPartsLoder.h"

class CFlower
{
private:
	int m_HitBlockNo;
	CVector3 m_GapPos;

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
	bool Load(PartsSet set);
	void Initialize();
	void Update();
	void Fire();
	void Hit(int no, CVector3 pos);
	void UpdateDebug();
	void Render();
	void Render(CVector3 pos);
	void RenderDebug();
	void Release();

	void SetCameraEnable();

	bool GetFire() { return m_bFire; }
	int GetNo() { return m_HitBlockNo; }

	PartsSet GetParts() { return m_Parts; }
	CVector3 GetPos() { return m_Pos; }
};

