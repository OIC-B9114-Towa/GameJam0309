#include "SceneCollection.h"

CSceneCollection::CSceneCollection()
{
}

void CSceneCollection::Initialize(void)
{
}

void CSceneCollection::Update(void)
{
}

void CSceneCollection::UpdateDebug(void)
{
}

void CSceneCollection::Render(void)
{
}

void CSceneCollection::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "コレクション画面");
}

void CSceneCollection::Release(void)
{
}
