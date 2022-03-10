#include "GameUIManager.h"
#include <algorithm>
#include <iostream>

CGameUIManager::CGameUIManager() :
	gScoreBackTexture(),
	gWindIconTexture(),
	gFlowerIconBackTexture(),
	gFlowerIconTexture(),
	gThrowResultBackTexture(),
	gPauseBack(),
	gPauseButtonBack(),
	gPauseButtonBack_Select(),
	gBlackCurtainAlpha(255),
	gCurrentMenuNum(0)
{}

CGameUIManager::~CGameUIManager() {
}

void CGameUIManager::Initialize() {
	//フォントの設定
	gScoreFont.Create(48, "MS ゴシック");
	gPauseMenuFont.Create(32, "MS ゴシック");
	
	//画像の読み込み
	gScoreBackTexture.Load("ScoreBack.png");
	gWindIconTexture.Load("WindIcon.png");
	gFlowerIconBackTexture.Load("FlowerIconBack.png");

	gFlowerIconTexture = new CTexture[FLOWERTYPE_COUNT];
	gFlowerIconTexture[0].Load("Flower_Blue.png");
	gFlowerIconTexture[1].Load("Flower_Red.png");
	gFlowerIconTexture[2].Load("Flower_Green.png");

	gThrowResultBackTexture.Load("");

	gPauseBack.Load("PauseMenuBack.png");
	gPauseButtonBack.Load("PauseButton.png");
	gPauseButtonBack_Select.Load("PauseButton_Select.png");

	//暗幕アルファ値の初期化
	gBlackCurtainAlpha = 255;
}
bool CGameUIManager::GameStartAnim() {
	gBlackCurtainAlpha -= 2;
	//暗幕が上がりきっていたら終了を通知する
	if (gBlackCurtainAlpha <= 0)
	{
		gBlackCurtainAlpha = 0;
		return true;
	}
	return false;
}

bool CGameUIManager::GameEndAnim() {
	gBlackCurtainAlpha += 2;
	//暗幕が上がりきっていたら終了を通知する
	if (gBlackCurtainAlpha > 255)
	{
		gBlackCurtainAlpha = 255;
		return true;
	}
	return false;
}

void CGameUIManager::UpdateUI() {

}

void CGameUIManager::UpdatePauseMenu() {
	if (g_pInput->IsKeyPush(MOFKEY_UPARROW))
	{
		gCurrentMenuNum++;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW))
	{
		gCurrentMenuNum--;
	}
	//値を0～2の範囲に調整
	gCurrentMenuNum = (std::max)(gCurrentMenuNum, 0);
	gCurrentMenuNum = (std::min)(gCurrentMenuNum, 2);

	//決定ボタン処理
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		gbPause = false;
	}
	//Escボタンでゲームに戻る
	else if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		gCurrentMenuNum = 0;
		gbPause = false;
	}
}
void CGameUIManager::RenderUI(int fcount, int fmaxcount, Result *result) {
	int ScreenWidth = g_pGraphics->GetTargetWidth();
	int ScreenHeight = g_pGraphics->GetTargetHeight();

	//スコア、風、花の描画
	gScoreBackTexture.Render(10, 10);
	char str[256];
	sprintf(str, "Score : %d", result->score);
	gScoreFont.RenderString(40, 40, str);
	gWindIconTexture.Render(10, 200);
	gFlowerIconBackTexture.RenderScale
	(ScreenWidth - gFlowerIconBackTexture.GetWidth() * 0.5f - 10, ScreenHeight - gFlowerIconBackTexture.GetHeight() * 0.5f - 10, 0.5f);
	for (int i = fcount; i < fmaxcount; i++)
	{
		if (i == fcount)
		{
			gFlowerIconTexture[result->FlowerColor[i]].RenderScale(ScreenWidth - 180, ScreenHeight - 180, 0.3f);
		}
		else
		{
			gFlowerIconTexture[result->FlowerColor[i]].RenderScale
			(ScreenWidth - 250 - ((i - fcount) * 120), ScreenHeight - 120, 0.25f);
		}
	}

	//ポーズ画面を開いているときのポーズメニュー描画
	if (gbPause)
	{

	}

	//暗幕の描画
	CGraphicsUtilities::RenderFillRect(0, 0, ScreenWidth, ScreenHeight, MOF_ARGB(gBlackCurtainAlpha, 0, 0, 0));
}
void CGameUIManager::ReleaseUI() {
	gScoreBackTexture.Release();
	gWindIconTexture.Release();
	gFlowerIconBackTexture.Release();
	gFlowerIconTexture[0].Release();
	gFlowerIconTexture[1].Release();
	gFlowerIconTexture[2].Release();
	gThrowResultBackTexture.Release();
	gPauseBack.Release();
	gPauseButtonBack.Release();
	gPauseButtonBack_Select.Release();
}