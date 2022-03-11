#include "Flower.h"

CFlower::CFlower() :
	m_PartsCount(0),
	m_Parts(),
	m_CentralPos(),
	m_Pos(),
	m_Rotate(){
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

	m_PartsCount = min(30, m_PartsCount);

	for (int i = 0; i < m_PartsCount; i++)
	{
		m_Parts[i].PartsNo = i;
		m_Parts[i].Scale.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Scale.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Scale.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Translate.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts[i].Color.w = 1;
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

void CFlower::Initialize() {

	CVector3 startpos(0, 0, 0);
	CVector3 endpos(0, 0, 0);

	for (int i = 0; i < m_PartsCount; i++)
	{
		startpos.x = min(startpos.x, m_Parts[i].Translate.x);
		startpos.y = min(startpos.y, m_Parts[i].Translate.y);
		startpos.z = min(startpos.z, m_Parts[i].Translate.z);
		endpos.x = max(endpos.x, m_Parts[i].Translate.x);
		endpos.y = max(endpos.y, m_Parts[i].Translate.y);
		endpos.z = max(endpos.z, m_Parts[i].Translate.z);
	}

	m_CentralPos = (startpos + endpos) / 2;

	for (int i = 0; i < m_PartsCount; i++)
	{
		m_Parts[i].Translate -= m_CentralPos;
	}
}

void CFlower::Update() {

}

void CFlower::UpdateDebug() {
	float speed = 0.125f;
	if (g_pInput->IsKeyHold(MOFKEY_Q))
	{
		m_Pos.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_Pos.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		m_Pos.y += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		m_Pos.y -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_E))
	{
		m_Pos.z += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_Pos.z -= speed;
	}

	if (g_pInput->IsKeyHold(MOFKEY_U))
	{
		m_Rotate.x += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_J))
	{
		m_Rotate.x -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_I))
	{
		m_Rotate.y += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_K))
	{
		m_Rotate.y -= speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_O))
	{
		m_Rotate.z += speed;
	}
	if (g_pInput->IsKeyHold(MOFKEY_L))
	{
		m_Rotate.z -= speed;
	}
}

void CFlower::Render() {
	//様々なプリミティブを並べる
	CMatrix44 matWorld;

	for (int i = 0; i < m_PartsCount; i++)
	{
		CMatrix44 matTrans;
		CMatrix44 matRot;

		CVector3 pos = m_Parts[i].Translate + m_Pos;
		CVector3 rot = m_Rotate;

		matTrans.SetTranslation(pos);
		matRot.RotationXYZ(rot);
		matWorld.Scaling(m_Parts[i].Scale);
		matWorld *= matTrans;
		matWorld *= matRot;
		CGraphicsUtilities::RenderBox(matWorld, m_Parts[i].Color);
	}
}

void CFlower::Release() {

}