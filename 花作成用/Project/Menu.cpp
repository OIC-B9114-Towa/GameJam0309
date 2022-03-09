#include "Menu.h"

CMenu::CMenu() :
	m_MStatus(),
	m_pSubMenu(),
	m_pLabel(),
	m_pButton(),
	m_pNoTextBox(),
	m_StartPos(0, 0),
	m_EndPos(0, 0),
	m_Scroll(0, 0) {

}

CMenu::~CMenu() {

}

void CMenu::Initialize(MenuStatus ms, CMenu* submenu, LabelStatus* ls, ButtonStatus* bs, TextBoxStatus* ts, ComboBoxStatus* cbs) {
	m_MStatus = ms;
	m_StartPos = CVector2(0, 0);
	m_EndPos = CVector2(0, 0);
	switch (m_MStatus.Type)
	{
	case 0:
		// 中央
		m_MStatus.Pos.x = (g_pGraphics->GetTargetWidth() - m_MStatus.Size.x) / 2;
		m_MStatus.Pos.y = (g_pGraphics->GetTargetHeight() - m_MStatus.Size.y) / 2;
		break;
	case 1:
		// 左上
		m_MStatus.Pos.x = m_MStatus.Pos.x;
		m_MStatus.Pos.y = m_MStatus.Pos.y;
		break;
	case 2:
		// 右上
		m_MStatus.Pos.x = g_pGraphics->GetTargetWidth() - m_MStatus.Size.x - m_MStatus.Pos.x;
		m_MStatus.Pos.y = m_MStatus.Pos.y;
		break;
	case 3:
		m_MStatus.Pos.x = m_MStatus.Pos.x;
		m_MStatus.Pos.y = g_pGraphics->GetTargetHeight() - m_MStatus.Size.y - m_MStatus.Pos.y;
		// 左下
		break;
	case 4:
		// 右下
		m_MStatus.Pos.x = g_pGraphics->GetTargetWidth() - m_MStatus.Size.x - m_MStatus.Pos.x;
		m_MStatus.Pos.y = g_pGraphics->GetTargetHeight() - m_MStatus.Size.y - m_MStatus.Pos.y;
		break;
	default:
		break;
	}
	if (m_MStatus.SubMenuCount <= 0 && m_pSubMenu.size() > 0)
	{
		m_pSubMenu.clear();
	}
	if (m_MStatus.SubMenuCount > 0 && submenu)
	{
		m_pSubMenu.clear();
		for (int i = 0; i < m_MStatus.SubMenuCount; i++)
		{
			m_pSubMenu.push_back(&submenu[i]);
			m_StartPos.x = min(m_StartPos.x, m_pSubMenu[i]->GetMenuStatus().Pos.x - ms.EdgeSpaceSize - ms.EdgeLineSize);
			m_StartPos.y = min(m_StartPos.y, m_pSubMenu[i]->GetMenuStatus().Pos.y - ms.EdgeSpaceSize - ms.EdgeLineSize);
			m_EndPos.x = max(m_EndPos.x, m_pSubMenu[i]->GetMenuStatus().Pos.x + m_pSubMenu[i]->GetMenuStatus().Size.x + ms.EdgeSpaceSize + ms.EdgeLineSize);
			m_EndPos.y = max(m_EndPos.y, m_pSubMenu[i]->GetMenuStatus().Pos.y + m_pSubMenu[i]->GetMenuStatus().Size.y + ms.EdgeSpaceSize + ms.EdgeLineSize);
		}
	}
	if (m_MStatus.LabelCount <= 0 && m_pLabel.size() > 0)
	{
		m_pLabel.clear();
	}
	if (m_MStatus.LabelCount > 0 && ls)
	{
		m_pLabel.clear();
		for (int i = 0; i < m_MStatus.LabelCount; i++)
		{
			m_pLabel.push_back(CLabel());
			m_StartPos.x = min(m_StartPos.x, ls[i].Pos.x - ms.EdgeSpaceSize - ms.EdgeLineSize);
			m_StartPos.y = min(m_StartPos.y, ls[i].Pos.y - ms.EdgeSpaceSize - ms.EdgeLineSize);
			m_EndPos.x = max(m_EndPos.x, ls[i].Pos.x + ls[i].Size.x + ms.EdgeSpaceSize + ms.EdgeLineSize);
			m_EndPos.y = max(m_EndPos.y, ls[i].Pos.y + ls[i].Size.y + ms.EdgeSpaceSize + ms.EdgeLineSize);
			LabelStatus lstatus = ls[i];
			//lstatus.Pos += m_MStatus.Pos;
			m_pLabel[i].Initialize(lstatus);
		}
	}
	if (m_MStatus.ButtonCount <= 0 && m_pButton.size() > 0)
	{
		m_pButton.clear();
	}
	if (m_MStatus.ButtonCount > 0 && bs)
	{
		m_pButton.clear();
		for (int i = 0; i < m_MStatus.ButtonCount; i++)
		{
			m_pButton.push_back(CButton());
			m_StartPos.x = min(m_StartPos.x, bs[i].Pos.x - ms.EdgeSpaceSize);
			m_StartPos.y = min(m_StartPos.y, bs[i].Pos.y - ms.EdgeSpaceSize);
			m_EndPos.x = max(m_EndPos.x, bs[i].Pos.x + bs[i].Size.x + ms.EdgeSpaceSize + ms.EdgeLineSize);
			m_EndPos.y = max(m_EndPos.y, bs[i].Pos.y + bs[i].Size.y + ms.EdgeSpaceSize + ms.EdgeLineSize);
			ButtonStatus bstatus = bs[i];
			//bstatus.Pos += m_MStatus.Pos;
			m_pButton[i].Initialize(bstatus);
		}
	}
	if (m_MStatus.TextBoxCount <= 0 && m_pNoTextBox.size() > 0)
	{
		m_pNoTextBox.clear();
	}
	if (m_MStatus.TextBoxCount > 0 && ts)
	{
		m_pNoTextBox.clear();
		for (int i = 0; i < m_MStatus.TextBoxCount; i++)
		{
			m_pNoTextBox.push_back(CNoTextBox());
			m_StartPos.x = min(m_StartPos.x, ts[i].Pos.x - ms.EdgeSpaceSize);
			m_StartPos.y = min(m_StartPos.y, ts[i].Pos.y - ms.EdgeSpaceSize);
			m_EndPos.x = max(m_EndPos.x, ts[i].Pos.x + ts[i].Size.x + ms.EdgeSpaceSize + ms.EdgeLineSize);
			m_EndPos.y = max(m_EndPos.y, ts[i].Pos.y + ts[i].Size.y + ms.EdgeSpaceSize + ms.EdgeLineSize);
			TextBoxStatus tstatus = ts[i];
			//tstatus.Pos += m_MStatus.Pos;
			m_pNoTextBox[i].Initialize(tstatus);
		}
	}
	if (m_MStatus.ComboBoxCount <= 0 && m_pComboBox.size() > 0)
	{
		m_pComboBox.clear();
	}
	if (m_MStatus.ComboBoxCount > 0 && cbs)
	{
		m_pComboBox.clear();
		for (int i = 0; i < m_MStatus.ComboBoxCount; i++)
		{
			m_pComboBox.push_back(CComboBox());
			m_StartPos.x = min(m_StartPos.x, cbs[i].Pos.x - ms.EdgeSpaceSize);
			m_StartPos.y = min(m_StartPos.y, cbs[i].Pos.y - ms.EdgeSpaceSize);
			m_EndPos.x = max(m_EndPos.x, cbs[i].Pos.x + cbs[i].Size.x + ms.EdgeSpaceSize + ms.EdgeLineSize);
			m_EndPos.y = max(m_EndPos.y, cbs[i].Pos.y + cbs[i].Size.y + ms.EdgeSpaceSize + ms.EdgeLineSize);
			ComboBoxStatus cbstatus = cbs[i];
			//gstatus.Pos += m_MStatus.Pos;
			m_pComboBox[i].Initialize(cbstatus);
		}
	}

	m_EndPos.x = max(m_EndPos.x, ms.Size.x);
	m_EndPos.y = max(m_EndPos.y, ms.Size.y);

	//m_Scroll.y = m_StartPos.y;
	m_RenderTarget.Release();
	if (m_RenderTarget.CreateTarget(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(),
		PIXELFORMAT_R8G8B8A8_UNORM, BUFFERACCESS_GPUREADWRITE))
	{
		MOF_PRINTLOG("TT");
	}
}

