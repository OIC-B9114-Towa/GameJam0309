#include "NoTextBox.h"

CNoTextBox::CNoTextBox() :
	m_TStatus(),
	m_SelectNo(0),
	m_MaxNo(0),
	m_Count(0),
	m_bSelect(),
	m_bIsEnable(false) {
	memset(m_bSelect, false, 2);
}

CNoTextBox::~CNoTextBox() {

}

void CNoTextBox::Initialize(TextBoxStatus tstatus) {
	m_TStatus = tstatus;
	m_MaxNo = m_TStatus.Text.size();
	m_SelectNo = m_TStatus.Text.size();
}

void CNoTextBox::ChangeText(std::string tex) {
	m_TStatus.Text = tex;
	m_MaxNo = m_TStatus.Text.size();
	m_SelectNo = m_TStatus.Text.size();
}

void CNoTextBox::Update(bool select) {
	m_bSelect[1] = m_bSelect[0];
	m_bSelect[0] = select;
	if (m_Count > 0)
	{
		m_Count--;
	}
	else
	{
		m_Count = 90;
	}

	/*if (m_bSelect[0] && !m_bSelect[1])
	{
		m_bIsEnable = true;
		CImeProc::GetImeInput()->SetEnable(TRUE);
	}
	else if (!m_bSelect[0] && m_bSelect[1])
	{
		m_bIsEnable = false;
		CImeProc::GetImeInput()->SetEnable(FALSE);
	}*/
	if (m_bSelect[0] == false && m_bSelect[1] == false)
	{
		if (!m_TStatus.bOnlyNo) { return; }
		if (m_TStatus.Text == "")
		{
			m_TStatus.Text = std::to_string(max(0, m_TStatus.Min));
			m_MaxNo = GetDigit();
			m_SelectNo = m_MaxNo;
		}
		if (GetNo() > m_TStatus.Max)
		{
			m_TStatus.Text = std::to_string(m_TStatus.Max);
			m_MaxNo = GetDigit();
			m_SelectNo = m_MaxNo;
		}
		else if (GetNo() < m_TStatus.Min)
		{
			m_TStatus.Text = std::to_string(m_TStatus.Min);
			m_MaxNo = GetDigit();
			m_SelectNo = m_MaxNo;
		}
	}
}

void CNoTextBox::Input() {
	if (m_TStatus.bOnlyNo)
	{
		InputNo();
	}
	else
	{
		InputLetter();
	}
}

void CNoTextBox::InputNo() {
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		m_SelectNo--;
		if (m_TStatus.Text.substr(0, 1) == "-")
		{
			if (m_SelectNo < 1)
			{
				m_SelectNo = 1;
			}
		}
		else
		{
			if (m_SelectNo < 0)
			{
				m_SelectNo = 0;
			}
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		m_SelectNo++;
		if (m_SelectNo > m_MaxNo)
		{
			m_SelectNo = m_MaxNo;
		}
	}
	std::string FHalf = m_TStatus.Text.substr(0, m_SelectNo);
	std::string LHalf = m_TStatus.Text.substr(m_SelectNo, m_MaxNo);

	if (g_pInput->IsKeyPush(MOFKEY_0))
	{
		m_TStatus.Text = FHalf + "0" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		m_TStatus.Text = FHalf + "1" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		m_TStatus.Text = FHalf + "2" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_3))
	{
		m_TStatus.Text = FHalf + "3" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		m_TStatus.Text = FHalf + "4" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_5))
	{
		m_TStatus.Text = FHalf + "5" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_6))
	{
		m_TStatus.Text = FHalf + "6" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_7))
	{
		m_TStatus.Text = FHalf + "7" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_8))
	{
		m_TStatus.Text = FHalf + "8" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_9))
	{
		m_TStatus.Text = FHalf + "9" + LHalf;
		m_SelectNo++;
		m_MaxNo++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_BACKSPACE))
	{
		if (m_SelectNo > 0)
		{
			m_TStatus.Text = FHalf.substr(0, FHalf.size() - 1) + LHalf;
			m_SelectNo--;
			m_MaxNo--;
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DELETE))
	{
		if (m_MaxNo > 0 && m_SelectNo < m_MaxNo)
		{
			m_TStatus.Text = FHalf + LHalf.substr(1, LHalf.size());
			m_MaxNo--;
		}
	}
	if (m_TStatus.bCanMinus)
	{
		if (g_pInput->IsKeyPush(MOFKEY_MINUS) || g_pInput->IsKeyPush(MOFKEY_NUMPADMINUS))
		{
			if (m_TStatus.Text.substr(0, 1) != "-")
			{
				m_TStatus.Text = "-" + m_TStatus.Text;
				m_SelectNo++;
				m_MaxNo++;
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_NUMPADPLUS))
		{
			if (m_TStatus.Text.substr(0, 1) == "-")
			{
				m_TStatus.Text = m_TStatus.Text.substr(1, m_MaxNo);
				m_SelectNo--;
				m_MaxNo--;
			}
		}
	}
	/*if (m_TStatus.Text.size() != 0)
	{
		if (atoi(m_TStatus.Text.c_str()) < m_TStatus.Min)
		{
			m_TStatus.Text = std::to_string(m_TStatus.Min);
			m_SelectNo = m_TStatus.Text.size();
			m_MaxNo = m_TStatus.Text.size();
		}
		else if (atoi(m_TStatus.Text.c_str()) > m_TStatus.Max)
		{
			m_TStatus.Text = std::to_string(m_TStatus.Max);
			m_SelectNo = m_TStatus.Text.size();
			m_MaxNo = m_TStatus.Text.size();
		}
	}*/
}

