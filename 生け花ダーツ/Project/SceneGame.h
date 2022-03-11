#pragma once
#include "SceneBase.h"
#include "Flower.h"
#include "Target.h"
#include	<Graphics/ShaderEffect_ShadowMap.h>

class CSceneGame : public CSceneBase
{
private:
	CFlower m_Flower;
	CTarget m_Target[5];

	//カメラ
	CCamera						m_Camera;

	CVector3 m_vPos;
	CVector3 m_vTrans;

	//カメラ角度
	CVector3					m_CamAngle;
	//ライト
	CDirectionalLight			m_Light;
	//シャドウマップシェーダー
	CShaderEffect_ShadowMap		m_ShadowMap;
	//シェーダーエフェクト有効フラグ
	bool							m_EffectEnabled;

	void InitializeCamera();
	void UpdateCamera();
	void RenderUseShader();
	void RenderFlower();
public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

