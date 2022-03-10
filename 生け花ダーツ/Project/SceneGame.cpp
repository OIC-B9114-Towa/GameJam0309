#include "SceneGame.h"

CSceneGame::CSceneGame() {

}

void CSceneGame::Initialize() {

	//スコア、風データの初期化
	gScoreResult = CInGameData::Result{0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT]};
	gWind = new CInGameData::Wind[FLOWERCOUNT]{ 0, 0, CVector3(0, 0, 0) };
	//乱数の初期化
	std::srand(time(NULL));
	//花の初期化
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//スコア記録用構造体を初期化
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % CInGameData::TYPE_COUNT;

		//方向と速度をランダムで算出し、記録する
		gWind[i].gWindDirect = rand() % CInGameData::DIRECT_COUNT;
		int wPower = rand() % MAXWINDPOWER;
		gWind[i].gWindPower = wPower;
		gWind[i].gWindPowerToVector
			= CVector3(wPower * cos(45 * gWind[i].gWindDirect), wPower * sin(45 * gWind[i].gWindDirect), 0);
	}
	gGameUIManager.Initialize();
}

void CSceneGame::Update() {
	//各シーン状態に合わせた処理
	switch (gGamePhase)
	{
	case INTRO:
		if (gGameUIManager.GameStartAnim())
		{
			gGamePhase = WAITTHROW;
		}
		break;
	case WAITTHROW:
		//投げ終わったら「THROWING」フェーズへ移行
		break;
	case PAUSE:
		//ポーズ中(「WAITTHROW」から遷移)
		break;
	case THROWING:
		//投てき中処理
		break;
	case WAITTHROWRESULT:
		//投てき終了時処理


		//投げた本数を＋１し、既定の本数投げ終えたらゲームを終了する
		gCurrentFlowerCount++;
		if (gCurrentFlowerCount >= FLOWERCOUNT)
		{
			gGamePhase = GAMEEND;
		}
		break;
	case GAMEEND:
		//すべて投げ終わったらゲーム終了
		break;
	}
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {

	//UIの描画
	//gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {

}