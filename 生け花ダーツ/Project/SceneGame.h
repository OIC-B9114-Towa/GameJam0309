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
	LPGeometry	gOutBoard;				//ダーツが外れた時の判定用
	LPGeometry	gDartsFrame;			//花を挿す枠
	LPGeometry	gDartsOutFrame;			//枠の外側

	int			gCurrentSceneState;		//現在のシーン状態

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

