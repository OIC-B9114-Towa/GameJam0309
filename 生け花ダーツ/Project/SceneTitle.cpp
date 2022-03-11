#include "SceneTitle.h"

CSceneTitle::CSceneTitle() :
	m_titleLogo(),
	m_titleBack(),
	m_menuIcon(),
	m_menuFont(),
	m_menuBackColor{0,0,0},
	m_menuFrameColor{0,0,0},
	m_menuRect(0,0,0,0),
	m_selectMenu(0),
	m_logoAlpha(0),
	m_menuAlpha{0,0,0},
	m_windowAlpha(0),
	m_fileBuffer(NULL),
	m_menuDesc{NULL,NULL,NULL}
{

}

void CSceneTitle::LoadText()
{
	//テキストファイルを開く
	FILE* fp = fopen("Text\\MenuDescription.txt", "rt");
	if (fp == NULL)
	{
		return;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);  //fpの位置をファイルの終端へ
	long fSize = ftell(fp);  //ファイルの読み書き位置を取得、位置で容量を求める
	fseek(fp, 0, SEEK_SET);  //fpの位置をファイルの先頭へ
	//ファイルの容量文のメモリをmallocで動的に確保
	m_fileBuffer = (char*)malloc(fSize + 1);  //終端に\0を含めるため、+1
	//バッファにファイルを全て読み込む
	fSize = fread(m_fileBuffer, 1, fSize, fp);
	m_fileBuffer[fSize] = '\0';

	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		//最初の説明文のみ
		if(i == SELECTMENU_TOGAME)
			strtok(m_fileBuffer, "=");
		else
			strtok(NULL, "=");

		m_menuDesc[i] = strtok(NULL, ",");
	}

	//ファイルを閉じる
	fclose(fp);

}

void CSceneTitle::Initialize() {
	g_pGraphics->SetScreenSize(1024, 768);
	//テクスチャ読み込み
	m_titleLogo.Load("Texture\\TitleLogo.png");
	m_titleBack.Load("Texture\\TitleBack.png");

	m_menuIcon[SELECTMENU_TOGAME].Load("Texture\\MainGameIcon.png");
	m_menuIcon[SELECTMENU_TOCOLLECTION].Load("Texture\\CollectionIcon.png");
	m_menuIcon[SELECTMENU_TOOPTION].Load("Texture\\OptionIcon.png");
	m_menuIcon[SELECTMENU_QUIT].Load("Texture\\QuitIcon.png");

	//最初は[メインゲーム]に合わせる
	m_selectMenu = SELECTMENU_TOGAME;

	//アルファ値の初期化
	m_logoAlpha = 0;
	m_windowAlpha = 0;
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		m_menuAlpha[i] = 0;

		//説明文格納用・初期化
		m_menuDesc[i] = NULL;
	}

	m_fileBuffer = NULL;
	//テキストから読み込み
	LoadText();
	//フォント設定
	m_menuFont.Create(m_fontSize, "MS 明朝");
	
	//メニューの座標設定
	m_menuRect = CRectangle(m_initMenuRect);
	
	//メニューの色設定
	m_menuBackColor = { m_offMenuBackColor.red,m_offMenuBackColor.green, m_offMenuBackColor.blue };
	m_menuFrameColor = { m_offMenuFrameColor.red,m_offMenuFrameColor.green, m_offMenuFrameColor.blue };
}

//透明度の更新
void CSceneTitle::UpdateAlpha()
{
	if (m_logoAlpha < FF)
	{
		m_logoAlpha += m_logoAlphaSpeed;
		if (m_logoAlpha >= FF - 1)
			m_logoAlpha = FF;
	}
	if (m_windowAlpha < WINDOW_ALPHA_STOP_TIMING)
	{
		if (m_logoAlpha > WINDOW_ALPHA_START_TIMING)
			m_windowAlpha += m_windowAlphaSpeed;
	}
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_menuAlpha[i] < FF)
		{
			if ((i == SELECTMENU_TOGAME && m_logoAlpha >= WINDOW_ALPHA_START_TIMING) ||
				(i == SELECTMENU_TOCOLLECTION && m_menuAlpha[SELECTMENU_TOGAME] >= MENU_ALPHA_START_TIMING) ||
				(i == SELECTMENU_TOOPTION && m_menuAlpha[SELECTMENU_TOCOLLECTION] >= MENU_ALPHA_START_TIMING) ||
				(i == SELECTMENU_QUIT && m_menuAlpha[SELECTMENU_TOOPTION] >= MENU_ALPHA_START_TIMING))
			{
				m_menuAlpha[i] += m_menuAlphaSpeed;
			}
		}
	}
}

//メニュー選択の更新
void CSceneTitle::UpdateMenu()
{
	//矢印で項目の移動
	if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW) || g_pInput->IsKeyPush(MOFKEY_S))
	{
		//効果音：カーソル移動音

		if (m_selectMenu == SELECTMENU_COUNT - 1)
		{
			m_selectMenu = SELECTMENU_TOGAME;
		}
		else
		{
			m_selectMenu++;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_UPARROW) || g_pInput->IsKeyPush(MOFKEY_W))
	{
		//効果音：カーソル移動音

		if (m_selectMenu == SELECTMENU_TOGAME)
		{
			m_selectMenu = SELECTMENU_COUNT - 1;
		}
		else
		{
			m_selectMenu--;
		}
	}
}

