#include "SceneBase.h"

CSceneBase::CSceneBase() :
	m_bEnd(false),
	m_NextScene(SceneType::SCENETYPE_TITLE),
	m_SelectNo(0) {
}