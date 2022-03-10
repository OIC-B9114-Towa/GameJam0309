#include "SceneTitle.h"

CSceneTitle::CSceneTitle() :
m_fileBuffer(NULL)
{

}

void CSceneTitle::LoadText()
{
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen("Text\\MenuDescription.txt", "rt");
	if (fp == NULL)
	{
		return;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);  //fp�̈ʒu���t�@�C���̏I�[��
	long fSize = ftell(fp);  //�t�@�C���̓ǂݏ����ʒu���擾�A�ʒu�ŗe�ʂ����߂�
	fseek(fp, 0, SEEK_SET);  //fp�̈ʒu���t�@�C���̐擪��
	//�t�@�C���̗e�ʕ��̃�������malloc�œ��I�Ɋm��
	m_fileBuffer = (char*)malloc(fSize + 1);  //�I�[��\0���܂߂邽�߁A+1
	//�o�b�t�@�Ƀt�@�C����S�ēǂݍ���
	fSize = fread(m_fileBuffer, 1, fSize, fp);
	m_fileBuffer[fSize] = '\0';

	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		//�ŏ��̐������̂�
		if(i == SELECTMENU_TOGAME)
			strtok(m_fileBuffer, "=");
		else
			strtok(NULL, "=");

		m_menuDesc[i] = strtok(NULL, ",");
	}

	//�t�@�C�������
	fclose(fp);

}


void CSceneTitle::Initialize() {
	m_titleLogo.Load("Texture\\TitleLogo.png");
	m_titleBack.Load("Texture\\TitleBack.png");
	m_selectMenu = SELECTMENU_TOGAME;
	m_logoAlpha = 0;
	m_windowAlpha = 0;
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		m_menuAlpha[i] = 0;
	}
	m_fileBuffer = NULL;
	LoadText();
	m_menuFont.Create(40, "MS ����");
}

void CSceneTitle::Update() {

	//�Ƃ肠���� [Space] �ŉ�ʑJ��
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		//�Q�[�����
		if (m_selectMenu == SELECTMENU_TOGAME)
		{
			m_NextScene = SCENETYPE_GAME;
		}
		//�R���N�V�������
		if (m_selectMenu == SELECTMENU_TOCOLLECTION)
		{
			m_NextScene = SCENETYPE_COLLECTION;
		}
		//�I�v�V�������
		if (m_selectMenu == SELECTMENU_TOOPTION)
		{
			m_NextScene = SCENETYPE_OPTION;
		}
		//�Q�[���̏I��
		if (m_selectMenu == SELECTMENU_QUIT)
		{
			//��ʂ����
			PostQuitMessage(0);
			return;
		}

		//���݂̃V�[�������
		m_bEnd = true;
	}

	//���ō��ڂ̈ړ�
	if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW) || g_pInput->IsKeyPush(MOFKEY_S))
	{
		//���ʉ��F�J�[�\���ړ���

		if (m_selectMenu == SELECTMENU_COUNT - 1)
		{
			m_selectMenu = SELECTMENU_TOGAME;
		}
		else
		{
			m_selectMenu++;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_UPARROW) || g_pInput->IsKeyPush(MOFKEY_W))
	{
		//���ʉ��F�J�[�\���ړ���

		if (m_selectMenu == SELECTMENU_TOGAME)
		{
			m_selectMenu = SELECTMENU_COUNT - 1;
		}
		else
		{
			m_selectMenu--;
		}
	}

	if (m_logoAlpha < FF)
	{
		m_logoAlpha += 2;
		if (m_logoAlpha >= FF - 1)
			m_logoAlpha = FF;
	}
	if (m_windowAlpha < FF / 2)
	{
		if(m_logoAlpha > 100)
		m_windowAlpha++;
	}
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_menuAlpha[i] < FF)
		{
			if ((i == SELECTMENU_TOGAME && m_logoAlpha >= 100) ||
				(i == SELECTMENU_TOCOLLECTION && m_menuAlpha[SELECTMENU_TOGAME] >= 60) ||
				(i == SELECTMENU_TOOPTION && m_menuAlpha[SELECTMENU_TOCOLLECTION] >= 60) ||
				(i == SELECTMENU_QUIT && m_menuAlpha[SELECTMENU_TOOPTION] >= 60))
			{
				m_menuAlpha[i] += MENU_ALPHASPEED;
			}
		}
	}

}

void CSceneTitle::UpdateDebug() {

}

void CSceneTitle::Render() {
	//m_titleBack.Render(0, 0);

	//�I������
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_selectMenu == i && m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
		{
			CGraphicsUtilities::RenderFillRect(190, 400 + (i * 60), 410, 440 + (i * 60), MOF_XRGB(255, 200, 100));
			CGraphicsUtilities::RenderRect(190, 400 + (i * 60), 410, 440 + (i * 60), MOF_XRGB(0, 0, 0));

			m_menuFont.RenderString(190, 400 + (i * 60), MOF_COLOR_BLACK, m_menuName[i]);
		}
		else
		{
			CGraphicsUtilities::RenderFillRect(200, 400 + (i * 60), 420, 440 + (i * 60), MOF_ARGB(m_menuAlpha[i], 255, 255, 150));
			CGraphicsUtilities::RenderRect(200, 400 + (i * 60), 420, 440 + (i * 60), MOF_ARGB(m_menuAlpha[i], 100, 100, 100));

			m_menuFont.RenderString(200, 400 + (i * 60), MOF_ARGB(m_menuAlpha[i], 0, 0, 0), m_menuName[i]);
		}
	}

	//���S
	m_titleLogo.Render(100, 100,MOF_ARGB(m_logoAlpha, FF, FF, FF));

	//�����̘g
	CGraphicsUtilities::RenderFillRect(500, 600, 900, 700,MOF_ARGB(m_windowAlpha,255,255,200));
	CGraphicsUtilities::RenderRect(500, 600, 900, 700, MOF_ARGB(m_windowAlpha, 0, 100, 255));
	if (m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
	{
		CGraphicsUtilities::RenderString(510, 610, MOF_COLOR_BLACK, m_menuDesc[m_selectMenu]);
	}

}

void CSceneTitle::RenderDebug() {
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "�^�C�g�����");
	int sw, sh; 
	sw = g_pGraphics->GetTargetWidth();
	sh = g_pGraphics->GetTargetHeight();
	CGraphicsUtilities::RenderString(0, 100, MOF_COLOR_BLACK, "SW:%d  SH:%d", sw, sh);
}

void CSceneTitle::Release() {
	//�e�N�X�`���̉��
	m_titleLogo.Release();
	m_titleBack.Release();
	//�t�H���g�̉��
	m_menuFont.Release();
	//�m�ۂ����t�@�C���o�b�t�@�����
	free(m_fileBuffer);
}