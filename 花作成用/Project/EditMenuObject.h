#pragma once
#include "EditSubMenuObject.h"

class CEditMenuObject : public CMenu
{
private:
	CEditSubMenuObject m_SubMenu;

	static const int	m_BCount = 3;
	ButtonStatus m_BStatus[m_BCount];
	std::string m_BMessage[m_BCount] = { "パーツ追加","透明切り替え","保存" };

	static const int	m_LCount = 9;
	LabelStatus m_LStatus[m_LCount];
	TextBoxStatus m_TStatus[m_LCount];
	std::string m_LMessage[m_LCount] = { "x座標","y座標", "z座標","x倍率","y倍率", "z倍率", "R" , "G" , "B" };


	void InitializeButton();
	void InitializeLabel();
	void InitializeTextBox();
public:
	void Initialize();
};

