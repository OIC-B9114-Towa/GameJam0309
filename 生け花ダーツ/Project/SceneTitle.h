#pragma once
#include "SceneBase.h"

class CScenTitle : public CSceneBase
{
private:

public:
	CScenTitle();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};


