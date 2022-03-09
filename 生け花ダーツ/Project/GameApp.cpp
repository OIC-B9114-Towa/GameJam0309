/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneFactory.h"

CSceneBase* g_pScene = NULL;

bool		g_bDebug = false;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	CSceneFactory factory;

	g_pScene = factory.CreateScene(SceneType::SCENETYPE_TITLE);
	g_pScene->Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = !g_bDebug;
	}

	g_pScene->Update();
	if (g_bDebug)
	{
		g_pScene->UpdateDebug();
	}

	int StageNo = 0;
	if (g_pScene->IsEnd())
	{
		SceneType change = g_pScene->GetNextScene();
		g_pScene->Release();
		delete g_pScene;
		g_pScene = NULL;

		CSceneFactory scene;
		g_pScene = scene.CreateScene(change);
		g_pScene->Initialize();
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(1.0f,1.0f,1.0f,1.0f,1.0f,0);

	g_pScene->Render();
	if (g_bDebug)
	{
		g_pScene->RenderDebug();
	}

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
MofBool CGameApp::Release(void){
	g_pScene->Release();
	if (g_pScene)
	{
		delete g_pScene;
		g_pScene = NULL;
	}
	return TRUE;
}