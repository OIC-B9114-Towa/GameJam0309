#include "GameUIManager.h"
CGameUIManager::CGameUIManager() :
	gScoreBackTexture(),
	gWindIconTexture(),
	gFlowerIconTexture(),
	gCurrentFlowerBackTexture(),
	gScoreResult()
{}

CGameUIManager::~CGameUIManager() {
}

void CGameUIManager::Initialize() {
	//画像の読み込み
	gScoreBackTexture.Load("");
	gWindIconTexture.Load("");
	gFlowerIconTexture.Load("");
	gCurrentFlowerBackTexture.Load("");

	//スコアの初期化
	gScoreResult = Result();
	gScoreResult.score = 0;

	//乱数の初期化
	std::srand(time(NULL));
	//花の初期化
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//スコア記録用構造体を初期化
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % TYPE_COUNT;		
		
		//方向と速度をランダムで算出し、記録する
		gWind[i].gWindDirect = rand() % DIRECT_COUNT;
		int wPower = rand() % MAXWINDPOWER;
		gWind[i].gWindPower = wPower;
		gWind[i].gWindPowerToVector
			= CVector3(wPower * cos(45 * gWind[i].gWindDirect), wPower * sin(45 * gWind[i].gWindDirect), 0);
	}
}
void CGameUIManager::UpdateUI() {

}
void CGameUIManager::RenderUI() {

}
void CGameUIManager::ReleaseUI() {

}