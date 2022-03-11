#include "Flower.h"

CFlower::CFlower() :
	m_Camera(),
	m_CameraAngle(0),
	m_Parts(),
	m_CentralPos(),
	m_Pos(0, 0, 0),
	m_Rotate(0, 0, 0),
	m_MoveZ(0),
	m_bFire(false),
	m_MaxLife(180),
	m_Life(0) {
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

	m_Parts.Count = atoi(pstr);
	pstr = strtok(NULL, ",");

	m_Parts.Count = min(30, m_Parts.Count);

	for (int i = 0; i < m_Parts.Count; i++)
	{
		m_Parts.Parts[i].PartsNo = i;
		m_Parts.Parts[i].Scale.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Scale.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Scale.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Translate.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Translate.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Translate.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Color.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Color.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Color.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_Parts.Parts[i].Color.w = 1;
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

void CFlower::Initialize() {
	InitializePos();
	InitializeParts();

	m_vPos = CVector3(0.0135f, 23.1420f, 1.8235f);
	m_vTrans = CVector3(0.0136f, 22.1426f, 1.859f);
	m_Camera.SetViewPort();
	m_Camera.LookAt(m_vPos, m_vTrans, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	m_Camera.Update();
}

void CFlower::InitializeParts() {
	CVector3 startpos(0, 0, 0);
	CVector3 endpos(0, 0, 0);

	for (int i = 0; i < m_Parts.Count; i++)
	{
		startpos.x = min(startpos.x, m_Parts.Parts[i].Translate.x);
		startpos.y = min(startpos.y, m_Parts.Parts[i].Translate.y);
		startpos.z = min(startpos.z, m_Parts.Parts[i].Translate.z);
		endpos.x = max(endpos.x, m_Parts.Parts[i].Translate.x);
		endpos.y = max(endpos.y, m_Parts.Parts[i].Translate.y);
		endpos.z = max(endpos.z, m_Parts.Parts[i].Translate.z);
	}

	m_CentralPos = (startpos + endpos) / 2;

	for (int i = 0; i < m_Parts.Count; i++)
	{
		m_Parts.Parts[i].Translate -= m_CentralPos;
	}
}

void CFlower::InitializePos() {
	m_Pos = CVector3(0, 15, 0);
	m_Rotate = CVector3(0, 0, 0);
	m_MoveZ = 0.05f;
	m_Life = m_MaxLife;
	m_bFire = false;
}

void CFlower::Update() {
	UpdateCamera();
	if (!m_bFire) { return; }

	float speed = 0.2f;

	m_Pos.y -= speed;
	m_MoveZ = max(m_MoveZ - 0.002f, -0.02f);

	m_Pos.z += m_MoveZ;

	m_Life--;
	if (m_Life < 0)
	{
		InitializePos();
	}

}

void CFlower::UpdateCamera() {
	//カメラの設定
	CVector3 cpos = m_Pos;
	CVector3 tpos = m_Pos;
	CVector3 fvec(0, 0, -1);
	fvec.RotationY(m_CameraAngle);
	cpos.y += 3.0f;
	cpos -= fvec * 3.2f;
	tpos += fvec * 1.5f;
	tpos.y += -1;
	m_Camera.LookAt(cpos, tpos, CVector3(0, 1, 0));
	m_Camera.Update();
}

void CFlower::Fire() {
	m_bFire = true;
}

void CFlower::Hit() {
	m_bFire = false;
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

	for (int i = 0; i < m_Parts.Count; i++)
	{
		CBoxOBB box(m_Pos + m_Parts.Parts[i].Translate, m_Parts.Parts[i].Scale, m_Rotate);

		CGraphicsUtilities::RenderBox(box, m_Parts.Parts[i].Color);
	}
}

void CFlower::RenderDebug() {

}

void CFlower::Release() {

}

void CFlower::SetCameraEnable() {
	CGraphicsUtilities::SetCamera(&m_Camera);
}