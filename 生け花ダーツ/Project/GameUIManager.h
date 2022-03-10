#pragma once
#include <Mof.h>
#include "SceneBase.h"
#include "InGameData.h"

class CGameUIManager
{
private:
	CTexture	gScoreBackTexture;					//�X�R�A�o�b�N�{�[�h
	CTexture	gWindIconTexture;					//���̃A�C�R��
	CTexture	gFlowerIconBackTexture;				//�Ԃ̃A�C�R���o�b�N�{�[�h
	CTexture*	gFlowerIconTexture;					//�Ԃ̃A�C�R��

	CTexture	gThrowResultBackTexture;			//�X�R�A�e�L�X�g�o�b�N�{�[�h

	CTexture	gPauseBack;							//�|�[�Y��ʔw�i
	CTexture	gPauseButtonBack;					//�|�[�Y��ʃ{�^���w�i
	CTexture	gPauseButtonBack_Select;			//�|�[�Y��ʃ{�^���w�i�i�I�����j

	int			gBlackCurtainAlpha;					//�Ö��A���t�@�l

public:

	CGameUIManager();
	~CGameUIManager();
	void Initialize();
	bool GameStartAnim();
	void UpdateUI();
	void RenderUI(int fcount, int fmaxcount, CInGameData::Result *result);
	void ReleaseUI();
};

