#pragma once
#include "SceneBase.h"
class CSceneCollection : public CSceneBase
{
private:

public:
	CSceneCollection();
	void Initialize(void);
	void Update(void);
	void UpdateDebug(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

