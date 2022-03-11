#include "SceneEditor.h"

CSceneEditor::CSceneEditor() :
	m_Camera(),
	m_EditCamera(),
	m_CamAngle(),
	m_Light(),
	m_ShadowMap(),
	m_EffectEnabled(false),
	m_BoxStatus(),
	m_Menu(),
	m_SelectPartsNo(0),
	m_bTranslucent(true) {

}

CSceneEditor::~CSceneEditor() {
	Release();
}

void CSceneEditor::Initialize() {
	InitializeCamera();
	//�V�F�[�_�[�G�t�F�N�g�쐬
	m_ShadowMap.Create(2048);
	//�V���h�E�}�b�v�̃p�����[�^�[�ݒ�
	m_ShadowMap.SetShadowMapParam(50.0f, -10.0f, 50.0f, 0.003f);
	LoadBoxStatus();
	m_Menu.Initialize();
	SetMenuStatus();
	SubMenuSetButton();
}

void CSceneEditor::InitializeCamera() {
	//�J����������
	m_Camera.SetViewPort();
	m_Camera.Update();
	//�J����������
	m_EditCamera.SetViewPort(0, 0, 1024, 768);
	m_EditCamera.LookAt(Vector3(0.0f, 3.0f, -2.0f), Vector3(0, 0, 0), Vector3(0, 1, 0));
	m_EditCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	m_EditCamera.Update();
	CGraphicsUtilities::SetCamera(&m_EditCamera);

	//���C�g������
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	m_Light.SetDiffuse(MOF_COLOR_HWHITE);
	m_Light.SetAmbient(MOF_COLOR_CBLACK);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

void CSceneEditor::SetMenuStatus() {
	std::string textboxno[9];

	textboxno[0] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Translate.x * 100));
	textboxno[1] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Translate.y * 100));
	textboxno[2] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Translate.z * 100));
	textboxno[3] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Scale.x * 100));
	textboxno[4] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Scale.y * 100));
	textboxno[5] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Scale.z * 100));
	textboxno[6] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Color.x * 100));
	textboxno[7] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Color.y * 100));
	textboxno[8] = std::to_string((int)(m_BoxStatus[m_SelectPartsNo].Color.z * 100));

	m_Menu.UpdateTextBoxText(textboxno, 9);
}

void CSceneEditor::SubMenuSetButton() {
	int cnt = m_BoxStatus.size();
	ButtonStatus* bs = new ButtonStatus[cnt * 2];

	for (int i = 0; i < cnt; i++)
	{
		if (i == m_SelectPartsNo)
		{
			bs[2 * i].SurfaceColor = MOF_COLOR_HRED;
			bs[2 * i].SelectSurfaceColor = MOF_COLOR_HRED;
		}
		bs[2 * i].Size = CVector2(100, 40);
		bs[2 * i].Pos = CVector2(20, 20 + i * 60);
		bs[2 * i].Text = "�p�[�c" + std::to_string(i + 1);
		bs[2 * i + 1].Size = CVector2(40, 40);
		bs[2 * i + 1].Pos = CVector2(130, 20 + i * 60);
		bs[2 * i + 1].Text = "�~";
	}

	m_Menu.GetSubMenu(0)->SetButton(bs, cnt * 2);
	delete[] bs;
	bs = NULL;
}

void CSceneEditor::Update() {
	Vector2 mpos;
	g_pInput->GetMousePos(mpos);
	UpdateMenuMouse(mpos);
	UpdateMenuKeyboard();
	UpdateBoxStatus();

	if (mpos.x < 1024)
		UpdateCamera();

	//�V�F�[�_�[�G�t�F�N�gON/OFF�؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_EffectEnabled = !m_EffectEnabled;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		LoadBoxStatus();
		SubMenuSetButton();
	}
}

