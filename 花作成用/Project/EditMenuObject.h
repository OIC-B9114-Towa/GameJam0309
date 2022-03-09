#pragma once
#include "EditSubMenuObject.h"

class CEditMenuObject : public CMenu
{
private:
	CEditSubMenuObject m_SubMenu;

	static const int	m_BCount = 3;
	ButtonStatus m_BStatus[m_BCount];
	std::string m_BMessage[m_BCount] = { "�p�[�c�ǉ�","�����؂�ւ�","�ۑ�" };

	static const int	m_LCount = 9;
	LabelStatus m_LStatus[m_LCount];
	TextBoxStatus m_TStatus[m_LCount];
	std::string m_LMessage[m_LCount] = { "x���W","y���W", "z���W","x�{��","y�{��", "z�{��", "R" , "G" , "B" };


	void InitializeButton();
	void InitializeLabel();
	void InitializeTextBox();
public:
	void Initialize();
};

