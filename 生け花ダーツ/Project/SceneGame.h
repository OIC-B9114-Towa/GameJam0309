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

	int			gGamePhase;							//ゲーム状況
	int			gCurrentFlowerCount;				//現在投げた花の本数

	float		gThrowPower;
	bool		gbIsThrowing;						//投てき中フラグ
	bool		gbPowerPlus;						//投てきパワー増減フラグ

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

