#pragma once
#include "SceneBase.h"
#include "GameUIManager.h"
#include "InGameData.h"
#include "Flower.h"
#include "Target.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

#define			FLOWERCOUNT				5
#define			MAXWINDPOWER			5
#define			MAXTHROWPOWER			1.2f
#define			MINTHROWPOWER			0.8f
#define			ADDTHROWPOWERPERFRAME	0.01f

class CSceneGame : public CSceneBase
{
private:
	typedef enum s_SceneState {
		SS_INTRO,
		SS_WAITTHROW,
		SS_PAUSE,
		SS_THROWING,
		SS_WAITTHROWRESULT,
		SS_GAMERESULT,
		SS_GAMEEND,
		SS_RETRY,

		SCENESTATE_COUNT,
	}SceneState;

	CGameUIManager gGameUIManager;

	Result		gScoreResult;

	int			gGamePhase;							//�Q�[����
	int			gCurrentFlowerCount;				//���ݓ������Ԃ̖{��

	float		gThrowPower;
	bool		gbIsThrowing;						//���Ă����t���O
	bool		gbPowerPlus;						//���Ă��p���[�����t���O

	void UpdateSS_INTRO();
	void UpdateSS_WAITTHROW();
	void UpdateSS_PAUSE();
	void UpdateSS_THROWING();
	void UpdateSS_WAITTHROWRESULT();
	void UpdateSS_GAMERESULT();
	void UpdateSS_GAMEEND();
	void UpdateSS_RETRY();

	float GetSpeed(int type);
#pragma region ���S��
	CFlower m_Flower[FLOWERCOUNT];
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
	#pragma endregion

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

