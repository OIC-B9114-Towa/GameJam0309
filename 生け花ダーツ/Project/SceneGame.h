#pragma once
#include "SceneBase.h"
#include "Flower.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

class CSceneGame : public CSceneBase
{
private:
	CFlower m_Flower;

	//�J����
	CCamera						m_Camera;
	//�J�����p�x
	CVector3					m_CamAngle;
	//���C�g
	CDirectionalLight			m_Light;
	//�V���h�E�}�b�v�V�F�[�_�[
	CShaderEffect_ShadowMap		m_ShadowMap;
	//�V�F�[�_�[�G�t�F�N�g�L���t���O
	bool							m_EffectEnabled;

	void InitializeCamera();
	void UpdateCamera();
	void RenderUseShader();

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

