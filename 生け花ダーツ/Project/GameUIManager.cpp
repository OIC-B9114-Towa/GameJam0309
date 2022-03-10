#include "GameUIManager.h"
CGameUIManager::CGameUIManager() :
	gScoreBackTexture(),
	gWindIconTexture(),
	gFlowerIconBackTexture(),
	gFlowerIconTexture(),
	gThrowResultBackTexture(),
	gPauseBack(),
	gPauseButtonBack(),
	gPauseButtonBack_Select(),
	gBlackCurtainAlpha(255)
{}

CGameUIManager::~CGameUIManager() {
}

void CGameUIManager::Initialize() {
	//�摜�̓ǂݍ���
	gScoreBackTexture.Load("ScoreBack.png");
	gWindIconTexture.Load("WindIcon.png");
	gFlowerIconBackTexture.Load("FlowerIconBack.png");

	gFlowerIconTexture[0].Load("Flower_Blue.png");
	gFlowerIconTexture[1].Load("Flower_Red.png");
	gFlowerIconTexture[2].Load("Flower_Green.png");

	gThrowResultBackTexture.Load("");

	gPauseBack.Load("");
	gPauseButtonBack.Load("");
	gPauseButtonBack_Select.Load("");

	//�Ö��A���t�@�l�̏�����
	gBlackCurtainAlpha = 255;
}
bool CGameUIManager::GameStartAnim() {
	gBlackCurtainAlpha--;
	//�Ö����オ�肫���Ă�����I����ʒm����
	if (gBlackCurtainAlpha <= 0)
	{
		gBlackCurtainAlpha = 0;
		return true;
	}
	return false;
}

void CGameUIManager::UpdateUI() {

}
void CGameUIManager::RenderUI(int fcount, int fmaxcount, CInGameData::Result *result) {
	int ScreenWidth = g_pGraphics->GetTargetWidth();
	int ScreenHeight = g_pGraphics->GetTargetHeight();

	//�X�R�A�A���A�Ԃ̕`��
	gScoreBackTexture.Render(10, 10);
	CGraphicsUtilities::RenderString(40, 40, "Score : %d", result->score);
	gWindIconTexture.Render(10, 150);
	gFlowerIconBackTexture.Render(ScreenWidth - gFlowerIconBackTexture.GetWidth() - 10, ScreenHeight - gFlowerIconBackTexture.GetHeight() - 10);
	for (int i = fcount; i < fmaxcount; i++)
	{
		if (i == fcount)
		{
			gFlowerIconTexture[result->FlowerColor[i]].Render(ScreenWidth - 150, ScreenHeight - 150);
		}
		else
		{
			gFlowerIconTexture[result->FlowerColor[i]].Render(ScreenWidth - 150 - ((i - fcount) * 200), ScreenHeight - 150);
		}
	}
	//�Ö��̕`��
	CGraphicsUtilities::RenderRect(0, 0, ScreenWidth, ScreenHeight, MOF_ARGB(0, 0, 0, gBlackCurtainAlpha));
}
void CGameUIManager::ReleaseUI() {

}