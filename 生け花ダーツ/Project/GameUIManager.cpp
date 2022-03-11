#include "GameUIManager.h"
#include <algorithm>
#include <iostream>

CGameUIManager::CGameUIManager() :
	gScoreBackTexture(),
	gWindIconTexture(),
	gFlowerIconBackTexture(),
	gFlowerIconTexture(),
	gPauseBack(),
	gPauseButtonBack(),
	gPauseButtonBack_Select(),
	gBlackCurtainAlpha(255),
	gCurrentMenuNum(0)
{}

CGameUIManager::~CGameUIManager() {
}

void CGameUIManager::Initialize() {
	//�t�H���g�̐ݒ�
	gScoreFont.Create(48, "MS �S�V�b�N");
	gPauseMenuFont.Create(32, "MS �S�V�b�N");
	
	//�摜�̓ǂݍ���
	gScoreBackTexture.Load("ScoreBack.png");
	gWindIconTexture.Load("WindIcon.png");
	gFlowerIconBackTexture.Load("FlowerIconBack.png");

	gFlowerIconTexture = new CTexture[FLOWERTYPE_COUNT];
	gFlowerIconTexture[0].Load("Flower_Blue.png");
	gFlowerIconTexture[1].Load("Flower_Red.png");
	gFlowerIconTexture[2].Load("Flower_Green.png");

	gPauseBack.Load("PauseMenuBack.png");
	gPauseButtonBack.Load("PauseButton.png");
	gPauseButtonBack_Select.Load("PauseButton_Select.png");

	//�Ö��A���t�@�l�̏�����
	gBlackCurtainAlpha = 255;
	gbPause = false;
	gCurrentMenuNum = 0;
}
bool CGameUIManager::GameStartAnim() {
	gBlackCurtainAlpha -= 3;
	//�Ö����オ�肫���Ă�����I����ʒm����
	if (gBlackCurtainAlpha <= 0)
	{
		gBlackCurtainAlpha = 0;
		return true;
	}
	return false;
}

bool CGameUIManager::GameEndAnim() {
	gBlackCurtainAlpha += 3;
	//�Ö����オ�肫���Ă�����I����ʒm����
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
		gCurrentMenuNum--;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW))
	{
		gCurrentMenuNum++;
	}
	//�l��0�`2�͈̔͂ɒ���
	gCurrentMenuNum = (std::max)(gCurrentMenuNum, 0);
	gCurrentMenuNum = (std::min)(gCurrentMenuNum, 2);

	//����{�^������
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		gbPause = false;
	}
	//Esc�{�^���ŃQ�[���ɖ߂�
	else if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		gCurrentMenuNum = 0;
		gbPause = false;
	}
}
void CGameUIManager::RenderUI(int fcount, int fmaxcount, Result *result) {
	int ScreenWidth = g_pGraphics->GetTargetWidth();
	int ScreenHeight = g_pGraphics->GetTargetHeight();

	//�X�R�A�A���A�Ԃ̕`��
	gScoreBackTexture.Render(10, 10);
	char str[256];
	sprintf(str, "Tab�L�[�Ń|�[�Y\nSpace�L�[�Ńp���[������\nScore : %d", result->score);
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

	//�|�[�Y��ʂ��J���Ă���Ƃ��̃|�[�Y���j���[�`��
	if (gbPause)
	{
		gPauseBack.Render(400, 150);
		for (int i = 0; i < 3; i++)
		{
			if (i == gCurrentMenuNum)
			{
				gPauseButtonBack_Select.Render((ScreenWidth - gPauseButtonBack_Select.GetWidth()) / 2,
					(ScreenHeight - gPauseButtonBack_Select.GetHeight()) / 2 + i * 100);
			}
			else
			{
				gPauseButtonBack.Render((ScreenWidth - gPauseButtonBack.GetWidth()) / 2,
					(ScreenHeight - gPauseButtonBack.GetHeight()) / 2 + i * 100);
			}
			switch (i)
			{
			case 0:
				gPauseMenuFont.RenderString(700, 440, "�Q�[���ɖ߂�");
				break;
			case 1:
				gPauseMenuFont.RenderString(700, 540, "���g���C");
				break;
			case 2:
				gPauseMenuFont.RenderString(700, 640, "�^�C�g���֖߂�");
				break;
			}
		}
	}

	//�Ö��̕`��
	CGraphicsUtilities::RenderFillRect(0, 0, ScreenWidth, ScreenHeight, MOF_ARGB(gBlackCurtainAlpha, 0, 0, 0));
}
void CGameUIManager::ReleaseUI() {
	gScoreBackTexture.Release();
	gWindIconTexture.Release();
	gFlowerIconBackTexture.Release();
	gFlowerIconTexture[0].Release();
	gFlowerIconTexture[1].Release();
	gFlowerIconTexture[2].Release();
	gPauseBack.Release();
	gPauseButtonBack.Release();
	gPauseButtonBack_Select.Release();
}