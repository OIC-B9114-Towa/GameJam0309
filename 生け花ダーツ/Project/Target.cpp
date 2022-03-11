#include "Target.h"

CTarget::CTarget() :
	m_Status(),
	m_Rotate(),
	m_bXPlusMove(true),
	m_bYPlusMove(true),
	m_bZPlusMove(true),
	m_bMove(true) {
}

CTarget::~CTarget() {

}

void CTarget::Initialize(TargetStatus st) {
	m_Status = st;
	m_Rotate = CVector3(0, 0, 0);
	m_bMove = true;
}

void CTarget::Update() {
	if (!m_bMove) { return; }
	Move(m_Status.bxMove, m_bXPlusMove, m_Status.Pos.x);
	Move(m_Status.byMove, m_bYPlusMove, m_Status.Pos.y);
	Move(m_Status.bzMove, m_bZPlusMove, m_Status.Pos.z);
}

void CTarget::Move(bool bcan, bool& bmove, float& pos) {
	if (!bcan) { return; }
	if (bmove)
	{
		pos -= 0.1f;
		if (pos < -8.0f)
		{
			bmove = false;
		}
	}
	else
	{
		pos += 0.1f;
		if (pos > 8.0f)
		{
			bmove = true;
		}
	}
}

void CTarget::UpdateDebug() {
	float speed = 0.125f;
	if (g_pInput->IsKeyHold(MOFKEY_Q))
	{
		m_Status.Pos.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_Status.Pos.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		m_Status.Pos.y += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		m_Status.Pos.y -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_E))
	{
		m_Status.Pos.z += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_Status.Pos.z -= speed;
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

bool CTarget::Collision(CFlower& flower, int no) {
	if (!flower.GetFire()) { return false; }
	PartsSet parts = flower.GetParts();

	CBoxOBB box(m_Status.Pos, m_Status.Scale, m_Rotate);
	for (int i = 0; i < parts.Count; i++)
	{
		CBoxOBB fbox(parts.Parts[i].Translate + flower.GetPos(), parts.Parts[i].Scale, CVector3(0, 0, 0));
		if (box.CollisionOBB(fbox))
		{
			flower.Hit(no, m_Status.Pos);
			return true;
		}
	}
	return false;
}

void CTarget::Render() {
	CBoxOBB box(m_Status.Pos, m_Status.Scale, m_Rotate);

	CVector4 color(0, 1, 0, 1);
	CGraphicsUtilities::RenderBox(box, color);
}

void CTarget::RenderDebug() {

}

void CTarget::Release() {

}