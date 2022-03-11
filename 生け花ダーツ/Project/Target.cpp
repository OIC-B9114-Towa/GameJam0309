#include "Target.h"

CTarget::CTarget() :
	m_Pos(),
	m_Scale(),
	m_Rotate(),
	m_bLeftMove(true),
	m_bMove(true) {

}

CTarget::~CTarget() {

}

void CTarget::Initialize() {
	m_Scale = CVector3(2, 0.1f, 2);
	m_Rotate = CVector3(0, 0, 0);
	m_Pos = CVector3(0, 2, 1);
	m_bMove = true;
}

void CTarget::Update() {
	if (!m_bMove) { return; }
	m_Rotate.y += 0.065f;
	if (m_bLeftMove)
	{
		m_Pos.x -= 0.1f;
		if (m_Pos.x < -5.0f)
		{
			m_bLeftMove = false;
		}
	}
	else
	{
		m_Pos.x += 0.1f;
		if (m_Pos.x > 5.0f)
		{
			m_bLeftMove = true;
		}
	}
}

void CTarget::UpdateDebug() {
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

void CTarget::Collision(CFlower& flower) {
	PartsSet parts = flower.GetParts();

	CBoxOBB box(m_Pos, m_Scale, m_Rotate);
	for (int i = 0; i < parts.Count; i++)
	{
		CBoxOBB fbox(parts.Parts[i].Translate + flower.GetPos(), parts.Parts[i].Scale, CVector3(0, 0, 0));
		if (box.CollisionOBB(fbox))
		{
			flower.Hit();
			m_bMove = false;
			return;
		}
	}
}

void CTarget::Render() {
	CBoxOBB box(m_Pos, m_Scale, m_Rotate);

	CVector4 color(0, 1, 0, 1);
	CGraphicsUtilities::RenderBox(box, color);
}

void CTarget::RenderDebug() {

}

void CTarget::Release() {

}