//メニュー選んだとき、シーンの遷移更新
void CSceneTitle::UpdateTransition()
{
	//とりあえず [Space] で画面遷移
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		//ゲーム画面
		if (m_selectMenu == SELECTMENU_TOGAME)
		{
			m_NextScene = SCENETYPE_GAME;
		}
		//コレクション画面
		if (m_selectMenu == SELECTMENU_TOCOLLECTION)
		{
			m_NextScene = SCENETYPE_COLLECTION;
		}
		//オプション画面
		if (m_selectMenu == SELECTMENU_TOOPTION)
		{
			m_NextScene = SCENETYPE_OPTION;
		}
		//ゲームの終了
		if (m_selectMenu == SELECTMENU_QUIT)
		{
			//画面を閉じる
			PostQuitMessage(0);
			return;
		}

		//現在のシーンを閉じる
		m_bEnd = true;
	}
}

void CSceneTitle::Update() {

	//透明度の更新
	UpdateAlpha();

	//メニューのアルファ処理が終わるまで操作不可
	if (m_menuAlpha[SELECTMENU_COUNT - 1] < FF)
	{
		return;
	}

	//メニュー選んだとき、シーンの遷移更新
	UpdateTransition();
	//選択項目の更新
	UpdateMenu();
}

void CSceneTitle::UpdateDebug() {
}

//選択項目の描画
void CSceneTitle::RenderMenu()
{
	//選択項目
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{	
		if (m_selectMenu == i && m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
		{
			m_menuRect.Left = m_initMenuRect.Left - ON_CURSOR_SHIFT;
			m_menuRect.Right = m_initMenuRect.Right - ON_CURSOR_SHIFT;
			m_menuBackColor = { m_onMenuBackColor.red,m_onMenuBackColor.green, m_onMenuBackColor.blue };
			m_menuFrameColor = { m_onMenuFrameColor.red,m_onMenuFrameColor.green, m_onMenuFrameColor.blue };
		}
		else
		{
			m_menuRect.Left = m_initMenuRect.Left;
			m_menuRect.Right = m_initMenuRect.Right;
			m_menuBackColor = { m_offMenuBackColor.red,m_offMenuBackColor.green, m_offMenuBackColor.blue };
			m_menuFrameColor = { m_offMenuFrameColor.red,m_offMenuFrameColor.green, m_offMenuFrameColor.blue };
		}

		CGraphicsUtilities::RenderFillRect(m_menuRect.Left, m_menuRect.Top + (i * MENU_INTERVAL), m_menuRect.Right, m_menuRect.Bottom + (i * MENU_INTERVAL),
			MOF_ARGB(m_menuAlpha[i], m_menuBackColor.red, m_menuBackColor.green, m_menuBackColor.blue));
		CGraphicsUtilities::RenderRect(m_menuRect.Left, m_menuRect.Top + (i * MENU_INTERVAL), m_menuRect.Right, m_menuRect.Bottom + (i * MENU_INTERVAL),
			MOF_ARGB(m_menuAlpha[i], m_menuFrameColor.red, m_menuFrameColor.green, m_menuFrameColor.blue));

		m_menuFont.RenderString(m_menuRect.Left + ADJUST_MENU_TEXT, m_menuRect.Top + (i * MENU_INTERVAL) + ADJUST_MENU_TEXT,
			MOF_ARGB(m_menuAlpha[i], m_menuTextColor.red, m_menuTextColor.green, m_menuTextColor.blue), m_menuName[i]);
	}
}

//アイコンの描画
void CSceneTitle::RenderIcon()
{
	CGraphicsUtilities::RenderFillRect(m_iconWindowRect, MOF_ARGB(m_windowAlpha, m_iconWindowBackColor.red, m_iconWindowBackColor.green, m_iconWindowBackColor.blue));
	CGraphicsUtilities::RenderRect(m_iconWindowRect, MOF_ARGB(m_windowAlpha, m_iconWindowFrameColor.red, m_iconWindowFrameColor.green, m_iconWindowFrameColor.blue));
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
		{
			if (i == m_selectMenu)
				m_menuIcon[i].Render(m_iconPos.x, m_iconPos.y);
		}
	}
}

//説明
void CSceneTitle::RenderMenuDescription()
{
	CGraphicsUtilities::RenderFillRect(m_descWindowRect, MOF_ARGB(m_windowAlpha, m_descWindowBackColor.red, m_descWindowBackColor.green, m_descWindowBackColor.blue));
	CGraphicsUtilities::RenderRect(m_descWindowRect, MOF_ARGB(m_windowAlpha, m_descWindowFrameColor.red, m_descWindowFrameColor.green, m_descWindowFrameColor.blue));
	if (m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
	{
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, m_menuDesc[m_selectMenu]);
	}
}

void CSceneTitle::Render() {

	//背景
	m_titleBack.Render(0, 0);

	//選択項目
	RenderMenu();

	//ロゴ
	m_titleLogo.Render(m_logoPos.x,m_logoPos.y,MOF_ARGB(m_logoAlpha, FF, FF, FF));

	//アイコン
	RenderIcon();
	
	//説明
	RenderMenuDescription();
	
	//操作方法
	CGraphicsUtilities::RenderString(m_howToTextPos.x, m_howToTextPos.y, MOF_COLOR_BLACK, "[↑↓]で選択　[Space]で決定");
}

void CSceneTitle::RenderDebug() {
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "タイトル画面");
	int sw, sh; 
	sw = g_pGraphics->GetTargetWidth();
	sh = g_pGraphics->GetTargetHeight();
	CGraphicsUtilities::RenderString(0, 100, MOF_COLOR_BLACK, "SW:%d  SH:%d", sw, sh);
}

void CSceneTitle::Release() {
	//テクスチャの解放
	m_titleLogo.Release();
	m_titleBack.Release();
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		m_menuIcon[i].Release();
	}
	//フォントの解放
	m_menuFont.Release();
	//確保したファイルバッファを解放
	free(m_fileBuffer);
}