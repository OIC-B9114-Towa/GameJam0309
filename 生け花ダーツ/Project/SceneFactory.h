#pragma once
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneOption.h"
#include "SceneCollection.h"

class CSceneFactory
{
public:
	CSceneBase* CreateScene(SceneType scene_type) {
		switch (scene_type)
		{
		case SCENETYPE_TITLE:
			return new CSceneTitle();
		case SCENETYPE_GAME:
			return new CSceneGame();
		case SCENETYPE_OPTION:
			return new CSceneOption();
		case SCENETYPE_COLLECTION:
			return new CSceneCollection();
		default:
			break;
		}
		return nullptr;
	}
};