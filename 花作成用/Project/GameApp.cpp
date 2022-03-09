/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

//カメラ
CCamera						gCamera;
//カメラ角度
CVector3					gCamAngle;
//ライト
CDirectionalLight			gLight;
//シャドウマップシェーダー
CShaderEffect_ShadowMap		gShadowMap;
//シェーダーエフェクト有効フラグ
bool							gEffectEnabled = true;

typedef struct tag_BoxStatus
{
	CVector3 Scale;
	CVector3 Translate;
	tag_BoxStatus() :
		Scale(),
		Translate()
	{
	}
}BoxStatus;

std::vector<BoxStatus> m_BoxStatus;

/**
 * シーン描画
 */
void RenderScene() {
	//様々なプリミティブを並べる
	CMatrix44 matWorld;

	for (int i = 0; i < m_BoxStatus.size(); i++)
	{
		matWorld.Scaling(m_BoxStatus[i].Scale);
		matWorld.SetTranslation(m_BoxStatus[i].Translate);
		CGraphicsUtilities::RenderBox(matWorld);
	}
}

bool LoadBoxStatus() {
	FILE* fp = fopen("BoxStatus.txt", "rb");
	if (!fp) { return false; }

	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");

	int boxcnt = atoi(pstr);
	pstr = strtok(NULL, ",");

	for (int i = 0; i < boxcnt; i++)
	{
		m_BoxStatus.push_back(BoxStatus());
		m_BoxStatus[i].Scale.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.z = atof(pstr);
		pstr = strtok(NULL, ",");
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//カメラ初期化
	//カメラ初期化
	gCamera.SetViewPort();
	gCamera.LookAt(Vector3(0.0f, 3.0f, -2.0f), Vector3(0, 0, 0), Vector3(0, 1, 0));
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	gCamera.Update();
	CGraphicsUtilities::SetCamera(&gCamera);

	//ライト初期化
	gLight.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	gLight.SetDiffuse(MOF_COLOR_HWHITE);
	gLight.SetAmbient(MOF_COLOR_CBLACK);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	//シェーダーエフェクト作成
	gShadowMap.Create(2048);

	//シャドウマップのパラメーター設定
	gShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);

	LoadBoxStatus();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	//マウスによるカメラ回転
	CVector3 vRot;
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		g_pInput->GetMouseMove(vRot);
		vRot *= 0.005f;
	}
	gCamAngle += Vector3(vRot.y, vRot.x, 0);

	//カメラの向きを計算
	CMatrix33 matRot;
	matRot.RotationZXY(gCamAngle);
	CVector3 vFront(0, 0, 1);
	vFront.TransformCoord(matRot, vFront);

	//キーによるカメラ移動
	float speed = 0.1f;
	CVector3 vMove;
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vMove.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vMove.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		vMove.z -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		vMove.z += speed;
	}
	vMove.TransformCoord(matRot, vMove);
	CVector3 vPos = gCamera.GetViewPosition() + vMove;

	//カメラ更新
	gCamera.LookAt(vPos, vPos + vFront, Vector3(0, 1, 0));
	gCamera.Update();

	//シェーダーエフェクトON/OFF切り替え
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		gEffectEnabled = !gEffectEnabled;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		LoadBoxStatus();
	}

	return TRUE;
}

/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画処理
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);

	//床描画用行列
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);

	//シェーダーエフェクトを使って描画
	if (gEffectEnabled)
	{
		g_pGraphics->SetBlending(BLEND_NONE);

		gShadowMap.BeginTexture();
		{
			g_pGraphics->ClearTarget();

			CGraphicsUtilities::RenderPlane(matPlane);

			RenderScene();
		}
		gShadowMap.EndTexture();

		g_pGraphics->SetBlending(BLEND_NORMAL);

		gShadowMap.BeginRenderer();
		{
			g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
			//床描画
			CGraphicsUtilities::RenderPlane(matPlane, CVector4(0, 0.5f, 0.5f, 1));
			//シーン描画
			RenderScene();
		}
		gShadowMap.EndRenderer();
	}
	//シェーダーエフェクトを使わずに描画
	else
	{
		//床描画
		CGraphicsUtilities::RenderPlane(matPlane, CVector4(0, 0.5f, 0.5f, 1));

		//シーン描画
		RenderScene();
	}

	CGraphicsUtilities::RenderString(10, 10, "上下左右キーでカメラ移動");
	CGraphicsUtilities::RenderString(10, 34, "マウス左ドラッグでカメラ回転");
	CGraphicsUtilities::RenderString(10, 58, "SPACEキーでシャドウマップ適用 %s", gEffectEnabled ? "ON" : "OFF");

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	//シェーダーエフェクト解放
	gShadowMap.Release();
	return TRUE;
}