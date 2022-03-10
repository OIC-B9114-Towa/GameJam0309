#include "SceneGame.h"

CSceneGame::CSceneGame() {

}

void CSceneGame::Initialize() {

	//�X�R�A�A���f�[�^�̏�����
	gScoreResult = CInGameData::Result{0, new CVector3[FLOWERCOUNT], new int[FLOWERCOUNT]};
	gWind = new CInGameData::Wind[FLOWERCOUNT]{ 0, 0, CVector3(0, 0, 0) };
	//�����̏�����
	std::srand(time(NULL));
	//�Ԃ̏�����
	for (int i = 0; i < FLOWERCOUNT; i++)
	{
		//�X�R�A�L�^�p�\���̂�������
		gScoreResult.FlowerPos[i] = CVector3(0, 0, 0);
		gScoreResult.FlowerColor[i] = rand() % CInGameData::TYPE_COUNT;

		//�����Ƒ��x�������_���ŎZ�o���A�L�^����
		gWind[i].gWindDirect = rand() % CInGameData::DIRECT_COUNT;
		int wPower = rand() % MAXWINDPOWER;
		gWind[i].gWindPower = wPower;
		gWind[i].gWindPowerToVector
			= CVector3(wPower * cos(45 * gWind[i].gWindDirect), wPower * sin(45 * gWind[i].gWindDirect), 0);
	}
	gGameUIManager.Initialize();
}

void CSceneGame::Update() {
	//�e�V�[����Ԃɍ��킹������
	switch (gGamePhase)
	{
	case INTRO:
		if (gGameUIManager.GameStartAnim())
		{
			gGamePhase = WAITTHROW;
		}
		break;
	case WAITTHROW:
		//�����I�������uTHROWING�v�t�F�[�Y�ֈڍs
		break;
	case PAUSE:
		//�|�[�Y��(�uWAITTHROW�v����J��)
		break;
	case THROWING:
		//���Ă�������
		break;
	case WAITTHROWRESULT:
		//���Ă��I��������


		//�������{�����{�P���A����̖{�������I������Q�[�����I������
		gCurrentFlowerCount++;
		if (gCurrentFlowerCount >= FLOWERCOUNT)
		{
			gGamePhase = GAMEEND;
		}
		break;
	case GAMEEND:
		//���ׂē����I�������Q�[���I��
		break;
	}
}

void CSceneGame::UpdateDebug() {

}

void CSceneGame::Render() {

	//UI�̕`��
	//gGameUIManager.RenderUI(gCurrentFlowerCount, FLOWERCOUNT, &gScoreResult);
}

void CSceneGame::RenderDebug() {

}

void CSceneGame::Release() {

}