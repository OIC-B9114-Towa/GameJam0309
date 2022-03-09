#pragma once
#include "SceneBase.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>
#include	"EditMenuObject.h"

class CSceneEditor : public CSceneBase
{
private:
	typedef struct tag_BoxStatus
	{
		CVector3 Scale;
		CVector3 Translate;
		CVector4 Color;

		tag_BoxStatus() :
			Scale(),
			Translate(),
			Color()
		{
		}
	}BoxStatus;

	//�J����
	CCamera						m_Camera;
	CCamera						m_EditCamera;
	//�J�����p�x
	CVector3					m_CamAngle;
	//���C�g
	CDirectionalLight			m_Light;
	//�V���h�E�}�b�v�V�F�[�_�[
	CShaderEffect_ShadowMap		m_ShadowMap;
	//�V�F�[�_�[�G�t�F�N�g�L���t���O
	bool							m_EffectEnabled;

	std::vector<BoxStatus> m_BoxStatus;

	CEditMenuObject	m_Menu;

	int	m_SelectPartsNo;

	bool m_bTranslucent;

	void InitializeCamera();

	void SetMenuStatus();
	void SubMenuSetButton();

	void RenderScene();
	bool LoadBoxStatus();
	bool SaveBoxStatus();

	void UpdateCamera();

	void UpdateMenuKeyboard();
	void UpdateMenuMouse(Vector2 vec);
	void UpdateMenuResult();

	void UpdateBoxStatus();

	void RenderUseShader();
public:
	CSceneEditor();
	~CSceneEditor();

	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

