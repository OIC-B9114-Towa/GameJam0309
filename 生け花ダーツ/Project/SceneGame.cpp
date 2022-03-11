#include "SceneGame.h"

CSceneGame::CSceneGame() :
	m_Flower(),
	m_Target(),
	m_vPos(),
	m_vTrans() {

}

void CSceneGame::Initialize() {
	m_Flower.Load();
	m_Flower.Initialize();

	TargetStatus st[5];
	st[0].Pos = CVector3(0, 2, 1);
	st[0].Scale = CVector3(1, 0.1f, 1);
	st[0].bxMove = true;
	st[1].Pos = CVector3(0, -5, 1);
	st[1].Scale = CVector3(0.5f, 0.1f, 0.5f);
	st[1].bzMove = true;
	st[2].Pos = CVector3(0, 2, 1);
	st[2].Scale = CVector3(1, 0.1f, 2);
	st[2].byMove = true;
	st[2].bxMove = true;
	st[3].Pos = CVector3(0, 2, 1);
	st[3].Scale = CVector3(2, 0.1f, 1);
	st[3].bzMove = true;
	st[4].Pos = CVector3(0, 2, 1);
	st[4].Scale = CVector3(1, 0.1f, 1);
	st[4].Pos = CVector3(0, 2, 1);
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
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_Flower.Fire();
	}
	m_Flower.Update();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].Update();
		m_Target[i].Collision(m_Flower, i);
	}
	//UpdateCamera();
}

void CSceneGame::UpdateCamera() {
	//マウスによるカメラ回転
	CVector3 vRot;
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		g_pInput->GetMouseMove(vRot);
		vRot *= 0.005f;
	}
	m_CamAngle += Vector3(vRot.y, vRot.x, 0);

	//カメラの向きを計算
	CMatrix33 matRot;
	matRot.RotationZXY(m_CamAngle);
	CVector3 vFront(0, 0, 1);
	vFront.TransformCoord(matRot, vFront);

	//キーによるカメラ移動
	float speed = 0.1;
	CVector3 vMove;
	CVector3 mMove;
	float mwheel = g_pInput->GetMouseWheelMove();
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vMove.x -= speed;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vMove.x += speed;
	}
	else if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
	{
		g_pInput->GetMouseMove(mMove);
		mMove *= 0.005f;
		vMove.x -= mMove.x;
		vMove.y += mMove.y;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		vMove.z -= speed;
	}
	else if (mwheel < 0)
	{
		vMove.z -= speed * 2;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		vMove.z += speed;
	}
	else if (mwheel > 0)
	{
		vMove.z += speed * 2;
	}

	vMove.TransformCoord(matRot, vMove);
	m_vPos = m_Camera.GetViewPosition() + vMove;
	m_vTrans = m_vPos + vFront;

	//カメラ更新
	m_Camera.LookAt(m_vPos, m_vTrans, Vector3(0, 1, 0));
	m_Camera.Update();
}

void CSceneGame::UpdateDebug() {
	m_Flower.UpdateDebug();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].UpdateDebug();
	}
}

void CSceneGame::Render() {
	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);

	if (m_Flower.GetFire())
	{
		//プレイヤーのカメラを有効にする
		//m_Flower.SetCameraEnable();
	}
	else
	{
		CGraphicsUtilities::SetCamera(&m_Camera);
	}

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

	CGraphicsUtilities::RenderString(10, 10, "上下キー・マウスホイールでカメラ前後移動");
	CGraphicsUtilities::RenderString(10, 34, "左右キー・マウス右ドラッグでカメラ上下左右移動");
	CGraphicsUtilities::RenderString(10, 58, "マウス左ドラッグでカメラ回転");
	CGraphicsUtilities::RenderString(10, 82, "SPACEキーでシャドウマップ適用 %s", m_EffectEnabled ? "ON" : "OFF");
	CGraphicsUtilities::RenderString(10, 106, "ENTERキーでオブジェクト再読み込み");
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
		g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
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
	int no = m_Flower.GetNo();
	if (no != -1)
		m_Flower.Render(m_Target[no].GetPos());
	else
		m_Flower.Render();
}

void CSceneGame::RenderDebug() {
	CGraphicsUtilities::RenderString(10, 130, "Debug : ON");
	m_Flower.RenderDebug();
	for (int i = 0; i < 5; i++)
	{
		m_Target[i].RenderDebug();
	}

	CGraphicsUtilities::RenderString(10, 154, "vPos x : %f, y : %f, z : %f", m_vPos.x, m_vPos.y, m_vPos.z);
	CGraphicsUtilities::RenderString(10, 178, "vTrans x : %f, y : %f, z : %f", m_vTrans.x, m_vTrans.y, m_vTrans.z);
}

void CSceneGame::Release() {
	m_Flower.Release();
}