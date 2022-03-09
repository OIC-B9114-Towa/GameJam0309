#pragma once
#include <Mof.h>

typedef struct tag_ButtonStatus {
	CVector2		Pos;
	CVector2		Size;
	std::string		Text;
	bool			bClick;
	MofU32			TextColor;
	MofU32			NoClickTextColor;
	MofU32			SurfaceColor;
	MofU32			EdgeColor;
	MofU32			SelectSurfaceColor;
	MofU32			SelectEdgeColor;
	MofU32			NoClickSurfaceColor;
	MofU32			NoClickEdgeColor;

	tag_ButtonStatus() {
		Pos = CVector2(0, 0);
		Size = CVector2(0, 0);
		Text = "";
		bClick = true;
		TextColor = MOF_ARGB(255, 255, 255, 255);
		NoClickTextColor = MOF_ARGB(255, 200, 200, 200);
		SurfaceColor = MOF_ARGB(255, 0, 0, 0);
		EdgeColor = MOF_ARGB(255, 255, 255, 255);
		SelectSurfaceColor = MOF_ARGB(255, 0, 0, 0);
		SelectEdgeColor = MOF_ARGB(255, 255, 50, 50);
		NoClickSurfaceColor = MOF_ARGB(255, 0, 0, 0);
		NoClickEdgeColor = MOF_ARGB(255, 200, 200, 200);
	}
}ButtonStatus;

class CButton
{
private:
	ButtonStatus	m_BStatus;
	bool			m_bSelect;

public:
	CButton();
	~CButton();

	void Initialize(ButtonStatus bstatus);
	void ChangeText(std::string tex);
	void Update(bool select);
	bool Collision(CVector2 pos);
	void Render(CVector2 pos = CVector2(0, 0));
	void Release();
	ButtonStatus GetButtonStatus() { return m_BStatus; }
	CRectangle GetRect(CVector2 pos = CVector2(0, 0)) {
		return CRectangle(m_BStatus.Pos.x + pos.x, m_BStatus.Pos.y + pos.y, m_BStatus.Pos.x + m_BStatus.Size.x + pos.x, m_BStatus.Pos.y + m_BStatus.Size.y + pos.y);
	}

	void UpdateText(std::string text) { m_BStatus.Text = text; };
};