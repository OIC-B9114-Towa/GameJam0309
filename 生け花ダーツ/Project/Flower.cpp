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
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");

	m_PartsCount = atoi(pstr);
	pstr = strtok(NULL, ",");

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

}

void CFlower::Release() {

}