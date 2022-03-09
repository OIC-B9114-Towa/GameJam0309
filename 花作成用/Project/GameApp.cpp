/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

//�J����
CCamera						gCamera;
//�J�����p�x
CVector3					gCamAngle;
//���C�g
CDirectionalLight			gLight;
//�V���h�E�}�b�v�V�F�[�_�[
CShaderEffect_ShadowMap		gShadowMap;
//�V�F�[�_�[�G�t�F�N�g�L���t���O
bool							gEffectEnabled = true;

typedef struct tag_BoxStatus
{
	CVector3 Scale;
	CVector3 Translate;
	tag_BoxStatus() :
		Scale(),
		Translate()
	{
	}
}BoxStatus;

std::vector<BoxStatus> m_BoxStatus;

/**
 * �V�[���`��
 */
void RenderScene() {
	//�l�X�ȃv���~�e�B�u����ׂ�
	CMatrix44 matWorld;

	for (int i = 0; i < m_BoxStatus.size(); i++)
	{
		matWorld.Scaling(m_BoxStatus[i].Scale);
		matWorld.SetTranslation(m_BoxStatus[i].Translate);
		CGraphicsUtilities::RenderBox(matWorld);
	}
}

bool LoadBoxStatus() {
	FILE* fp = fopen("BoxStatus.txt", "rb");
	if (!fp) { return false; }

	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");

	int boxcnt = atoi(pstr);
	pstr = strtok(NULL, ",");

	for (int i = 0; i < boxcnt; i++)
	{
		m_BoxStatus.push_back(BoxStatus());
		m_BoxStatus[i].Scale.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.z = atof(pstr);
		pstr = strtok(NULL, ",");
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�J����������
	//�J����������
	gCamera.SetViewPort();
	gCamera.LookAt(Vector3(0.0f, 3.0f, -2.0f), Vector3(0, 0, 0), Vector3(0, 1, 0));
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	gCamera.Update();
	CGraphicsUtilities::SetCamera(&gCamera);

	//���C�g������
	gLight.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	gLight.SetDiffuse(MOF_COLOR_HWHITE);
	gLight.SetAmbient(MOF_COLOR_CBLACK);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	//�V�F�[�_�[�G�t�F�N�g�쐬
	gShadowMap.Create(2048);

	//�V���h�E�}�b�v�̃p�����[�^�[�ݒ�
	gShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);

	LoadBoxStatus();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�}�E�X�ɂ��J������]
	CVector3 vRot;
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		g_pInput->GetMouseMove(vRot);
		vRot *= 0.005f;
	}
	gCamAngle += Vector3(vRot.y, vRot.x, 0);

	//�J�����̌������v�Z
	CMatrix33 matRot;
	matRot.RotationZXY(gCamAngle);
	CVector3 vFront(0, 0, 1);
	vFront.TransformCoord(matRot, vFront);

	//�L�[�ɂ��J�����ړ�
	float speed = 0.1f;
	CVector3 vMove;
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vMove.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vMove.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		vMove.z -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		vMove.z += speed;
	}
	vMove.TransformCoord(matRot, vMove);
	CVector3 vPos = gCamera.GetViewPosition() + vMove;

	//�J�����X�V
	gCamera.LookAt(vPos, vPos + vFront, Vector3(0, 1, 0));
	gCamera.Update();

	//�V�F�[�_�[�G�t�F�N�gON/OFF�؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		gEffectEnabled = !gEffectEnabled;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		LoadBoxStatus();
	}

	return TRUE;
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`�揈��
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);

	//���`��p�s��
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);

	//�V�F�[�_�[�G�t�F�N�g���g���ĕ`��
	if (gEffectEnabled)
	{
		g_pGraphics->SetBlending(BLEND_NONE);

		gShadowMap.BeginTexture();
		{
			g_pGraphics->ClearTarget();

			CGraphicsUtilities::RenderPlane(matPlane);

			RenderScene();
		}
		gShadowMap.EndTexture();

		g_pGraphics->SetBlending(BLEND_NORMAL);

		gShadowMap.BeginRenderer();
		{
			g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
			//���`��
			CGraphicsUtilities::RenderPlane(matPlane, CVector4(0, 0.5f, 0.5f, 1));
			//�V�[���`��
			RenderScene();
		}
		gShadowMap.EndRenderer();
	}
	//�V�F�[�_�[�G�t�F�N�g���g�킸�ɕ`��
	else
	{
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane, CVector4(0, 0.5f, 0.5f, 1));

		//�V�[���`��
		RenderScene();
	}

	CGraphicsUtilities::RenderString(10, 10, "�㉺���E�L�[�ŃJ�����ړ�");
	CGraphicsUtilities::RenderString(10, 34, "�}�E�X���h���b�O�ŃJ������]");
	CGraphicsUtilities::RenderString(10, 58, "SPACE�L�[�ŃV���h�E�}�b�v�K�p %s", gEffectEnabled ? "ON" : "OFF");

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	//�V�F�[�_�[�G�t�F�N�g���
	gShadowMap.Release();
	return TRUE;
}