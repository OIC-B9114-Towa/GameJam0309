/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneEditor.h"

CSceneBase* g_pScene;

bool m_bDebug = false;

/**
 * �V�[���`��
 */


/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	MoveWindow(g_pFramework->GetWindow()->GetWindowHandle(), (GetSystemMetrics(SM_CXSCREEN) - 1424) / 2, (GetSystemMetrics(SM_CYSCREEN) - 720) / 2, 1280, 720, FALSE);
	g_pGraphics->SetScreenSize(1424, 720);

	g_pScene = new CSceneEditor();
	g_pScene->Initialize();

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
	CInputManager::GetInstance().Refresh();

	g_pScene->Update();
	if (m_bDebug)
	{
		g_pScene->UpdateDebug();
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

	g_pScene->Render();
	if (m_bDebug)
	{
		g_pScene->RenderDebug();
	}	

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
	g_pScene->Release();
	if (g_pScene)
	{
		delete g_pScene;
		g_pScene = NULL;
	}	
	return TRUE;
}