void CMenu::Update() {
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		m_pSubMenu[i]->Update();
	}
	for (int i = 0; i < m_pButton.size(); i++)
	{
		m_pButton[i].Update(false);
	}
	for (int i = 0; i < m_pNoTextBox.size(); i++)
	{
		m_pNoTextBox[i].Update(false);
	}

}

void CMenu::SelectButton(int sno) {
	int no = 0;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		no += m_pSubMenu[i]->GetRangeNo();
		if (no > sno)
		{
			m_pSubMenu[i]->SelectButton(no - sno - m_pSubMenu[i]->GetRangeNo());
			return;
		}
	}
	if (sno < no + m_pButton.size())
	{
		m_pButton[sno - no].Update(true);
	}
	else if (sno < no + m_pButton.size() + m_pNoTextBox.size())
	{
		m_pNoTextBox[sno - no - m_MStatus.ButtonCount].Update(true);
	}
}

void CMenu::InputText(int i) {
	int tno = ChangeTextBoxNo(i);
	if (m_pNoTextBox.size() > 0 && tno != -1)
	{
		m_pNoTextBox[tno].Input();
	}
}

int CMenu::Collision(CVector2 vec) {
	if (!GetEdgeRect().CollisionPoint(vec))
	{
		return -1;
	}
	if (m_MStatus.bScroll)
	{
		float hoil = g_pInput->GetMouseWheelMove();
		if (hoil != 0)
		{
			m_Scroll.y -= hoil * 0.2f;
		}
		if (m_Scroll.y < m_StartPos.y)
		{
			m_Scroll.y = m_StartPos.y;
		}
		else if (m_Scroll.y > m_EndPos.y - m_MStatus.Size.y)
		{
			m_Scroll.y = m_EndPos.y - m_MStatus.Size.y;
		}
	}
	vec -= m_MStatus.Pos - m_Scroll;
	int no = 0;
	int cnt = 0;
	// 選択済みのコンボボックスがあれば、ほかの当たり判定をしない
	for (int i = 0; i < m_pComboBox.size(); i++)
	{
		if (m_pComboBox[i].IsSelect())
		{
			if (m_pComboBox[i].Collision(vec) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				m_pComboBox[i].Update(false);
			}
			return -1;
		}
	}
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		no = m_pSubMenu[i]->Collision(vec);
		if (no != -1)
		{
			return cnt + no;
		}
		else
		{
			cnt += m_pSubMenu[i]->GetRangeNo();
		}
	}
	for (int i = 0; i < m_pButton.size(); i++)
	{
		if (m_pButton[i].Collision(vec))
		{
			m_pButton[i].Update(true);
			return cnt + i;
		}
	}
	for (int i = 0; i < m_pNoTextBox.size(); i++)
	{
		if (m_pNoTextBox[i].Collision(vec))
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				m_pNoTextBox[i].Update(true);
				return cnt + i + m_pButton.size();
			}
		}
	}
	for (int i = 0; i < m_pComboBox.size(); i++)
	{
		if (m_pComboBox[i].Collision(vec))
		{
			return cnt + i + m_pButton.size() + m_pNoTextBox.size();
		}
	}
	return -1;
}

