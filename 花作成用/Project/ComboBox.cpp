#include "ComboBox.h"

CComboBox::CComboBox() :
	m_CBStatus(),
	m_bSelect(false),
	m_Scroll(0) {
}

CComboBox::~CComboBox() {
}

void CComboBox::Initialize(const ComboBoxStatus& cbstatus) {
	m_CBStatus = cbstatus;
	m_CBStatus.VerticalWidth = (m_CBStatus.VerticalWidth == 0) ? m_CBStatus.Size.y : m_CBStatus.VerticalWidth;
}

void CComboBox::Update(bool select) {
	m_bSelect = select;
}

bool CComboBox::Collision(CVector2 pos) {
	if (m_bSelect)
	{
		float scroll = g_pInput->GetMouseWheelMove();
		if (scroll < 0)
		{
			m_Scroll = min(m_CBStatus.Text.size() - 1, m_Scroll + 1);
		}
		else if (scroll > 0)
		{
			m_Scroll = max(0, m_Scroll - 1);
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			if (GetRect().CollisionPoint(pos))
			{
				m_bSelect = false;
				return true;
			}
			for (int i = 0; i < m_CBStatus.Text.size(); i++)
			{
				if (GetRect(CVector2(0, (i + 1) * m_CBStatus.VerticalWidth)).CollisionPoint(pos))
				{
					m_CBStatus.SelectNo = i + m_Scroll;
					m_bSelect = false;
					return true;
				}
			}
		}

	}
	else
	{
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			if (GetRect().CollisionPoint(pos))
			{
				m_bSelect = true;
				return true;
			}
		}
	}
	return false;
}

void CComboBox::ChangeText(int i, std::string tex) {
	if (i < m_CBStatus.Text.size() && 0 < i)
		m_CBStatus.Text[i] = tex;
}

void CComboBox::AddText(std::string tex) {
	m_CBStatus.Text.push_back(tex);
}

void CComboBox::DeleteText(int i) {
	m_CBStatus.Text.erase(m_CBStatus.Text.begin() + i);
}

void CComboBox::Render(CVector2 pos) {
	CGraphicsUtilities::RenderFillRect(GetRect(pos), m_CBStatus.SurfaceColor);
	CGraphicsUtilities::RenderRect(GetRect(pos), m_CBStatus.EdgeColor);

	std::string text;
	if (m_CBStatus.Text.size() <= 0)
		text = "No Data";
	else
		text = m_CBStatus.Text[m_CBStatus.SelectNo];

	float x = 0;
	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, text.c_str(), trec);


	switch (m_CBStatus.Justified)
	{
	case 0:
		x = m_CBStatus.Pos.x + m_CBStatus.Size.x / 2 - trec.GetWidth() / 2;
		break;
	case 1:
		x = m_CBStatus.Pos.x;
		break;
	case 2:
		x = m_CBStatus.Pos.x + m_CBStatus.Size.x - trec.GetWidth();
		break;
	default:
		break;
	}

	float y = (m_CBStatus.Pos.y + m_CBStatus.Size.y / 2) - trec.GetHeight() / 2;
	CGraphicsUtilities::RenderString(x, y, m_CBStatus.TextColor, text.c_str());

	if (m_bSelect)
	{
		for (int i = 0; i < m_CBStatus.Text.size() - m_Scroll; i++)
		{
			CGraphicsUtilities::RenderFillRect(GetRect(pos + CVector2(0, (i + 1) * m_CBStatus.VerticalWidth)), m_CBStatus.ListSurfaceColor);
			CGraphicsUtilities::RenderRect(GetRect(pos + CVector2(0, (i + 1) * m_CBStatus.VerticalWidth)), m_CBStatus.EdgeColor);
			text = m_CBStatus.Text[i + m_Scroll];
			CGraphicsUtilities::CalculateStringRect(0, 0, text.c_str(), trec);
			switch (m_CBStatus.Justified)
			{
			case 0:
				x = m_CBStatus.Pos.x + m_CBStatus.Size.x / 2 - trec.GetWidth() / 2;
				break;
			case 1:
				x = m_CBStatus.Pos.x;
				break;
			case 2:
				x = m_CBStatus.Pos.x + m_CBStatus.Size.x - trec.GetWidth();
				break;
			default:
				break;
			}
			CGraphicsUtilities::RenderString(x, y + (i + 1) * m_CBStatus.VerticalWidth, m_CBStatus.TextColor, text.c_str());
		}
	}
}

void CComboBox::Release() {

}