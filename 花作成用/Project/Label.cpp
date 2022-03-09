#include "Label.h"

CLabel::CLabel() :
	m_LStatus() {

}

CLabel::~CLabel() {

}

void CLabel::Initialize(const LabelStatus& lstatus) {
	m_LStatus = lstatus;
}

void CLabel::ChangeText(std::string tex) {
	m_LStatus.Text = tex;
}

void CLabel::Render(CVector2 pos) {
	if (m_LStatus.SurfaceColor != 0)
		CGraphicsUtilities::RenderFillRect(GetRect(), m_LStatus.SurfaceColor);
	if (m_LStatus.EdgeColor != 0)
		CGraphicsUtilities::RenderRect(GetRect(), m_LStatus.EdgeColor);

	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_LStatus.Text.c_str(), trec);

	float x = 0;
	float y = m_LStatus.Pos.y + m_LStatus.Size.y / 2 - trec.GetHeight() / 2;

	switch (m_LStatus.Justified)
	{
	case 0:
		x = m_LStatus.Pos.x + m_LStatus.Size.x / 2 - trec.GetWidth() / 2;
		break;
	case 1:
		x = m_LStatus.Pos.x;
		break;
	case 2:
		x = m_LStatus.Pos.x + m_LStatus.Size.x - trec.GetWidth();
		break;
	default:
		break;
	}

	CGraphicsUtilities::RenderString(x, y, m_LStatus.TextColor, m_LStatus.Text.c_str());
}

void CLabel::Release() {

}