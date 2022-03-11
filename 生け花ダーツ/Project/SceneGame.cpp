#include "SceneGame.h"
#include <ctime>

CSceneGame::CSceneGame() :
	gGamePhase(SS_INTRO),
	gCurrentFlowerCount(0),
	gThrowPower(0.0f),
	gbIsThrowing(false),
	gbPowerPlus(false)
{}

void CSceneGame::Initialize() {
	g_pGraphics->SetScreenSize(1600, 900);

	//�X�R�A�A���f�[�^�̏�����
	gScoreResult = Result{0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT]};
	//�����̏�����
	std::srand(time(NULL));
	//�Ԃ̏�����
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//�X�R�A�L�^�p�\���̂�������
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % FLOWERTYPE_COUNT;
	}
	gGamePhase = SS_INTRO;
	gCurrentFlowerCount = 0;
	gGameUIManager.Initialize();
}

void CSceneGame::Update() {
	//�e�V�[����Ԃɍ��킹������
	switch (gGamePhase)
	{
	case SS_INTRO:
		//�Ö����オ��܂őҋ@
		if (gGameUIManager.GameStartAnim())
		{
			gGamePhase = SS_WAITTHROW;
		}
		break;
	case SS_WAITTHROW:
		//Tab�L�[�Ń|�[�Y��ʂ�
		if (g_pInput->IsKeyPush(MOFKEY_TAB))
		{
			gGameUIManager.OpenPauseMenu();
			gGamePhase = SS_PAUSE;
			return;
		}
		//�L�[�𒷉������Ă���ԁA������͂���
		if (g_pInput->IsKeyHold(MOFKEY_SPACE))
		{
			//�p���[������
			if (gbPowerPlus)
			{
				gThrowPower += ADDTHROWPOWERPERFRAME;
				//�ō��l������Ύ��̃t���[�����猸��������
				if (gThrowPower >= MAXTHROWPOWER)
				{
					gThrowPower = MAXTHROWPOWER;
					gbPowerPlus = !gbPowerPlus;
				}
			}
			//�p���[������
			else
			{
				gThrowPower -= ADDTHROWPOWERPERFRAME;
				//�Œ�l�������Ύ��̃t���[�����瑝��������
				if (gThrowPower <= MINTHROWPOWER)
				{
					gThrowPower = MINTHROWPOWER;
					gbPowerPlus = !gbPowerPlus;
				}
			}
		}
		else if (g_pInput->IsKeyPull(MOFKEY_SPACE))
		{
			//�����I�������uTHROWING�v�t�F�[�Y�ֈڍs

		}
		break;
	case SS_PAUSE:
		//�|�[�Y������
		gGameUIManager.UpdatePauseMenu();
		
		//�|�[�Y��ʏI�����A���Ă��ҋ@��Ԃɖ߂�
		if (!gGameUIManager.IsOpenPauseMenu())
		{
			switch (gGameUIManager.GetPauseMenuNum())
			{
			case PM_RETURNGAME:
				gGamePhase = SS_WAITTHROW;
				break;
			case PM_RETRY:
				gGamePhase = SS_RETRY;
				break;
			case PM_GAMEEND:
				gGamePhase = SS_GAMEEND;
				break;
			}
		}
		break;
	case SS_THROWING:
		//���Ă�������

		break;
	case SS_WAITTHROWRESULT:
		//���Ă��I��������


		//�������{�����{�P���A����̖{�������I������Q�[�����I������
		gCurrentFlowerCount++;
		if (gCurrentFlowerCount >= FLOWERCOUNT)
		{
			gGamePhase = SS_GAMEEND;
		}
		break;

	case SS_GAMERESULT:
		if (gGameUIManager.ResultSlideIn())
		{
			if (g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				gGamePhase = SS_GAMEEND;
			}
			else if (g_pInput->IsKeyPush(MOFKEY_X))
			{
				gGamePhase = SS_RETRY;
			}
		}
		break;

	case SS_GAMEEND:
		//���ׂē����I�������Q�[���I��
		//�Ö��������܂őҋ@
		if (gGameUIManager.GameEndAnim())
		{
			m_bEnd = true;
			m_NextScene = SCENETYPE_TITLE;
		}
		break;

	case SS_RETRY:
		//�|�[�Y���j���[�Ń��g���C�I����
		//�Ö��������܂őҋ@
		if (gGameUIManager.GameEndAnim())
		{
			gGamePhase = SS_INTRO;
			this->Release();
			this->Initialize();
		}
		break;
	}

	//UI�A�b�v�f�[�g����
	gGameUIManager.UpdateUI();
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	//UI�̕`��
	gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {
	gGameUIManager.ReleaseUI();
}