void CMenu::UpdateButton(int i, std::string tex) {
	m_pButton[i].ChangeText(tex);
}

void CMenu::UpdateStatus(CMenu* submenu, LabelStatus* ls, ButtonStatus* bs, TextBoxStatus* ts, ComboBoxStatus* cbs) {
	if (submenu != NULL)
	{
		for (int i = 0; i < m_MStatus.SubMenuCount; i++)
		{
			m_pSubMenu[i] = &submenu[i];
		}
	}
	if (ls != NULL)
	{
		for (int i = 0; i < m_MStatus.ButtonCount; i++)
		{
			m_pLabel[i].Initialize(ls[i]);
		}
	}
	if (bs != NULL)
	{
		for (int i = 0; i < m_MStatus.ButtonCount; i++)
		{
			m_pButton[i].Initialize(bs[i]);
		}
	}
	if (ts != NULL)
	{
		for (int i = 0; i < m_MStatus.TextBoxCount; i++)
		{
			m_pNoTextBox[i].Initialize(ts[i]);
		}
	}
	if (cbs != NULL)
	{
		for (int i = 0; i < m_MStatus.ComboBoxCount; i++)
		{
			m_pComboBox[i].Initialize(cbs[i]);
		}
	}
}

void CMenu::UpdateTextBoxText(std::string* tex, int cnt, int start) {
	int end = min(m_pNoTextBox.size(), start + cnt);
	for (int i = 0; i < end; i++)
	{
		m_pNoTextBox[i + start].ChangeText(tex[i]);
	}
}

