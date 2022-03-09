#pragma once
#include "SceneBase.h"
class CSceneOption : public CSceneBase
{
private:

public:
	CSceneOption();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

