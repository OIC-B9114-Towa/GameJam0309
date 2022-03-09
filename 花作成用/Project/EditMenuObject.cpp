#include "EditMenuObject.h"

void CEditMenuObject::Initialize() {
	m_SubMenu.Initialize();

	InitializeButton();
	InitializeLabel();
	InitializeTextBox();

	m_MStatus.Size = CVector2(400, 720);
	m_MStatus.Type = 2;
	m_MStatus.SurfaceColor = MOF_XRGB(150, 150, 150);
	m_MStatus.SubMenuCount = 1;

	CMenu::Initialize(m_MStatus, &m_SubMenu, m_LStatus, m_BStatus, m_TStatus);
}

void CEditMenuObject::InitializeButton() {
	for (int i = 0; i < m_BCount; i++)
	{
		m_BStatus[i].Size = CVector2(160, 40);
		m_BStatus[i].Pos = CVector2(220, i * 50 - 30);
		m_BStatus[i].Text = m_BMessage[i];
	}

	m_BStatus[0].Size = CVector2(160, 40);
	m_BStatus[0].Pos = CVector2(30, 660);

	m_MStatus.ButtonCount = m_BCount;
}

void CEditMenuObject::InitializeLabel() {
	for (int i = 0; i < m_LCount; i++)
	{
		m_LStatus[i].Size = CVector2(160, 30);
		m_LStatus[i].Pos = CVector2(220, i * 80 + 120);
		m_LStatus[i].Text = m_LMessage[i];
	}

	for (int i = 6; i < m_LCount; i++)
	{
		m_LStatus[i].Size = CVector2(40, 30);
		m_LStatus[i].Pos = CVector2(220 + (i - 6) * 60, 600);
	}

	m_MStatus.LabelCount = m_LCount;
}

void CEditMenuObject::InitializeTextBox() {
	for (int i = 0; i < m_LCount; i++)
	{
		m_TStatus[i].Size = CVector2(160, 30);
		m_TStatus[i].Pos = CVector2(220, i * 80 + 160);
	}

	for (int i = 6; i < m_LCount; i++)
	{
		m_TStatus[i].Size = CVector2(40, 30);
		m_TStatus[i].Pos = CVector2(220 + (i - 6) * 60, 640);
	}

	m_MStatus.TextBoxCount = m_LCount;
}