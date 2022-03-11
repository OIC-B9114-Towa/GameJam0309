#include "SceneGame.h"
#include <ctime>

CSceneGame::CSceneGame() :
	gGamePhase(SS_INTRO),
	gCurrentFlowerCount(0)
{}

void CSceneGame::Initialize() {
	//スコア、風データの初期化
	gScoreResult = Result{0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT]};
	gWind = new Wind[FLOWERCOUNT]{ 0, 0, CVector3(0, 0, 0) };
	//乱数の初期化
	std::srand(time(NULL));
	//花の初期化
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//スコア記録用構造体を初期化
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % FLOWERTYPE_COUNT;

		//方向と速度をランダムで算出し、記録する
		gWind[i].gWindDirect = rand() % WINDDIRECT_COUNT;
		int wPower = rand() % MAXWINDPOWER;
		gWind[i].gWindPower = wPower;
		gWind[i].gWindPowerToVector
			= CVector3(wPower * cos(45 * gWind[i].gWindDirect), wPower * sin(45 * gWind[i].gWindDirect), 0);
	}

	gGamePhase = SS_INTRO;
	gCurrentFlowerCount = 0;
	gGameUIManager.Initialize();
}

void CSceneGame::Update() {
	//各シーン状態に合わせた処理
	switch (gGamePhase)
	{
	case SS_INTRO:
		//暗幕が上がるまで待機
		if (gGameUIManager.GameStartAnim())
		{
			gGamePhase = SS_WAITTHROW;
		}
		break;
	case SS_WAITTHROW:
		//Tabキーでポーズ画面へ
		if (g_pInput->IsKeyPush(MOFKEY_TAB))
		{
			gGamePhase = SS_PAUSE;
			return;
		}
		//キーを長押ししている間、投げる力を決
		if (g_pInput->IsKeyHold(MOFKEY_SPACE))
		{
			//パワー増加中
			if (gbPowerPlus)
			{
				gThrowPower += ADDTHROWPOWERPERFRAME;
				//最高値を上回れば次のフレームから減少させる
				if (gThrowPower >= MAXTHROWPOWER)
				{
					gThrowPower = MAXTHROWPOWER;
					gbPowerPlus = !gbPowerPlus;
				}
			}
			//パワー減少中
			else
			{
				gThrowPower -= ADDTHROWPOWERPERFRAME;
				//最低値を下回れば次のフレームから増加させる
				if (gThrowPower <= MINTHROWPOWER)
				{
					gThrowPower = MINTHROWPOWER;
					gbPowerPlus = !gbPowerPlus;
				}
			}
		}
		else if (g_pInput->IsKeyPull(MOFKEY_SPACE))
		{
			//投げ終わったら「THROWING」フェーズへ移行

		}
		else
		{
			//花移動処理
			if (g_pInput->IsKeyHold(MOFKEY_UPARROW))
			{

			}
			else if (g_pInput->IsKeyHold(MOFKEY_UPARROW))
			{

			}
			if (g_pInput->IsKeyHold(MOFKEY_RIGHTARROW))
			{

			}
			else if (g_pInput->IsKeyHold(MOFKEY_LEFTARROW))
			{

			}
		}
		break;
	case SS_PAUSE:
		//ポーズ中処理
		gGameUIManager.UpdatePauseMenu();
		
		//ポーズ画面終了時、投てき待機状態に戻す
		if (!gGameUIManager.IsOpenPauseMenu())
		{
			switch (gGameUIManager.GetPauseMenuNum())
			{
			case PM_RETURNGAME:
				gGamePhase = SS_WAITTHROW;
				break;
			case PM_RETRY:
				gGamePhase = SS_RETRY;
				break;
			case PM_GAMEEND:
				gGamePhase = SS_GAMEEND;
				break;
			}
		}
		break;
	case SS_THROWING:
		//投てき中処理
		break;
	case SS_WAITTHROWRESULT:
		//投てき終了時処理


		//投げた本数を＋１し、既定の本数投げ終えたらゲームを終了する
		gCurrentFlowerCount++;
		if (gCurrentFlowerCount >= FLOWERCOUNT)
		{
			gGamePhase = SS_GAMEEND;
		}
		break;

	case SS_GAMEEND:
		//すべて投げ終わったらゲーム終了
		//暗幕が下りるまで待機
		if (gGameUIManager.GameEndAnim())
		{
			m_bEnd = true;
			m_NextScene = SCENETYPE_TITLE;
		}
		break;

	case SS_RETRY:
		//ポーズメニューでリトライ選択時
		//暗幕が下りるまで待機
		if (gGameUIManager.GameEndAnim())
		{
			gGamePhase = SS_INTRO;
			this->Initialize();
		}
		break;
	}

	//UIアップデート処理
	gGameUIManager.UpdateUI();
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	//UIの描画
	gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {
	gGameUIManager.ReleaseUI();
}