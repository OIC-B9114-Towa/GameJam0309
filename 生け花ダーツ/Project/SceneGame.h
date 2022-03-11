#pragma once
#include "SceneBase.h"
#include "GameUIManager.h"
#include "InGameData.h"

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

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

