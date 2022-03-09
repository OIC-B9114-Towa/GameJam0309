#pragma once
#include <Mof.h>

typedef struct tag_TextBoxStatus {
	bool			bOnlyNo;
	int				Min;
	int				Max;
	bool			bCanMinus;
	CVector2		Pos;
	CVector2		Size;
	bool			bClick;
	std::string		Text;
	MofU32			TextColor;
	MofU32			SurfaceColor;
	MofU32			EdgeColor;
	MofU32			SelectSurfaceColor;
	MofU32			SelectEdgeColor;

	tag_TextBoxStatus() {
		bOnlyNo = true;
		Min = -100000;
		Max = 100000;
		Pos = CVector2(0, 0);
		Size = CVector2(0, 0);
		Text = "";
		bClick = true;
		bCanMinus = false;
		TextColor = MOF_ARGB(255, 0, 0, 0);
		SurfaceColor = MOF_ARGB(255, 255, 255, 255);
		EdgeColor = MOF_ARGB(255, 0, 0, 0);
		SelectSurfaceColor = MOF_ARGB(255, 255, 255, 255);
		SelectEdgeColor = MOF_ARGB(255, 255, 50, 50);
	}
}TextBoxStatus;

class CNoTextBox
{
private:
	TextBoxStatus	m_TStatus;
	bool			m_bSelect[2];
	int				m_MaxNo;
	int				m_SelectNo;
	int				m_Count;

	bool			m_bIsEnable;

	void InputNo();
	void InputLetter();

	bool IsBIG(const std::string& st, int no);
	int BackSpaceWord();
	int DeleteWord();

	CRectangle GetRect(CVector2 pos = CVector2(0, 0)) {
		return CRectangle(m_TStatus.Pos.x + pos.x, m_TStatus.Pos.y + pos.y, m_TStatus.Pos.x + m_TStatus.Size.x + pos.x, m_TStatus.Pos.y + m_TStatus.Size.y + pos.y);
	}
public:
	CNoTextBox();
	~CNoTextBox();

	void Initialize(TextBoxStatus tstatus);
	void ChangeText(std::string tex);
	void Update(bool select);
	void Input();
	bool Collision(CVector2 pos);
	void Render(CVector2 pos = CVector2(0, 0));
	void Release();
	std::string GetText() { return m_TStatus.Text; }
	TextBoxStatus GetTextBoxStatus() { return m_TStatus; }
	int GetNo() { return atoi(m_TStatus.Text.c_str()); }
	int GetDigit();
};

