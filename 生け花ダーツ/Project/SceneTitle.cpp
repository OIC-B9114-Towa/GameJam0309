#include "SceneTitle.h"

CSceneTitle::CSceneTitle() :
	m_titleLogo(),
	m_titleBack(),
	m_menuIcon(),
	m_menuFont(),
	m_menuBackColor{0,0,0},
	m_menuFrameColor{0,0,0},
	m_menuRect(0,0,0,0),
	m_selectMenu(0),
	m_logoAlpha(0),
	m_menuAlpha{0,0,0},
	m_windowAlpha(0),
	m_fileBuffer(NULL),
	m_menuDesc{NULL,NULL,NULL}
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
	g_pGraphics->SetScreenSize(1024, 768);
	//�e�N�X�`���ǂݍ���
	m_titleLogo.Load("Texture\\TitleLogo.png");
	m_titleBack.Load("Texture\\TitleBack.png");

	m_menuIcon[SELECTMENU_TOGAME].Load("Texture\\MainGameIcon.png");
	m_menuIcon[SELECTMENU_TOCOLLECTION].Load("Texture\\CollectionIcon.png");
	m_menuIcon[SELECTMENU_TOOPTION].Load("Texture\\OptionIcon.png");
	m_menuIcon[SELECTMENU_QUIT].Load("Texture\\QuitIcon.png");

	//�ŏ���[���C���Q�[��]�ɍ��킹��
	m_selectMenu = SELECTMENU_TOGAME;

	//�A���t�@�l�̏�����
	m_logoAlpha = 0;
	m_windowAlpha = 0;
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		m_menuAlpha[i] = 0;

		//�������i�[�p�E������
		m_menuDesc[i] = NULL;
	}

	m_fileBuffer = NULL;
	//�e�L�X�g����ǂݍ���
	LoadText();
	//�t�H���g�ݒ�
	m_menuFont.Create(m_fontSize, "MS ����");
	
	//���j���[�̍��W�ݒ�
	m_menuRect = CRectangle(m_initMenuRect);
	
	//���j���[�̐F�ݒ�
	m_menuBackColor = { m_offMenuBackColor.red,m_offMenuBackColor.green, m_offMenuBackColor.blue };
	m_menuFrameColor = { m_offMenuFrameColor.red,m_offMenuFrameColor.green, m_offMenuFrameColor.blue };
}

//�����x�̍X�V
void CSceneTitle::UpdateAlpha()
{
	if (m_logoAlpha < FF)
	{
		m_logoAlpha += m_logoAlphaSpeed;
		if (m_logoAlpha >= FF - 1)
			m_logoAlpha = FF;
	}
	if (m_windowAlpha < WINDOW_ALPHA_STOP_TIMING)
	{
		if (m_logoAlpha > WINDOW_ALPHA_START_TIMING)
			m_windowAlpha += m_windowAlphaSpeed;
	}
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_menuAlpha[i] < FF)
		{
			if ((i == SELECTMENU_TOGAME && m_logoAlpha >= WINDOW_ALPHA_START_TIMING) ||
				(i == SELECTMENU_TOCOLLECTION && m_menuAlpha[SELECTMENU_TOGAME] >= MENU_ALPHA_START_TIMING) ||
				(i == SELECTMENU_TOOPTION && m_menuAlpha[SELECTMENU_TOCOLLECTION] >= MENU_ALPHA_START_TIMING) ||
				(i == SELECTMENU_QUIT && m_menuAlpha[SELECTMENU_TOOPTION] >= MENU_ALPHA_START_TIMING))
			{
				m_menuAlpha[i] += m_menuAlphaSpeed;
			}
		}
	}
}

//���j���[�I���̍X�V
void CSceneTitle::UpdateMenu()
{
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
}

//���j���[�I�񂾂Ƃ��A�V�[���̑J�ڍX�V
void CSceneTitle::UpdateTransition()
{
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
}

void CSceneTitle::Update() {

	//�����x�̍X�V
	UpdateAlpha();

	//���j���[�̃A���t�@�������I���܂ő���s��
	if (m_menuAlpha[SELECTMENU_COUNT - 1] < FF)
	{
		return;
	}

	//���j���[�I�񂾂Ƃ��A�V�[���̑J�ڍX�V
	UpdateTransition();
	//�I�����ڂ̍X�V
	UpdateMenu();
}

void CSceneTitle::UpdateDebug() {
}

