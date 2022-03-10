#pragma once
#include "SceneBase.h"

//�F�Ƃ��̐ݒ�ő�l
#define FF 255
//���ڂ̌�����悤�ɂȂ鑬�x
#define MENU_ALPHASPEED 3

//�I�ׂ鍀�ڂ̗�
enum SelectMenu
{
	SELECTMENU_TOGAME,
	SELECTMENU_TOCOLLECTION,
	SELECTMENU_TOOPTION,
	SELECTMENU_QUIT,

	SELECTMENU_COUNT,
};

class CSceneTitle : public CSceneBase
{
private:
	CTexture m_titleLogo;
	CTexture m_titleBack;

	CFont m_menuFont;

	//�ǂ̍��ڂ�I�𒆂�
	int m_selectMenu;

	int	m_logoAlpha;
	int m_menuAlpha[SELECTMENU_COUNT];
	int m_windowAlpha;

	char* m_fileBuffer;
	char* m_menuDesc[SELECTMENU_COUNT];
	char* m_menuName[SELECTMENU_COUNT] = { 
		"���C���Q�[��",
		"�R���N�V����",
		" �I�v�V���� ",
		"  �� �� ��  " };

public:
	CSceneTitle();
	void LoadText();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};


