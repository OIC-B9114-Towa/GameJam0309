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
	gScoreResult = Result{ 0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT] };
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

	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		m_Flower[i].Load(CFlowerPartsLoder::GetInstance().GetBoxStatus(gScoreResult.FlowerColor[i]));
		m_Flower[i].Initialize();
	}

	TargetStatus st[5];
	st[0].Pos = CVector3(0, 2, 1);
	st[0].Scale = CVector3(1, 0.1f, 1);
	st[0].bxMove = true;
	st[1].Pos = CVector3(0, -5, 1);
	st[1].Scale = CVector3(0.5f, 0.1f, 0.5f);
	st[1].bzMove = true;
	st[2].Pos = CVector3(0, 2, 1);
	st[2].Scale = CVector3(1, 0.1f, 2);
	st[2].byMove = true;
	st[2].bxMove = true;
	st[3].Pos = CVector3(0, 2, 1);
	st[3].Scale = CVector3(2, 0.1f, 1);
	st[3].bzMove = true;
	st[4].Pos = CVector3(0, 2, 1);
	st[4].Scale = CVector3(1, 0.1f, 1);
	st[4].Pos = CVector3(0, 2, 1);
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Initialize(st[i]);
	}
	InitializeCamera();
	//�V�F�[�_�[�G�t�F�N�g�쐬
	m_ShadowMap.Create(2048);
	//�V���h�E�}�b�v�̃p�����[�^�[�ݒ�
	m_ShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);
}

void CSceneGame::InitializeCamera() {
	m_vPos = CVector3(0.0135f, 23.1420f, 1.8235f);
	m_vTrans = CVector3(0.0136f, 22.1426f, 1.859f);
	//�J����������
	m_Camera.SetViewPort();
	m_Camera.LookAt(m_vPos, m_vTrans, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Camera);

	//���C�g������
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	m_Light.SetDiffuse(MOF_COLOR_HWHITE);
	m_Light.SetAmbient(MOF_COLOR_CBLACK);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

void CSceneGame::Update() {
	//�e�V�[����Ԃɍ��킹������
	switch (gGamePhase)
	{
	case SS_INTRO:
		UpdateSS_INTRO();
		break;
	case SS_WAITTHROW:
		UpdateSS_WAITTHROW();
		break;
	case SS_PAUSE:
		UpdateSS_PAUSE();
		break;
	case SS_THROWING:
		//���Ă�������
		UpdateSS_THROWING();
		break;
	case SS_WAITTHROWRESULT:
		//���Ă��I��������
		UpdateSS_WAITTHROWRESULT();
		break;
	case SS_GAMERESULT:
		UpdateSS_GAMERESULT();
		break;
	case SS_GAMEEND:
		UpdateSS_GAMEEND();
		break;
	case SS_RETRY:
		UpdateSS_RETRY();
		break;
	}
	//UI�A�b�v�f�[�g����
	gGameUIManager.UpdateUI();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Update();
	}
}

void CSceneGame::UpdateSS_INTRO() {
	//�Ö����オ��܂őҋ@
	if (gGameUIManager.GameStartAnim())
	{
		gGamePhase = SS_WAITTHROW;
	}
}

void CSceneGame::UpdateSS_WAITTHROW() {
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
		m_Flower[gCurrentFlowerCount].Fire();
		gGamePhase = SS_THROWING;
	}
}

void CSceneGame::UpdateSS_PAUSE() {
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
}

void CSceneGame::UpdateSS_THROWING() {
	m_Flower[gCurrentFlowerCount].Update();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Collision(m_Flower[gCurrentFlowerCount], i);
	}
}

void CSceneGame::UpdateSS_WAITTHROWRESULT() {
	//�������{�����{�P���A����̖{�������I������Q�[�����I������
	gCurrentFlowerCount++;
	if (gCurrentFlowerCount >= FLOWERCOUNT)
	{
		gGamePhase = SS_GAMEEND;
	}
}

void CSceneGame::UpdateSS_GAMERESULT() {
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
}

void CSceneGame::UpdateSS_GAMEEND() {
	//���ׂē����I�������Q�[���I��
		//�Ö��������܂őҋ@
	if (gGameUIManager.GameEndAnim())
	{
		m_bEnd = true;
		m_NextScene = SCENETYPE_TITLE;
	}
}

void CSceneGame::UpdateSS_RETRY() {
	//�|�[�Y���j���[�Ń��g���C�I����
		//�Ö��������܂őҋ@
	if (gGameUIManager.GameEndAnim())
	{
		gGamePhase = SS_INTRO;
		this->Release();
		this->Initialize();
	}
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);


	CGraphicsUtilities::SetCamera(&m_Camera);

	//�V�F�[�_�[�G�t�F�N�g���g���ĕ`��
	if (m_EffectEnabled)
	{
		RenderUseShader();
	}
	//�V�F�[�_�[�G�t�F�N�g���g�킸�ɕ`��
	else
	{
		//���`��p�s��
		CMatrix44 matPlane;
		//matPlane.Scaling(50.0f);
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	g_pGraphics->SetDepthEnable(FALSE);

	//UI�̕`��
	gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderUseShader() {
	//���`��p�s��
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);
	g_pGraphics->SetBlending(BLEND_NONE);

	m_ShadowMap.BeginTexture();
	{
		g_pGraphics->ClearTarget();

		//CGraphicsUtilities::RenderPlane(matPlane);

		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	m_ShadowMap.EndTexture();

	g_pGraphics->SetBlending(BLEND_NORMAL);

	m_ShadowMap.BeginRenderer();
	{
		g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
		//���`��
		//CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	m_ShadowMap.EndRenderer();
}

void CSceneGame::RenderFlower() {
	for (int i = 0; i <= gCurrentFlowerCount; i++)
	{
		int no = m_Flower[i].GetNo();
		if (no != -1)
			m_Flower[i].Render(m_Target[no].GetPos());
		else
			m_Flower[i].Render();
	}
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {
	gGameUIManager.ReleaseUI();
	if (gScoreResult.FlowerPos)
	{
		delete[] gScoreResult.FlowerPos;
		gScoreResult.FlowerPos = NULL;
	}
	if (gScoreResult.FlowerColor)
	{
		delete[] gScoreResult.FlowerColor;
		gScoreResult.FlowerColor = NULL;
	}
}