void CSceneEditor::UpdateCamera() {
	//�}�E�X�ɂ��J������]
	CVector3 vRot;
	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		g_pInput->GetMouseMove(vRot);
		vRot *= 0.005f;
	}
	m_CamAngle += Vector3(vRot.y, vRot.x, 0);

	//�J�����̌������v�Z
	CMatrix33 matRot;
	matRot.RotationZXY(m_CamAngle);
	CVector3 vFront(0, 0, 1);
	vFront.TransformCoord(matRot, vFront);

	//�L�[�ɂ��J�����ړ�
	float speed = 0.1;
	CVector3 vMove;
	CVector3 mMove;
	float mwheel = g_pInput->GetMouseWheelMove();
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vMove.x -= speed;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vMove.x += speed;
	}
	else if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
	{
		g_pInput->GetMouseMove(mMove);
		mMove *= 0.005f;
		vMove.x -= mMove.x;
		vMove.y += mMove.y;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		vMove.z -= speed;
	}
	else if (mwheel < 0)
	{
		vMove.z -= speed * 2;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		vMove.z += speed;
	}
	else if (mwheel > 0)
	{
		vMove.z += speed * 2;
	}

	vMove.TransformCoord(matRot, vMove);
	CVector3 vPos = m_EditCamera.GetViewPosition() + vMove;

	//�J�����X�V
	m_EditCamera.LookAt(vPos, vPos + vFront, Vector3(0, 1, 0));
	m_EditCamera.Update();
}

void CSceneEditor::UpdateMenuKeyboard() {
	CInputManager::GetInstance().SelectVertical(0, m_SelectNo, m_Menu.GetRangeNo(), 0);
	m_Menu.SelectButton(m_SelectNo);
	m_Menu.InputText(m_SelectNo);
	if (CInputManager::GetInstance().GetPush(0, 1) || CInputManager::GetInstance().GetPush(0, 8))
	{
		UpdateMenuResult();
	}
}

void CSceneEditor::UpdateMenuMouse(Vector2 vec) {
	m_Menu.Update();
	int no = m_Menu.Collision(vec);
	if (no == -1) { return; }
	m_SelectNo = no;
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		UpdateMenuResult();
	}
}

void CSceneEditor::UpdateMenuResult() {
	int no = m_Menu.GetSubMenuGetRange(0);
	if (m_SelectNo < no)
	{
		if (m_SelectNo % 2 == 0)
		{
			m_SelectPartsNo = m_SelectNo / 2;
			SetMenuStatus();
			SubMenuSetButton();
			return;
		}
		else
		{
			if (m_SelectPartsNo == m_BoxStatus.size() - 1)
			{
				m_SelectPartsNo = 0;
			}
			int delno = (m_SelectNo - 1) / 2;
			m_BoxStatus.erase(m_BoxStatus.begin() + delno);
			SubMenuSetButton();
			return;
		}
	}
	no = m_Menu.ChangeButtonNo(m_SelectNo);
	if (no == 0)
	{
		m_BoxStatus.push_back(BoxStatus());
		SubMenuSetButton();
	}
	else if (no == 1)
	{
		m_bTranslucent = !m_bTranslucent;
	}
	else if (no == 2)
	{
		SaveBoxStatus();
	}
}