void CNoTextBox::InputLetter() {
	if (m_bIsEnable)
	{
		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			m_SelectNo -= (IsBIG(m_TStatus.Text, m_SelectNo)) ? 2 : 1;
			m_SelectNo = max(0, m_SelectNo);
		}
		else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			m_SelectNo += (IsBIG(m_TStatus.Text, m_SelectNo)) ? 2 : 1;
			m_SelectNo = min(m_SelectNo, m_TStatus.Text.length());
		}

		if (g_pInput->IsKeyPush(MOFKEY_BACKSPACE))
		{
			m_SelectNo = BackSpaceWord();
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DELETE))
		{
			m_SelectNo = DeleteWord();
		}
	}

	if (CImeProc::GetImeInput()->GetEnterString()->GetLength() > 0)
	{
		//•¶Žš‚Æ‚µ‚Ä’Ç‰Á
		std::string f;
		std::string l;
		f = m_TStatus.Text.substr(0, m_SelectNo);
		l = m_TStatus.Text.substr(m_SelectNo, m_TStatus.Text.length());
		f += CImeProc::GetImeInput()->GetEnterString()->GetString();
		m_TStatus.Text = f + l;
		m_SelectNo += CImeProc::GetImeInput()->GetEnterString()->GetLength();
		//’Ç‰Á‚·‚ê‚ÎƒŠƒZƒbƒg
		CImeProc::GetImeInput()->ResetEnterString();
	}
}

bool CNoTextBox::IsBIG(const std::string& st, int no) {
	bool BIG = false;
	for (int i = 0; i < no; i++)
	{
		if (IsDBCSLeadByte(st[i]))
		{
			BIG = true;
			i++;
		}
		else
		{
			BIG = false;
		}
	}
	return BIG;
}

int CNoTextBox::BackSpaceWord() {
	std::string f;
	std::string l;
	if (m_TStatus.Text.length() == 0 || m_SelectNo == 0)
	{
		return m_SelectNo;
	}
	if (IsBIG(m_TStatus.Text, m_SelectNo))
	{
		f = m_TStatus.Text.substr(0, m_SelectNo - 2);
		l = m_TStatus.Text.substr(m_SelectNo, m_TStatus.Text.length());
		m_SelectNo -= 2;
	}
	else
	{
		f = m_TStatus.Text.substr(0, m_SelectNo - 1);
		l = m_TStatus.Text.substr(m_SelectNo, m_TStatus.Text.length());
		m_SelectNo -= 1;
	}
	m_TStatus.Text = f + l;
	return m_SelectNo;
}

int CNoTextBox::DeleteWord() {
	std::string f;
	std::string l;
	if (m_TStatus.Text.length() == 0 || m_TStatus.Text.length() == m_SelectNo)
	{
		return m_SelectNo;
	}
	if (IsBIG(m_TStatus.Text, m_SelectNo + 1))
	{
		f = m_TStatus.Text.substr(0, m_SelectNo);
		l = m_TStatus.Text.substr(m_SelectNo + 2, m_TStatus.Text.length());
	}
	else
	{
		f = m_TStatus.Text.substr(0, m_SelectNo);
		l = m_TStatus.Text.substr(m_SelectNo + 1, m_TStatus.Text.length());
	}
	m_TStatus.Text = f + l;
	return m_SelectNo;
}

bool CNoTextBox::Collision(CVector2 pos) {
	return (m_TStatus.bClick) ? GetRect().CollisionPoint(pos) : false;
}

void CNoTextBox::Render(CVector2 pos) {
	if (m_TStatus.bClick)
	{
		CGraphicsUtilities::RenderFillRect(GetRect(), (m_bSelect[0]) ? m_TStatus.SelectSurfaceColor : m_TStatus.SurfaceColor);
		CGraphicsUtilities::RenderRect(GetRect(), (m_bSelect[0]) ? m_TStatus.SelectEdgeColor : m_TStatus.EdgeColor);
	}

	std::string text;
	text = m_TStatus.Text;


	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, text.c_str(), trec);

	float x = (m_TStatus.Pos.x + m_TStatus.Size.x / 2) - trec.GetWidth() / 2;
	float y = (m_TStatus.Pos.y + m_TStatus.Size.y / 2) - 21 / 2;


	CGraphicsUtilities::RenderString(x, y, m_TStatus.TextColor, text.c_str());

	if (m_bSelect[0] && m_Count > 35)
	{
		std::string line;
		line = text.substr(0, m_SelectNo);

		CRectangle lrec;
		CGraphicsUtilities::CalculateStringRect(0, 0, line.c_str(), lrec);
		CGraphicsUtilities::RenderLine(x + lrec.GetWidth(), y, x + lrec.GetWidth(), y + 23, MOF_ARGB(255, 0, 0, 0));
	}
}

void CNoTextBox::Release() {

}

int CNoTextBox::GetDigit() {
	int Disit = 0;
	int num = atoi(m_TStatus.Text.c_str());

	while (num != 0) {
		num /= 10;
		Disit++;
	}

	return Disit;
}