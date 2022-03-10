#pragma once
#include "SceneBase.h"
#include "Flower.h"

class CSceneGame : public CSceneBase
{
private:
	CFlower m_Flower;
public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