void CSceneEditor::UpdateBoxStatus() {
	m_BoxStatus[m_SelectPartsNo].Translate.x = atoi(m_Menu.GetTextBoxText(0).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Translate.y = atoi(m_Menu.GetTextBoxText(1).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Translate.z = atoi(m_Menu.GetTextBoxText(2).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Scale.x = atoi(m_Menu.GetTextBoxText(3).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Scale.y = atoi(m_Menu.GetTextBoxText(4).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Scale.z = atoi(m_Menu.GetTextBoxText(5).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Color.x = atoi(m_Menu.GetTextBoxText(6).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Color.y = atoi(m_Menu.GetTextBoxText(7).c_str()) * 0.01f;
	m_BoxStatus[m_SelectPartsNo].Color.z = atoi(m_Menu.GetTextBoxText(8).c_str()) * 0.01f;
}

void CSceneEditor::UpdateDebug() {

}

void CSceneEditor::Render() {
	CGraphicsUtilities::SetCamera(&m_EditCamera);

	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);

	//�V�F�[�_�[�G�t�F�N�g���g���ĕ`��
	if (m_EffectEnabled)
	{
		RenderUseShader();
	}
	//�V�F�[�_�[�G�t�F�N�g���g�킸�ɕ`��
	else
	{
		//���`��p�s��
		CMatrix44 matPlane;
		matPlane.Scaling(50.0f);
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		RenderScene();
	}

	CGraphicsUtilities::SetCamera(&m_Camera);
	g_pGraphics->SetDepthEnable(FALSE);

	CGraphicsUtilities::RenderString(10, 10, "�㉺�L�[�E�}�E�X�z�C�[���ŃJ�����O��ړ�");
	CGraphicsUtilities::RenderString(10, 34, "���E�L�[�E�}�E�X�E�h���b�O�ŃJ�����㉺���E�ړ�");
	CGraphicsUtilities::RenderString(10, 58, "�}�E�X���h���b�O�ŃJ������]");
	CGraphicsUtilities::RenderString(10, 82, "SPACE�L�[�ŃV���h�E�}�b�v�K�p %s", m_EffectEnabled ? "ON" : "OFF");
	CGraphicsUtilities::RenderString(10, 104, "ENTER�L�[�ŃI�u�W�F�N�g�ēǂݍ���");

	m_Menu.Render();
}

void CSceneEditor::RenderDebug() {

}

void CSceneEditor::RenderUseShader() {
	//���`��p�s��
	CMatrix44 matPlane;
	matPlane.Scaling(50.0f);
	g_pGraphics->SetBlending(BLEND_NONE);

	m_ShadowMap.BeginTexture();
	{
		g_pGraphics->ClearTarget();

		CGraphicsUtilities::RenderPlane(matPlane);

		RenderScene();
	}
	m_ShadowMap.EndTexture();

	g_pGraphics->SetBlending(BLEND_NORMAL);

	m_ShadowMap.BeginRenderer();
	{
		g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
		//���`��
		CGraphicsUtilities::RenderPlane(matPlane);
		//�V�[���`��
		RenderScene();
	}
	m_ShadowMap.EndRenderer();
}

void CSceneEditor::Release() {
	m_ShadowMap.Release();
	m_Menu.Release();
}

void CSceneEditor::RenderScene() {
	//�l�X�ȃv���~�e�B�u����ׂ�
	CMatrix44 matWorld;

	for (int i = 0; i < m_BoxStatus.size(); i++)
	{
		CBoxOBB box(m_BoxStatus[i].Translate, m_BoxStatus[i].Scale, CVector3(0, 0, 0));

		CVector4 color = m_BoxStatus[i].Color;
		if (m_SelectPartsNo != i && m_bTranslucent)
			color.w = 0.3f;
		CGraphicsUtilities::RenderBox(box, color);
	}
}

bool CSceneEditor::LoadBoxStatus() {
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

	int boxcnt = atoi(pstr);
	pstr = strtok(NULL, ",");

	for (int i = 0; i < boxcnt; i++)
	{
		m_BoxStatus.push_back(BoxStatus());
		m_BoxStatus[i].Scale.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Scale.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Translate.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Color.x = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Color.y = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Color.z = atof(pstr);
		pstr = strtok(NULL, ",");
		m_BoxStatus[i].Color.w = 1;
	}

	fclose(fp);
	free(pBuffer);
	return true;
}

bool CSceneEditor::SaveBoxStatus() {
	FILE* fp = fopen("BoxStatus.txt", "wt");
	if (!fp) { return false; }

	fprintf(fp, "%d,\n\n", m_BoxStatus.size());

	for (int i = 0; i < m_BoxStatus.size(); i++)
	{
		fprintf(fp, "%f,%f,%f,\n", m_BoxStatus[i].Scale.x, m_BoxStatus[i].Scale.y, m_BoxStatus[i].Scale.z);
		fprintf(fp, "%f,%f,%f,\n", m_BoxStatus[i].Translate.x, m_BoxStatus[i].Translate.y, m_BoxStatus[i].Translate.z);
		fprintf(fp, "%f,%f,%f,\n\n", m_BoxStatus[i].Color.x, m_BoxStatus[i].Color.y, m_BoxStatus[i].Color.z);
	}
	fclose(fp);
}