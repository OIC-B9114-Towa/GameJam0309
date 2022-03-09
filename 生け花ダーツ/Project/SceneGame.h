#pragma once
#include "SceneBase.h"
class CSceneGame : public CSceneBase
{
private:

public:
	CSceneGame();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