void CMenu::SetButton(ButtonStatus* bs, int cnt) {
	m_pButton.clear();
	m_MStatus.ButtonCount = cnt;
	for (int i = 0; i < cnt; i++)
	{
		m_pButton.push_back(CButton());
		m_StartPos.x = min(m_StartPos.x, bs[i].Pos.x - m_MStatus.EdgeSpaceSize);
		m_StartPos.y = min(m_StartPos.y, bs[i].Pos.y - m_MStatus.EdgeSpaceSize);
		m_EndPos.x = max(m_EndPos.x, bs[i].Pos.x + bs[i].Size.x + m_MStatus.EdgeSpaceSize + m_MStatus.EdgeLineSize);
		m_EndPos.y = max(m_EndPos.y, bs[i].Pos.y + bs[i].Size.y + m_MStatus.EdgeSpaceSize + m_MStatus.EdgeLineSize);
		ButtonStatus bstatus = bs[i];
		//bstatus.Pos += m_MStatus.Pos;
		m_pButton[i].Initialize(bstatus);
	}
}

// 構造を後で治す
void CMenu::Render() {
	MakeRender();
	RenderMakedRect();
	RenderGraphic();
}

void CMenu::MakeRender() {
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		m_pSubMenu[i]->MakeRender();
	}
	//画像を描画対象にする
	LPRenderTarget old = g_pGraphics->GetRenderTarget();
	LPDepthTarget oldd = g_pGraphics->GetDepthTarget();
	g_pGraphics->SetRenderTarget(m_RenderTarget.GetRenderTarget(), g_pGraphics->GetDepthTarget());
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	for (int i = 0; i < m_pLabel.size(); i++)
	{
		m_pLabel[i].Render(-m_Scroll);
	}
	for (int i = 0; i < m_pButton.size(); i++)
	{
		m_pButton[i].Render(-m_Scroll);
	}
	for (int i = 0; i < m_pNoTextBox.size(); i++)
	{
		m_pNoTextBox[i].Render(-m_Scroll);
	}
	for (int i = 0; i < m_pComboBox.size(); i++)
	{
		if (!m_pComboBox[i].IsSelect())
			m_pComboBox[i].Render(-m_Scroll);
	}
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		m_pSubMenu[i]->RenderMakedRect();
		m_pSubMenu[i]->RenderGraphic();
	}
	for (int i = 0; i < m_pComboBox.size(); i++)
	{
		if (m_pComboBox[i].IsSelect())
			m_pComboBox[i].Render(-m_Scroll);
	}
	//描画対象を元に戻す
	g_pGraphics->SetRenderTarget(old, oldd);
}

