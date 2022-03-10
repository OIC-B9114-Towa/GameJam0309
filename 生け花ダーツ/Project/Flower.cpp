#include "Flower.h"

CFlower::CFlower() :
	m_PartsCount(0),
	m_Parts(){
}

CFlower::~CFlower() {

}

bool CFlower::Load() {
	FILE* fp = fopen("BoxStatus.txt", "rb");
	if (!fp) { return false; }

	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");

	m_PartsCount = atoi(pstr);
	pstr = strtok(NULL, ",");

	m_PartsCount = min(30, m_PartsCount);

	for (int i = 0; i < m_PartsCount; i++) 
	{
		m_Parts[i].PartsNo = i;
		m_Parts[i].Scale.x = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Scale.y = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Scale.z = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.x = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.y = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.z = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.x = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.y = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.z = atoi(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.z = 1;
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

void CFlower::Initialize() {

}

void CFlower::Update() {

}

void CFlower::Render() {
	//�l�X�ȃv���~�e�B�u����ׂ�
	CMatrix44 matWorld;

	for (int i = 0; i < m_PartsCount; i++)
	{
		matWorld.Scaling(m_Parts[i].Scale);
		matWorld.SetTranslation(m_Parts[i].Translate);
		CGraphicsUtilities::RenderBox(matWorld, m_Parts[i].Color);
	}
}

void CFlower::Release() {

}