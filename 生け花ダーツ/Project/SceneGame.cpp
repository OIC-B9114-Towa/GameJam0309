#include "SceneGame.h"

CSceneGame::CSceneGame():
m_Flower(){

}

void CSceneGame::Initialize() {
	m_Flower.Load();
	m_Flower.Initialize();
	InitializeCamera();
	//�V�F�[�_�[�G�t�F�N�g�쐬
	m_ShadowMap.Create(2048);
	//�V���h�E�}�b�v�̃p�����[�^�[�ݒ�
	m_ShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);
}

void CSceneGame::InitializeCamera() {
	//�J����������
	m_Camera.SetViewPort();
	m_Camera.LookAt(Vector3(0.0f, 3.0f, -2.0f), Vector3(0, 0, 0), Vector3(0, 1, 0));
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
	m_Flower.Update();
	UpdateCamera();
}

void CSceneGame::UpdateCamera() {
	//�}�E�X�ɂ��J������]
	CVector3 vRot;
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		g_pInput->GetMouseMove(vRot);
		vRot *= 0.005f;
	}
	m_CamAngle += Vector3(vRot.y, vRot.x, 0);

	//�J�����̌������v�Z
	CMatrix33 matRot;
	matRot.RotationZXY(m_CamAngle);
	CVector3 vFront(0, 0, 1);
	vFront.TransformCoord(matRot, vFront);

	//�L�[�ɂ��J�����ړ�
	float speed = 0.1;
	CVector3 vMove;
	CVector3 mMove;
	float mwheel = g_pInput->GetMouseWheelMove();
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vMove.x -= speed;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vMove.x += speed;
	}
	else if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
	{
		g_pInput->GetMouseMove(mMove);
		mMove *= 0.005f;
		vMove.x -= mMove.x;
		vMove.y += mMove.y;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		vMove.z -= speed;
	}
	else if (mwheel < 0)
	{
		vMove.z -= speed * 2;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		vMove.z += speed;
	}
	else if (mwheel > 0)
	{
		vMove.z += speed * 2;
	}

	vMove.TransformCoord(matRot, vMove);
	CVector3 vPos = m_Camera.GetViewPosition() + vMove;

	//�J�����X�V
	m_Camera.LookAt(vPos, vPos + vFront, Vector3(0, 1, 0));
	m_Camera.Update();
}

void CSceneGame::UpdateDebug() {
	m_Flower.UpdateDebug();
}

void CSceneGame::Render() {
	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);

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
		matPlane.Scaling(50.0f);
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		m_Flower.Render();
	}
	g_pGraphics->SetDepthEnable(FALSE);

	CGraphicsUtilities::RenderString(10, 10, "�㉺�L�[�E�}�E�X�z�C�[���ŃJ�����O��ړ�");
	CGraphicsUtilities::RenderString(10, 34, "���E�L�[�E�}�E�X�E�h���b�O�ŃJ�����㉺���E�ړ�");
	CGraphicsUtilities::RenderString(10, 58, "�}�E�X���h���b�O�ŃJ������]");
	CGraphicsUtilities::RenderString(10, 82, "SPACE�L�[�ŃV���h�E�}�b�v�K�p %s", m_EffectEnabled ? "ON" : "OFF");
	CGraphicsUtilities::RenderString(10, 106, "ENTER�L�[�ŃI�u�W�F�N�g�ēǂݍ���");
}

void CSceneGame::RenderUseShader() {
	//���`��p�s��
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);
	g_pGraphics->SetBlending(BLEND_NONE);

	m_ShadowMap.BeginTexture();
	{
		g_pGraphics->ClearTarget();

		CGraphicsUtilities::RenderPlane(matPlane);

		m_Flower.Render();
	}
	m_ShadowMap.EndTexture();

	g_pGraphics->SetBlending(BLEND_NORMAL);

	m_ShadowMap.BeginRenderer();
	{
		g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		m_Flower.Render();
	}
	m_ShadowMap.EndRenderer();
}

void CSceneGame::RenderDebug() {
	CGraphicsUtilities::RenderString(10, 130, "Debug : ON");
}

void CSceneGame::Release() {
	m_Flower.Release();
}