#include "Flower.h"

CFlower::CFlower() :
	m_HitBlockNo(0),
	m_GapPos(0,0,0),
	m_Camera(),
	m_CameraAngle(0),
	m_Parts(),
	m_CentralPos(),
	m_Pos(0, 0, 0),
	m_Rotate(0, 0, 0),
	m_MoveZ(0),
	m_bFire(false),
	m_MaxLife(180),
	m_Life(0) {
}

CFlower::~CFlower() {

}

bool CFlower::Load(PartsSet set) {
	m_Parts = set;
	return true;
}

void CFlower::Initialize() {
	InitializePos();
	InitializeParts();

	m_HitBlockNo = -1;
	m_GapPos = CVector3(0, 0, 0);

	m_vPos = CVector3(0.0135f, 23.1420f, 1.8235f);
	m_vTrans = CVector3(0.0136f, 22.1426f, 1.859f);
	m_Camera.SetViewPort();
	m_Camera.LookAt(m_vPos, m_vTrans, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	m_Camera.Update();
}

void CFlower::InitializeParts() {
	CVector3 startpos(0, 0, 0);
	CVector3 endpos(0, 0, 0);

	for (int i = 0; i < m_Parts.Count; i++)
	{
		startpos.x = min(startpos.x, m_Parts.Parts[i].Translate.x);
		startpos.y = min(startpos.y, m_Parts.Parts[i].Translate.y);
		startpos.z = min(startpos.z, m_Parts.Parts[i].Translate.z);
		endpos.x = max(endpos.x, m_Parts.Parts[i].Translate.x);
		endpos.y = max(endpos.y, m_Parts.Parts[i].Translate.y);
		endpos.z = max(endpos.z, m_Parts.Parts[i].Translate.z);
	}

	m_CentralPos = (startpos + endpos) / 2;

	for (int i = 0; i < m_Parts.Count; i++)
	{
		m_Parts.Parts[i].Translate -= m_CentralPos;
	}
}

void CFlower::InitializePos() {
	m_Pos = CVector3(0, 15, 0);
	m_Rotate = CVector3(0, 0, 0);
	m_MoveZ = 0.05f;
	m_Life = m_MaxLife;
	m_bFire = false;
}

void CFlower::Update() {
	if (!m_bFire) { return; }

	m_Pos.y -= m_Speed;
	m_MoveZ = max(m_MoveZ - 0.002f, -0.02f);

	m_Pos.z += m_MoveZ;

	m_Life--;
}

void CFlower::Fire(float speed) {
	m_bFire = true;
	m_Speed = 0.2f * speed;
}

void CFlower::Hit(int no, CVector3 pos) {
	m_bFire = false;
	m_HitBlockNo = no;
	m_GapPos = m_Pos - pos;
}

void CFlower::UpdateDebug() {
	float speed = 0.125f;
	if (g_pInput->IsKeyHold(MOFKEY_Q))
	{
		m_Pos.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_Pos.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		m_Pos.y += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		m_Pos.y -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_E))
	{
		m_Pos.z += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_Pos.z -= speed;
	}

	if (g_pInput->IsKeyHold(MOFKEY_U))
	{
		m_Rotate.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_J))
	{
		m_Rotate.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_I))
	{
		m_Rotate.y += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_K))
	{
		m_Rotate.y -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_O))
	{
		m_Rotate.z += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_L))
	{
		m_Rotate.z -= speed;
	}
}

void CFlower::Render() {
	//?l?X???v???~?e?B?u????????
	CMatrix44 matWorld;

	for (int i = 0; i < m_Parts.Count; i++)
	{
		CBoxOBB box(m_Pos + m_Parts.Parts[i].Translate, m_Parts.Parts[i].Scale, m_Rotate);

		CGraphicsUtilities::RenderBox(box, m_Parts.Parts[i].Color);
	}
}

void CFlower::Render(CVector3 pos) {
	//?l?X???v???~?e?B?u????????
	CMatrix44 matWorld;

	for (int i = 0; i < m_Parts.Count; i++)
	{
		CBoxOBB box(m_GapPos + m_Parts.Parts[i].Translate + pos, m_Parts.Parts[i].Scale, m_Rotate);

		CGraphicsUtilities::RenderBox(box, m_Parts.Parts[i].Color);
	}
}

void CFlower::RenderDebug() {

}

void CFlower::Release() {

}

void CFlower::SetCameraEnable() {
	CGraphicsUtilities::SetCamera(&m_Camera);
}