//�I�����ڂ̕`��
void CSceneTitle::RenderMenu()
{
	//�I������
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{	
		if (m_selectMenu == i && m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
		{
			m_menuRect.Left = m_initMenuRect.Left - ON_CURSOR_SHIFT;
			m_menuRect.Right = m_initMenuRect.Right - ON_CURSOR_SHIFT;
			m_menuBackColor = { m_onMenuBackColor.red,m_onMenuBackColor.green, m_onMenuBackColor.blue };
			m_menuFrameColor = { m_onMenuFrameColor.red,m_onMenuFrameColor.green, m_onMenuFrameColor.blue };
		}
		else
		{
			m_menuRect.Left = m_initMenuRect.Left;
			m_menuRect.Right = m_initMenuRect.Right;
			m_menuBackColor = { m_offMenuBackColor.red,m_offMenuBackColor.green, m_offMenuBackColor.blue };
			m_menuFrameColor = { m_offMenuFrameColor.red,m_offMenuFrameColor.green, m_offMenuFrameColor.blue };
		}

		CGraphicsUtilities::RenderFillRect(m_menuRect.Left, m_menuRect.Top + (i * MENU_INTERVAL), m_menuRect.Right, m_menuRect.Bottom + (i * MENU_INTERVAL),
			MOF_ARGB(m_menuAlpha[i], m_menuBackColor.red, m_menuBackColor.green, m_menuBackColor.blue));
		CGraphicsUtilities::RenderRect(m_menuRect.Left, m_menuRect.Top + (i * MENU_INTERVAL), m_menuRect.Right, m_menuRect.Bottom + (i * MENU_INTERVAL),
			MOF_ARGB(m_menuAlpha[i], m_menuFrameColor.red, m_menuFrameColor.green, m_menuFrameColor.blue));

		m_menuFont.RenderString(m_menuRect.Left + ADJUST_MENU_TEXT, m_menuRect.Top + (i * MENU_INTERVAL) + ADJUST_MENU_TEXT,
			MOF_ARGB(m_menuAlpha[i], m_menuTextColor.red, m_menuTextColor.green, m_menuTextColor.blue), m_menuName[i]);
	}
}

//�A�C�R���̕`��
void CSceneTitle::RenderIcon()
{
	CGraphicsUtilities::RenderFillRect(m_iconWindowRect, MOF_ARGB(m_windowAlpha, m_iconWindowBackColor.red, m_iconWindowBackColor.green, m_iconWindowBackColor.blue));
	CGraphicsUtilities::RenderRect(m_iconWindowRect, MOF_ARGB(m_windowAlpha, m_iconWindowFrameColor.red, m_iconWindowFrameColor.green, m_iconWindowFrameColor.blue));
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		if (m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
		{
			if (i == m_selectMenu)
				m_menuIcon[i].Render(m_iconPos.x, m_iconPos.y);
		}
	}
}

//����
void CSceneTitle::RenderMenuDescription()
{
	CGraphicsUtilities::RenderFillRect(m_descWindowRect, MOF_ARGB(m_windowAlpha, m_descWindowBackColor.red, m_descWindowBackColor.green, m_descWindowBackColor.blue));
	CGraphicsUtilities::RenderRect(m_descWindowRect, MOF_ARGB(m_windowAlpha, m_descWindowFrameColor.red, m_descWindowFrameColor.green, m_descWindowFrameColor.blue));
	if (m_menuAlpha[SELECTMENU_COUNT - 1] >= FF)
	{
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, m_menuDesc[m_selectMenu]);
	}
}

void CSceneTitle::Render() {

	//�w�i
	m_titleBack.Render(0, 0);

	//�I������
	RenderMenu();

	//���S
	m_titleLogo.Render(m_logoPos.x,m_logoPos.y,MOF_ARGB(m_logoAlpha, FF, FF, FF));

	//�A�C�R��
	RenderIcon();
	
	//����
	RenderMenuDescription();
	
	//������@
	CGraphicsUtilities::RenderString(m_howToTextPos.x, m_howToTextPos.y, MOF_COLOR_BLACK, "[����]�őI���@[Space]�Ō���");
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
	for (int i = 0; i < SELECTMENU_COUNT; i++)
	{
		m_menuIcon[i].Release();
	}
	//�t�H���g�̉��
	m_menuFont.Release();
	//�m�ۂ����t�@�C���o�b�t�@�����
	free(m_fileBuffer);
}