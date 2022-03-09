#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:

public:
	CSceneTitle();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};


