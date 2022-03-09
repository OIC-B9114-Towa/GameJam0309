#pragma once
#include <Mof.h>

typedef struct tag_ComboBoxStatus {
	CVector2					Pos;
	CVector2					Size;
	std::vector<std::string>	Text;
	int							SelectNo;
	int							Justified;
	float						VerticalWidth;
	MofU32						TextColor;
	MofU32						SurfaceColor;
	MofU32						ListSurfaceColor;
	MofU32						EdgeColor;

	tag_ComboBoxStatus() :
		Pos(0, 0),
		Size(0, 0),
		Text(),
		SelectNo(0),
		Justified(0),
		VerticalWidth(0),
		TextColor(MOF_XRGB(0, 0, 0)),
		SurfaceColor(MOF_XRGB(255, 255, 255)),
		ListSurfaceColor(MOF_XRGB(200, 200, 200)),
		EdgeColor(MOF_XRGB(0, 0, 0)) {
	}
}ComboBoxStatus;

class CComboBox
{
private:
	ComboBoxStatus	m_CBStatus;
	bool			m_bSelect;
	int				m_Scroll;

public:
	CComboBox();
	~CComboBox();

	void Initialize(const ComboBoxStatus& cbstatus);
	void Update(bool select);
	bool Collision(CVector2 pos);
	void ChangeText(int i, std::string tex);
	void AddText(std::string tex);
	void DeleteText(int i);
	void Render(CVector2 pos = CVector2(0, 0));
	void Release();
	bool IsSelect() { return m_bSelect; }
	ComboBoxStatus GetComboBoxStatus() { return m_CBStatus; }
	CRectangle GetRect(CVector2 pos = CVector2(0, 0)) {
		return CRectangle(m_CBStatus.Pos.x + pos.x, m_CBStatus.Pos.y + pos.y, m_CBStatus.Pos.x + m_CBStatus.Size.x + pos.x, m_CBStatus.Pos.y + m_CBStatus.Size.y + pos.y);
	}
	int GetSelectNo() { return m_CBStatus.SelectNo; }
};

