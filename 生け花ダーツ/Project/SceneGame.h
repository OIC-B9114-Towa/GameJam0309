#pragma once
#include "SceneBase.h"
#include "GameUIManager.h"
#include "InGameData.h"

#define			FLOWERCOUNT				5
#define			MAXWINDPOWER			5

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
	LPGeometry	gOutBoard;							//�_�[�c���O�ꂽ���̔���p
	LPGeometry	gDartsFrame;						//�Ԃ�}���g
	LPGeometry	gDartsOutFrame;						//�g�̊O��

	CInGameData::Result		gScoreResult;
	CInGameData::Wind*		gWind;

	int			gGamePhase;							//�Q�[����
	int			gCurrentFlowerCount;				//���ݓ������Ԃ̖{��

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

