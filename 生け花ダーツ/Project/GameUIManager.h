#pragma once
#include <Mof.h>
#include "SceneBase.h"
#include "InGameData.h"

class CGameUIManager
{
private:
	CTexture	gScoreBackTexture;					//スコアバックボード
	CTexture	gWindIconTexture;					//風のアイコン
	CTexture	gFlowerIconBackTexture;				//花のアイコンバックボード
	CTexture*	gFlowerIconTexture;					//花のアイコン

	CTexture	gThrowResultBackTexture;			//スコアテキストバックボード

	CTexture	gPauseBack;							//ポーズ画面背景
	CTexture	gPauseButtonBack;					//ポーズ画面ボタン背景
	CTexture	gPauseButtonBack_Select;			//ポーズ画面ボタン背景（選択時）

	int			gBlackCurtainAlpha;					//暗幕アルファ値

public:

	CGameUIManager();
	~CGameUIManager();
	void Initialize();
	bool GameStartAnim();
	void UpdateUI();
	void RenderUI(int fcount, int fmaxcount, CInGameData::Result *result);
	void ReleaseUI();
};

