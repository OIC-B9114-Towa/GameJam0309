#include "SceneGame.h"

CSceneGame::CSceneGame():
m_Flower(){

}

void CSceneGame::Initialize() {
	m_Flower.Load();
	m_Flower.Initialize();
}

void CSceneGame::Update() {
	m_Flower.Update();
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {
	m_Flower.Render();
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {
	m_Flower.Release();
}