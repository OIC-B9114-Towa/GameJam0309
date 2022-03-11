#include "SceneGame.h"
#include <ctime>

CSceneGame::CSceneGame() :
	gGamePhase(SS_INTRO),
	gCurrentFlowerCount(0),
	gThrowPower(0.0f),
	gbIsThrowing(false),
	gbPowerPlus(false)
{}

void CSceneGame::Initialize() {
	g_pGraphics->SetScreenSize(1600, 900);

	//スコア、風データの初期化
	gScoreResult = Result{ 0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT] };
	//乱数の初期化
	std::srand(time(NULL));
	//花の初期化
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//スコア記録用構造体を初期化
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % FLOWERTYPE_COUNT;
	}
	gGamePhase = SS_INTRO;
	gCurrentFlowerCount = 0;
	gGameUIManager.Initialize();

	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		m_Flower[i].Load(CFlowerPartsLoder::GetInstance().GetBoxStatus(gScoreResult.FlowerColor[i]));
		m_Flower[i].Initialize();
	}

	TargetStatus st[5];

	for (int i = 0; i < 5; i++)
	{
		st[i].Pos.x = rand() % 4 - 2;
		st[i].Pos.y = rand() % 4 - 2;
		st[i].Pos.z = rand() % 4 - 2;
		st[i].StartPos.x = st[i].Pos.x - (rand() % 8 + 2);
		st[i].StartPos.y = st[i].Pos.y - (rand() % 8 + 2);
		st[i].StartPos.z = st[i].Pos.z - (rand() % 8 + 2);
		st[i].EndPos.x = st[i].Pos.x + (rand() % 8 + 2);
		st[i].EndPos.y = st[i].Pos.y + (rand() % 8 + 2);
		st[i].EndPos.z = st[i].Pos.z + (rand() % 8 + 2);
		st[i].Scale.x = rand() % 3 + 1;
		st[i].Scale.z = rand() % 3 + 1;
		st[i].Scale.y = float(rand() % 3 + 1) / 10;
		st[i].Speed.x = float(rand() % 35 + 5) / 100;
		st[i].Speed.y = float(rand() % 35 + 5) / 100;
		st[i].Speed.z = float(rand() % 35 + 5) / 100;
		st[i].bxMove = (rand() % 4 != 0) ? true : false;
		st[i].byMove = (rand() % 2 != 0) ? true : false;
		st[i].bzMove = (rand() % 4 != 0) ? true : false;
		st[i].Score = (rand() % 10 + 10) * 5;
		float col = rand() % 180;
		float gcol = rand() % (255 - (int)col - 40) + (int)col + 40;
		col /= 128;
		st[i].Color.x = col;
		st[i].Color.z = col;
		st[i].Color.y = gcol / 128;
	}
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Initialize(st[i]);
	}
	InitializeCamera();
	//シェーダーエフェクト作成
	m_ShadowMap.Create(2048);
	//シャドウマップのパラメーター設定
	m_ShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);
}

void CSceneGame::InitializeCamera() {
	m_vPos = CVector3(0.0135f, 23.1420f, 1.8235f);
	m_vTrans = CVector3(0.0136f, 22.1426f, 1.859f);
	//カメラ初期化
	m_Camera.SetViewPort();
	m_Camera.LookAt(m_vPos, m_vTrans, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Camera);

	//ライト初期化
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	m_Light.SetDiffuse(MOF_COLOR_HWHITE);
	m_Light.SetAmbient(MOF_COLOR_CBLACK);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

void CSceneGame::Update() {
	//各シーン状態に合わせた処理
	switch (gGamePhase)
	{
	case SS_INTRO:
		UpdateSS_INTRO();
		break;
	case SS_WAITTHROW:
		UpdateSS_WAITTHROW();
		break;
	case SS_PAUSE:
		UpdateSS_PAUSE();
		break;
	case SS_THROWING:
		//投てき中処理
		UpdateSS_THROWING();
		break;
	case SS_WAITTHROWRESULT:
		//投てき終了時処理
		UpdateSS_WAITTHROWRESULT();
		break;
	case SS_GAMERESULT:
		UpdateSS_GAMERESULT();
		break;
	case SS_GAMEEND:
		UpdateSS_GAMEEND();
		break;
	case SS_RETRY:
		UpdateSS_RETRY();
		break;
	}
	//UIアップデート処理
	gGameUIManager.UpdateUI();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Update();
	}
}

void CSceneGame::UpdateSS_INTRO() {
	//暗幕が上がるまで待機
	if (gGameUIManager.GameStartAnim())
	{
		gGamePhase = SS_WAITTHROW;
	}
}

