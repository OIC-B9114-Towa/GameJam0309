#pragma once
#include "SceneBase.h"
#include "Flower.h"
#include "Target.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

class CSceneGame : public CSceneBase
{
private:
	CFlower m_Flower;
	CTarget m_Target[5];

	//�J����
	CCamera						m_Camera;

	CVector3 m_vPos;
	CVector3 m_vTrans;

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
	void RenderFlower();
public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

