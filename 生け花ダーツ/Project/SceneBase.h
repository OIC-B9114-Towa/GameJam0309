#pragma once
#include <Mof.h>
#include "SceneType.h"

class CSceneBase
{
private:
protected:

	bool				m_bEnd;
	SceneType				m_NextScene;
	int					m_SelectNo;
public:
	CSceneBase();
	virtual ~CSceneBase() {};
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void UpdateDebug(void) = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;

	SceneType GetNextScene(void) { return m_NextScene; }
	int GetStageNo() { return m_SelectNo; }
	int SetStageNo(int i) { return m_SelectNo = i; }
	bool IsEnd(void) { return m_bEnd; }
};