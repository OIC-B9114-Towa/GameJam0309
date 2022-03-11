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

	CTexture	gScoreBackTexture;					//�X�R�A�o�b�N�{�[�h
	CTexture	gWindIconTexture;					//���̃A�C�R��
	CTexture	gFlowerIconBackTexture;				//�Ԃ̃A�C�R���o�b�N�{�[�h
	CTexture*	gFlowerIconTexture;					//�Ԃ̃A�C�R��

	CTexture	gPauseBack;							//�|�[�Y��ʔw�i
	CTexture	gPauseButtonBack;					//�|�[�Y��ʃ{�^���w�i
	CTexture	gPauseButtonBack_Select;			//�|�[�Y��ʃ{�^���w�i�i�I�����j

	int			gBlackCurtainAlpha;					//�Ö��A���t�@�l
	float		gResultSlideOffsetX;				//���U���g�p�X���C�h�I�t�Z�b�gX
	float		gResultSlideSpeedX;					//�X���C�h���x

	bool		gbPause;							//�|�[�Y���j���[�t���O
	int			gCurrentMenuNum;					//���݂̑I�����j���[�ԍ�

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