void CSceneGame::UpdateSS_WAITTHROW() {
	//Tabキーでポーズ画面へ
	if (g_pInput->IsKeyPush(MOFKEY_TAB))
	{
		gGameUIManager.OpenPauseMenu();
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
		m_Flower[gCurrentFlowerCount].Fire(GetSpeed(gScoreResult.FlowerColor[gCurrentFlowerCount]));
		gGamePhase = SS_THROWING;
	}
}

void CSceneGame::UpdateSS_PAUSE() {
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
}

void CSceneGame::UpdateSS_THROWING() {
	m_Flower[gCurrentFlowerCount].Update();
	if (m_Flower[gCurrentFlowerCount].IsDead())
	{
		gGamePhase = SS_WAITTHROWRESULT;
		return;
	}
	for (int i = 0; i < 5; i++)
	{
		if (m_Target[i].Collision(m_Flower[gCurrentFlowerCount], i))
		{
			gScoreResult.score += m_Target[i].GetScore();
			gGamePhase = SS_WAITTHROWRESULT;
			return;
		}
	}
}

void CSceneGame::UpdateSS_WAITTHROWRESULT() {
	//投げた本数を＋１し、既定の本数投げ終えたらゲームを終了する
	gCurrentFlowerCount++;
	if (gCurrentFlowerCount >= FLOWERCOUNT)
	{
		gGamePhase = SS_GAMERESULT;
		return;
	}
	gGamePhase = SS_WAITTHROW;
}

void CSceneGame::UpdateSS_GAMERESULT() {
	if (gGameUIManager.ResultSlideIn())
	{
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			gGamePhase = SS_GAMEEND;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_X))
		{
			gGamePhase = SS_RETRY;
		}
	}
}

void CSceneGame::UpdateSS_GAMEEND() {
	//すべて投げ終わったらゲーム終了
		//暗幕が下りるまで待機
	if (gGameUIManager.GameEndAnim())
	{
		m_bEnd = true;
		m_NextScene = SCENETYPE_TITLE;
	}
}

void CSceneGame::UpdateSS_RETRY() {
	//ポーズメニューでリトライ選択時
		//暗幕が下りるまで待機
	if (gGameUIManager.GameEndAnim())
	{
		gGamePhase = SS_INTRO;
		this->Release();
		this->Initialize();
	}
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);


	CGraphicsUtilities::SetCamera(&m_Camera);

	//シェーダーエフェクトを使って描画
	if (m_EffectEnabled)
	{
		RenderUseShader();
	}
	//シェーダーエフェクトを使わずに描画
	else
	{
		//床描画用行列
		CMatrix44 matPlane;
		//matPlane.Scaling(50.0f);
		//床描画
		CGraphicsUtilities::RenderPlane(matPlane);
		//シーン描画
		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	g_pGraphics->SetDepthEnable(FALSE);

	//UIの描画
	gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderUseShader() {
	//床描画用行列
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);
	g_pGraphics->SetBlending(BLEND_NONE);

	m_ShadowMap.BeginTexture();
	{
		g_pGraphics->ClearTarget();

		//CGraphicsUtilities::RenderPlane(matPlane);

		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	m_ShadowMap.EndTexture();

	g_pGraphics->SetBlending(BLEND_NORMAL);

	m_ShadowMap.BeginRenderer();
	{
		g_pGraphics->ClearTarget(0.9f, 0.9f, 0.9f, 0.0f, 1.0f, 0);
		//床描画
		//CGraphicsUtilities::RenderPlane(matPlane);
		//シーン描画
		RenderFlower();
		for (int i = 0; i < 5; i++)
		{
			m_Target[i].Render();
		}
	}
	m_ShadowMap.EndRenderer();
}

void CSceneGame::RenderFlower() {
	int cnt = min(FLOWERCOUNT - 1, gCurrentFlowerCount);
	for (int i = 0; i <= cnt; i++)
	{
		if (m_Flower[i].IsDead()) { continue; }
		int no = m_Flower[i].GetNo();
		if (no != -1)
			m_Flower[i].Render(m_Target[no].GetPos());
		else
			m_Flower[i].Render();
	}
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {
	gGameUIManager.ReleaseUI();
	if (gScoreResult.FlowerPos)
	{
		delete[] gScoreResult.FlowerPos;
		gScoreResult.FlowerPos = NULL;
	}
	if (gScoreResult.FlowerColor)
	{
		delete[] gScoreResult.FlowerColor;
		gScoreResult.FlowerColor = NULL;
	}
}

float CSceneGame::GetSpeed(int type) {
	switch (type)
	{
	case 0:
		return 1.0f;
	case 1:
		return 2.0f;
	case 2:
		return 0.6f;
	}
	return 1.0f;
}