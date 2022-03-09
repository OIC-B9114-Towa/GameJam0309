#pragma once
#include "SceneBase.h"
#include "GameUIManager.h"
class CSceneGame : public CSceneBase
{
private:
	typedef enum s_SceneState {
		INTRO,
		WAITTHROW,
		PAUSE,
		THROWING,
		WAITTHROWRESULT,
		GAMEEND,

		STATE_COUNT,
	}SceneState;

	CGameUIManager gGameUIManager;

	CCamera		gCamera;
	LPGeometry	gOutBoard;				//�_�[�c���O�ꂽ���̔���p
	LPGeometry	gDartsFrame;			//�Ԃ�}���g
	LPGeometry	gDartsOutFrame;			//�g�̊O��

	int			gCurrentSceneState;		//���݂̃V�[�����

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

