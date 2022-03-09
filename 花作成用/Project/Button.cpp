#include "Button.h"

CButton::CButton() :
	m_BStatus(),
	m_bSelect(false) {

}

CButton::~CButton() {

}

void CButton::Initialize(ButtonStatus bstatus) {
	m_BStatus = bstatus;
}

void CButton::ChangeText(std::string tex) {
	m_BStatus.Text = tex;
}

void CButton::Update(bool select) {
	m_bSelect = select;
}

bool CButton::Collision(CVector2 pos) {
	return (m_BStatus.bClick) ? GetRect().CollisionPoint(pos) : false;
}

void CButton::Render(CVector2 pos) {
	if (m_BStatus.bClick)
	{
		if (m_bSelect)
		{
			CGraphicsUtilities::RenderFillRect(GetRect(pos), m_BStatus.SelectSurfaceColor);
			CGraphicsUtilities::RenderRect(GetRect(pos), m_BStatus.SelectEdgeColor);
		}
		else
		{
			CGraphicsUtilities::RenderFillRect(GetRect(pos), m_BStatus.SurfaceColor);
			CGraphicsUtilities::RenderRect(GetRect(pos), m_BStatus.EdgeColor);
		}
	}
	else
	{
		CGraphicsUtilities::RenderFillRect(GetRect(pos), m_BStatus.NoClickSurfaceColor);
		CGraphicsUtilities::RenderRect(GetRect(pos), m_BStatus.NoClickEdgeColor);
	}

	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_BStatus.Text.c_str(), trec);

	float x = (m_BStatus.Pos.x + m_BStatus.Size.x / 2) - trec.GetWidth() / 2;
	float y = (m_BStatus.Pos.y + m_BStatus.Size.y / 2) - trec.GetHeight() / 2;

	CGraphicsUtilities::RenderString(x + pos.x, y + pos.y, (m_BStatus.bClick) ? m_BStatus.TextColor : m_BStatus.NoClickTextColor, m_BStatus.Text.c_str());
}

void CButton::Release() {

}