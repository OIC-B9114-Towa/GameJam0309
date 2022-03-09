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
	//�摜�̓ǂݍ���
	gScoreBackTexture.Load("");
	gWindIconTexture.Load("");
	gFlowerIconTexture.Load("");
	gCurrentFlowerBackTexture.Load("");

	//�X�R�A�̏�����
	gScoreResult = Result();
	gScoreResult.score = 0;

	//�����̏�����
	std::srand(time(NULL));
	//�Ԃ̏�����
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//�X�R�A�L�^�p�\���̂�������
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % TYPE_COUNT;		
		
		//�����Ƒ��x�������_���ŎZ�o���A�L�^����
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