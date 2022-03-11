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
	Move(m_Status.bxMove, m_bXPlusMove, m_Status.Pos.x, m_Status.Speed.x, m_Status.StartPos.x, m_Status.EndPos.x);
	Move(m_Status.byMove, m_bYPlusMove, m_Status.Pos.y, m_Status.Speed.y, m_Status.StartPos.y, m_Status.EndPos.y);
	Move(m_Status.bzMove, m_bZPlusMove, m_Status.Pos.z, m_Status.Speed.z, m_Status.StartPos.z, m_Status.EndPos.z);
}

void CTarget::Move(bool bcan, bool& bmove, float& pos, float speed, float start, float end) {
	if (!bcan) { return; }
	if (bmove)
	{
		pos -= speed;
		if (pos < start)
		{
			bmove = false;
		}
	}
	else
	{
		pos += speed;
		if (pos > end)
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
	CGraphicsUtilities::RenderBox(box, m_Status.Color);
}

void CTarget::RenderDebug() {

}

void CTarget::Release() {

}