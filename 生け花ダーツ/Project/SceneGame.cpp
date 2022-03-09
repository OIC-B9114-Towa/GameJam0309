#include "SceneGame.h"

CSceneGame::CSceneGame() {

}

void CSceneGame::Initialize() {
	gGameUIManager.Initialize();
}

void CSceneGame::Update() {
	//äeÉVÅ[ÉìèÛë‘Ç…çáÇÌÇπÇΩèàóù
	switch (gCurrentSceneState)
	{
	case INTRO:
		break;
	case WAITTHROW:
		break;
	case PAUSE:
		break;
	case THROWING:
		break;
	case WAITTHROWRESULT:
		break;
	case GAMEEND:
		break;
	}
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	gDartsFrame = CGraphicsUtilities::CreateBoxGeometry(10.0f, 5.0f, 1.0f, 1, 1, 1, CVector3(0, 0, 0));
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {

}