#pragma once
#include "SceneBase.h"

//色とかの設定最大値
#define FF 255
//カーソルを合わせているとき左に飛び出す長さ
#define ON_CURSOR_SHIFT 10
//メニュー内の文字位置調整
#define ADJUST_MENU_TEXT 5
//メニューの間隔
#define MENU_INTERVAL 60
//透明度更新タイミング
#define WINDOW_ALPHA_START_TIMING 100
#define MENU_ALPHA_START_TIMING 60
//枠の透明度止めるタイミング
#define WINDOW_ALPHA_STOP_TIMING 200

//選べる項目の列挙
enum SelectMenu
{
	SELECTMENU_TOGAME,
	SELECTMENU_TOCOLLECTION,
	SELECTMENU_TOOPTION,
	SELECTMENU_QUIT,

	SELECTMENU_COUNT,
};

//3色定義用
struct RGB_Color
{
	int red;
	int green;
	int blue;
};

class CSceneTitle : public CSceneBase
{
private:
	CTexture m_titleLogo;
	CTexture m_titleBack;
	CTexture m_menuIcon[SELECTMENU_COUNT];

	CFont m_menuFont;
	//フォントサイズ
	const int m_fontSize = 40;

	//色
	//説明枠
	const RGB_Color m_descWindowBackColor = { 200,200,255 };
	const RGB_Color m_descWindowFrameColor = { 0,100,255 };
	//アイコン枠
	const RGB_Color m_iconWindowBackColor = { 200,200,210 };
	const RGB_Color m_iconWindowFrameColor = { 0,100,255 };
	//選ばれている状態のメニュー
	const RGB_Color m_onMenuBackColor = { 255,180,100 };
	const RGB_Color m_onMenuFrameColor = { 0,0,0 };
	//選ばれていない状態のメニュー
	const RGB_Color m_offMenuBackColor = { 255,255,150 };
	const RGB_Color m_offMenuFrameColor = { 100,100,100 };
	//メニュー
	RGB_Color m_menuBackColor;
	RGB_Color m_menuFrameColor;
	//メニュー内文字
	const RGB_Color m_menuTextColor = { 0, 0, 0 };

	//描画位置
	//説明枠
	const CRectangle m_descWindowRect = CRectangle(500, 470, 800, 540);
	//アイコン枠
	const CRectangle m_iconWindowRect = CRectangle(490, 320, 810, 550);
	//メニュー
	CRectangle m_menuRect;
	const CRectangle m_initMenuRect = CRectangle(210, 320, 440, 370);
	//ロゴ
	const CVector2 m_logoPos = CVector2(110, 70);
	//アイコン
	const CVector2 m_iconPos = CVector2(525, 330);
	//説明
	const CVector2 m_descPos = CVector2(510, 480);
	//操作方法
	const CVector2 m_howToTextPos = CVector2(320, 580);

	//どの項目を選択中か
	int m_selectMenu;

	//透明度
	//ロゴ
	int	m_logoAlpha;
	const int m_logoAlphaSpeed = 2;
	//メニュー
	int m_menuAlpha[SELECTMENU_COUNT];
	const int m_menuAlphaSpeed = 3;
	//枠
	int m_windowAlpha;
	const int m_windowAlphaSpeed = 2;

	//テキスト読み込み用
	char* m_fileBuffer;
	char* m_menuDesc[SELECTMENU_COUNT];

	//メニュー内文字
	const char* m_menuName[SELECTMENU_COUNT] = { 
		"メインゲーム",
		" コレクション",
		"  オプション ",
		"    おわる   " };

public:
	CSceneTitle();
	void LoadText();
	void Initialize(void);
	void UpdateAlpha();
	void UpdateMenu();
	void UpdateTransition();
	void Update(void);
	void UpdateDebug(void);
	void RenderMenu();
	void RenderIcon();
	void RenderMenuDescription();
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};


