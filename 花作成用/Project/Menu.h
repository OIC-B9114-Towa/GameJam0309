#pragma once
#include "Label.h"
#include "Button.h"
#include "NoTextBox.h"
#include "ComboBox.h"

typedef struct tag_MenuStatus {
	int			Type;
	CVector2	Pos;
	CVector2	Size;
	bool		bScroll;
	bool		bSelectVertical;
	int			SubMenuCount;
	int			LabelCount;
	int			ButtonCount;
	int			TextBoxCount;
	int			ComboBoxCount;
	int			EdgeLineSize;
	int			EdgeSpaceSize;
	MofU32			SurfaceColor;
	MofU32			EdgeLineColor;

	tag_MenuStatus() {
		Type = 0;
		Pos = CVector2(0, 0);
		Size = CVector2(0, 0);
		SubMenuCount = 0;
		bScroll = true;
		bSelectVertical = true;
		LabelCount = 0;
		ButtonCount = 0;
		TextBoxCount = 0;
		ComboBoxCount = 0;
		EdgeLineSize = 3;
		EdgeSpaceSize = 3;
		SurfaceColor = MOF_ARGB(255, 30, 30, 30);
		EdgeLineColor = MOF_ARGB(255, 50, 50, 200);
	}
}MenuStatus;

class CMenu
{
protected:
	MenuStatus				m_MStatus;
	std::vector<CMenu*>		m_pSubMenu;
	std::vector<CLabel>		m_pLabel;
	std::vector<CButton>	m_pButton;
	std::vector<CNoTextBox> m_pNoTextBox;
	std::vector<CComboBox>	m_pComboBox;

	CVector2 m_StartPos;
	CVector2 m_EndPos;
	CVector2 m_Scroll;
	CTexture m_RenderTarget;

	CTexture GetTerget() { return m_RenderTarget; }
	CRectangle GetEdgeRect()
	{
		return CRectangle(m_MStatus.Pos.x + m_MStatus.EdgeLineSize, m_MStatus.Pos.y + m_MStatus.EdgeLineSize, m_MStatus.Pos.x + m_MStatus.Size.x - m_MStatus.EdgeLineSize, m_MStatus.Pos.y + m_MStatus.Size.y - m_MStatus.EdgeLineSize);
	}
	void RenderMakedRect();
	void MakeRender();
	void RenderGraphic();

public:
	CMenu();
	~CMenu();

	void Initialize(MenuStatus ms, CMenu* submenu = NULL, LabelStatus* ls = NULL, ButtonStatus* bs = NULL, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL);
	void Initialize(MenuStatus ms, LabelStatus* ls, ButtonStatus* bs = NULL, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL) { Initialize(ms, NULL, ls, bs, ts, cbs); }
	void Initialize(MenuStatus ms, ButtonStatus* bs, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL) { Initialize(ms, NULL, NULL, bs, ts, cbs); }
	void Initialize(MenuStatus ms, TextBoxStatus* ts, ComboBoxStatus* cbs = NULL) { Initialize(ms, NULL, NULL, NULL, ts, cbs); }
	void Initialize(MenuStatus ms, ComboBoxStatus* cbs) { Initialize(ms, NULL, NULL, NULL, NULL, cbs); }
	void Update();
	void UpdateStatus(CMenu* submenu = NULL, LabelStatus* ls = NULL, ButtonStatus* bs = NULL, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL);
	void UpdateStatus(LabelStatus* ls, ButtonStatus* bs = NULL, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL) { UpdateStatus(NULL, ls, bs, ts, cbs); }
	void UpdateStatus(ButtonStatus* bs, TextBoxStatus* ts = NULL, ComboBoxStatus* cbs = NULL) { UpdateStatus(NULL, NULL, bs, ts, cbs); }
	void UpdateStatus(TextBoxStatus* ts, ComboBoxStatus* cbs = NULL) { UpdateStatus(NULL, NULL, NULL, ts, cbs); }
	void UpdateStatus(ComboBoxStatus* cbs) { UpdateStatus(NULL, NULL, NULL, NULL, cbs); }
	void UpdateTextBoxText(std::string* tex, int cnt, int strat = 0);
	void SetButton(ButtonStatus* bs, int cnt);
	void SelectButton(int i);
	void InputText(int i);
	int  Collision(CVector2 vec);
	void UpdateButton(int i, std::string tex);
	void Render();
	void Release();

	bool IsButton(int sno);
	bool IsTextBox(int sno);
	bool IsSubMenuNo(int sno, int mno);

	int ChangeMainMenuNo(const int& sno);
	int ChangeSubMenuNo(const int& sno, const int& menuno);
	int ChangeButtonNo(const int& sno);
	int ChangeTextBoxNo(const int& sno);

	CRectangle GetRect()
	{
		return CRectangle(m_MStatus.Pos.x, m_MStatus.Pos.y, m_MStatus.Pos.x + m_MStatus.Size.x, m_MStatus.Pos.y + m_MStatus.Size.y);
	}
	MenuStatus	GetMenuStatus() { return m_MStatus; }
	/*
	ButtonStatus* GetButtonStatus();
	TextBoxStatus* GetTextBoxStatus();
	GaugeStatus* GetGaugeStatus();
	*/
	int GetTextBoxNo(int i);
	int GetRangeNo();

	int GetButtonCount() { return (int)m_pButton.size(); }
	int GetTextBoxCount() { return (int)m_pNoTextBox.size(); }
	int GetSubMenuGetRange(int mno) { return m_pSubMenu[mno]->GetRangeNo(); }
	std::string GetTextBoxText(int i, int type = 0);

	void UpdateButtonText(int i, std::string text);

	ComboBoxStatus	GetComboBoxStatus(int i) { return m_pComboBox[i].GetComboBoxStatus(); }

	CMenu* GetSubMenu(int menuno) { return m_pSubMenu[menuno]; }
};

