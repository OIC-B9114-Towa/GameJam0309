#pragma once
#include "SceneBase.h"

//色とかの設定最大値
#define FF 255
//項目の見えるようになる速度
#define MENU_ALPHASPEED 3

//選べる項目の列挙
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

	//どの項目を選択中か
	int m_selectMenu;

	int	m_logoAlpha;
	int m_menuAlpha[SELECTMENU_COUNT];
	int m_windowAlpha;

	char* m_fileBuffer;
	char* m_menuDesc[SELECTMENU_COUNT];
	char* m_menuName[SELECTMENU_COUNT] = { 
		"メインゲーム",
		"コレクション",
		" オプション ",
		"  お わ る  " };

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