void CMenu::RenderMakedRect() {
	CGraphicsUtilities::RenderFillRect(GetRect(), m_MStatus.EdgeLineColor);
	CGraphicsUtilities::RenderFillRect(GetEdgeRect(), m_MStatus.SurfaceColor);
}

void CMenu::RenderGraphic() {
	CRectangle rec(m_MStatus.EdgeLineSize, m_MStatus.EdgeLineSize, m_MStatus.Size.x - m_MStatus.EdgeLineSize, m_MStatus.Size.y - m_MStatus.EdgeLineSize);
	m_RenderTarget.Render(m_MStatus.Pos.x + m_MStatus.EdgeLineSize, m_MStatus.Pos.y + m_MStatus.EdgeLineSize, rec);
}

void CMenu::Release() {
	m_RenderTarget.Release();
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		m_pSubMenu[i]->Release();
	}
}

int CMenu::GetTextBoxNo(int i) {
	return m_pNoTextBox[i].GetNo();
}

int CMenu::GetRangeNo() {
	int cnt = 0;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		cnt += m_pSubMenu[i]->GetRangeNo();
	}
	for (int i = 0; i < m_pButton.size(); i++)
	{
		if (m_pButton[i].GetButtonStatus().bClick)
		{
			cnt++;
		}
	}
	for (int i = 0; i < m_pNoTextBox.size(); i++)
	{
		cnt++;
	}
	for (int i = 0; i < m_pComboBox.size(); i++)
	{
		cnt++;
	}
	return cnt;
}

bool CMenu::IsSubMenuNo(int sno, int mno) {
	int no = sno;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		if (mno == i)
		{
			if (0 <= no && no < (int)m_pSubMenu[i]->GetRangeNo())
			{
				return true;
			}
		}
		else
		{
			no -= m_pSubMenu[i]->GetRangeNo();
		}
	}
	return false;
}

int CMenu::ChangeMainMenuNo(const int& sno) {
	int no = sno;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		no -= m_pSubMenu[i]->GetRangeNo();
	}
	if (0 <= no)
	{
		return no;
	}
	return -1;
}

int CMenu::ChangeSubMenuNo(const int& sno, const int& menuno) {
	int no = sno;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		if (i == menuno)
		{
			no = m_pSubMenu[menuno]->ChangeMainMenuNo(no);
			int rno = m_pSubMenu[menuno]->GetRangeNo();
			if (0 <= no && no < rno)
			{
				return no;
			}
		}
		no -= m_pSubMenu[i]->GetRangeNo();
	}
	return -1;
}

int CMenu::ChangeButtonNo(const int& sno) {
	int no = sno;
	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		no -= m_pSubMenu[i]->GetRangeNo();
	}
	if (0 <= no && no < (int)m_pButton.size())
	{
		return no;
	}
	return -1;
}

int CMenu::ChangeTextBoxNo(const int& sno) {
	int no = sno;

	for (int i = 0; i < m_pSubMenu.size(); i++)
	{
		no -= m_pSubMenu[i]->GetRangeNo();
	}
	for (int i = 0; i < m_pButton.size(); i++)
	{
		no--;
	}
	if (0 <= no && no < (int)m_pNoTextBox.size())
	{
		return no;
	}

	return -1;
}

bool CMenu::IsButton(int bno) {
	return  (ChangeButtonNo(bno) == -1) ? false : true;
}

bool CMenu::IsTextBox(int tno) {
	return  (ChangeTextBoxNo(tno) == -1) ? false : true;
}

std::string CMenu::GetTextBoxText(int i, int type) {
	std::string text = "";
	if (type == 0)
	{
		text = m_pNoTextBox[i].GetText();
	}
	return text;
}

void CMenu::UpdateButtonText(int i, std::string text) {
	if (i < 0 || i > m_pButton.size()) { return; }
	m_pButton[i].UpdateText(text);
}