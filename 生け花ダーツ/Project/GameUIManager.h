#pragma once
#include <Mof.h>
#include "SceneBase.h"
#include "InGameData.h"

#define		RESULTSLIDESTARTPOSX			2000.0f
#define		RESULTSLIDEADDFORCEX			0.1f

class CGameUIManager
{
private:
	CFont		gScoreFont;
	CFont		gPauseMenuFont;

	CTexture	gScoreBackTexture;					//スコアバックボード
	CTexture	gWindIconTexture;					//風のアイコン
	CTexture	gFlowerIconBackTexture;				//花のアイコンバックボード
	CTexture*	gFlowerIconTexture;					//花のアイコン

	CTexture	gPauseBack;							//ポーズ画面背景
	CTexture	gPauseButtonBack;					//ポーズ画面ボタン背景
	CTexture	gPauseButtonBack_Select;			//ポーズ画面ボタン背景（選択時）

	int			gBlackCurtainAlpha;					//暗幕アルファ値
	float		gResultSlideOffsetX;				//リザルト用スライドオフセットX
	float		gResultSlideSpeedX;					//スライド速度

	bool		gbPause;							//ポーズメニューフラグ
	int			gCurrentMenuNum;					//現在の選択メニュー番号

public:

	CGameUIManager();
	~CGameUIManager();
	void Initialize();
	bool GameStartAnim();
	bool GameEndAnim();
	bool ResultSlideIn();
	void UpdateUI();
	void UpdatePauseMenu();
	void RenderUI(int fcount, int fmaxcount, Result *result);
	void ReleaseUI();

	void OpenPauseMenu() { gbPause = true; }
	int GetPauseMenuNum() { return gCurrentMenuNum; }
	bool IsOpenPauseMenu() { return gbPause; }
};

