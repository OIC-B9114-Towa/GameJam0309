#include "SceneOption.h"

CSceneOption::CSceneOption():
	m_optionMenuSelect(0),
	m_seNum(0),
	m_bgmNum(0)
{

}

void CSceneOption::Initialize() {
	m_voiceIcon.Load("Texture\\VoiceIcon.png");

	//��ԏ�̍��ڂ�SE�̐ݒ�̂���
	m_optionMenuSelect = OPTION_SE;

	m_font.Create(40, "MS ����");

	m_seNum = 0; 
	m_bgmNum = 0;
	//���ʂ̓ǂݍ���
	//SE
	for (int i = VOLUME_COUNT - 1; i >= 0; i--)
	{
		if (CSoundManager::GetInstance().GetSEVolume() >= m_seVolume[i])
		{
			m_seNum = i;
			break;
		}
	}
	//BGM
	for (int i = VOLUME_COUNT - 1; i >= 0; i--)
	{
		if (CSoundManager::GetInstance().GetVolume() >= m_bgmVolume[i])
		{
			m_bgmNum = i;
			break;
		}
	}

	//BGM�̍Đ�
	CSoundManager::GetInstance().GetBGM(BGM_OPTION).Play();

}

void CSceneOption::UpdateVolume()
{
	//���ʂ̒���
	if (g_pInput->IsKeyPush(MOFKEY_LEFT) || g_pInput->IsKeyPush(MOFKEY_A))
	{
		if (m_optionMenuSelect == OPTION_SE)
		{
			if (m_seNum > VOLUME_MUTE)
				m_seNum--;
		}
		else if (m_optionMenuSelect == OPTION_BGM)
		{
			if (m_bgmNum > VOLUME_MUTE)
				m_bgmNum--;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_D))
	{
		if (m_optionMenuSelect == OPTION_SE)
		{
			if (m_seNum < VOLUME_L)
				m_seNum++;
		}
		else if (m_optionMenuSelect == OPTION_BGM)
		{
			if (m_bgmNum < VOLUME_L)
				m_bgmNum++;
		}
	}
	//���ʂ̍X�V
	CSoundManager::GetInstance().SetSEVolume(m_seVolume[m_seNum]);
	CSoundManager::GetInstance().SetVolume(m_bgmVolume[m_bgmNum]);
}

void CSceneOption::UpdateMenu()
{
	//���ڂ̑I��
	if (g_pInput->IsKeyPush(MOFKEY_UPARROW) || g_pInput->IsKeyPush(MOFKEY_W))
	{
		CSoundManager::GetInstance().GetSE(SE_CURSOR).Play();
		if (m_optionMenuSelect == OPTION_SE)
			m_optionMenuSelect = OPTION_TOTITLE;
		else
			m_optionMenuSelect--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW) || g_pInput->IsKeyPush(MOFKEY_S))
	{
		CSoundManager::GetInstance().GetSE(SE_CURSOR).Play();
		if (m_optionMenuSelect == OPTION_TOTITLE)
			m_optionMenuSelect = OPTION_SE;
		else
			m_optionMenuSelect++;
	}
}

void CSceneOption::UpdateTransition()
{
	//�^�C�g���֑J�ڂ���
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		if (m_optionMenuSelect == OPTION_TOTITLE)
		{
			CSoundManager::GetInstance().GetSE(SE_CLICK).Play();

			//�J�ڂ���O�Ɂ@SetVolume�@�ŉ��ʂ̕ۑ�
			CSoundManager::GetInstance().SaveVolume();

			//BGM�̃X�g�b�v
			CSoundManager::GetInstance().GetBGM(BGM_OPTION).Stop();

			//�J�ڐ�
			m_NextScene = SCENETYPE_TITLE;
			//�V�[�������
			m_bEnd = true;
		}
	}
}

void CSceneOption::Update() {

	//�J�ڂ���
	UpdateTransition();

	//���ʂ̍X�V
	UpdateVolume();

	//���ڂ̑I��
	UpdateMenu();

}

void CSceneOption::UpdateDebug() {



}

//���ʃA�C�R��
void CSceneOption::RenderIcon()
{
	//���ʃA�C�R��
	if (m_seNum == VOLUME_MUTE)
		m_voiceIcon.Render(m_seVoiceIconPos.x, m_seVoiceIconPos.y, m_muteVoiceIconShowRect);
	else
		m_voiceIcon.Render(m_seVoiceIconPos.x, m_seVoiceIconPos.y, m_voiceIconShowRect);

	if (m_bgmNum == VOLUME_MUTE)
		m_voiceIcon.Render(m_bgmVoiceIconPos.x, m_bgmVoiceIconPos.y, m_muteVoiceIconShowRect);
	else
		m_voiceIcon.Render(m_bgmVoiceIconPos.x, m_bgmVoiceIconPos.y, m_voiceIconShowRect);
}

//���j���[�\��
void CSceneOption::RenderMenu()
{
	//���j���[�\��
	if (m_optionMenuSelect == OPTION_SE)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS, MOF_COLOR_RED, " SE");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS, MOF_COLOR_BLACK, " SE");

	if (m_optionMenuSelect == OPTION_BGM)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS + MENU_INTERVAL, MOF_COLOR_RED, "BGM");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS + MENU_INTERVAL, MOF_COLOR_BLACK, "BGM");

	if (m_optionMenuSelect == OPTION_TOTITLE)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS + MENU_INTERVAL * 2, MOF_COLOR_RED, "�^�C�g����");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS + MENU_INTERVAL * 2, MOF_COLOR_BLACK, "�^�C�g����");
}

//�{�����[���̃o�[�̕`��
void CSceneOption::RenderVolume()
{
	//SE���ʂ̃o�[
	if (m_seNum != VOLUME_MUTE)
	{
		if (m_seNum >= VOLUME_S)
			CGraphicsUtilities::RenderFillRect(m_seVolumeSRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_seVolumeSRect, MOF_COLOR_BLACK);

		if (m_seNum >= VOLUME_M)
			CGraphicsUtilities::RenderFillRect(m_seVolumeMRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_seVolumeMRect, MOF_COLOR_BLACK);

		if (m_seNum >= VOLUME_L)
			CGraphicsUtilities::RenderFillRect(m_seVolumeLRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_seVolumeLRect, MOF_COLOR_BLACK);
	}
	//BGM���ʂ̃o�[
	if (m_bgmNum != VOLUME_MUTE)
	{
		if (m_bgmNum >= VOLUME_S)
			CGraphicsUtilities::RenderFillRect(m_bgmVolumeSRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_bgmVolumeSRect, MOF_COLOR_BLACK);

		if (m_bgmNum >= VOLUME_M)
			CGraphicsUtilities::RenderFillRect(m_bgmVolumeMRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_bgmVolumeMRect, MOF_COLOR_BLACK);

		if (m_bgmNum >= VOLUME_L)
			CGraphicsUtilities::RenderFillRect(m_bgmVolumeLRect, MOF_COLOR_BLACK);
		else
			CGraphicsUtilities::RenderRect(m_bgmVolumeLRect, MOF_COLOR_BLACK);
	}
}

//���ڂ̐���
void CSceneOption::RenderDescription()
{
	//�g
	CGraphicsUtilities::RenderFillRect(590, 189, 900, 240, MOF_ARGB(100, 100, 120, 255));
	CGraphicsUtilities::RenderRect(590, 189, 900, 240, MOF_ARGB(150, 10, 20, 255));
	//���ڂ̐���
	if (m_optionMenuSelect == OPTION_SE)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "SE�̉��ʂ𒲐��ł��܂�");
	if (m_optionMenuSelect == OPTION_BGM)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "BGM�̉��ʂ𒲐��ł��܂�");
	if (m_optionMenuSelect == OPTION_TOTITLE)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "�^�C�g���ɖ߂�܂�");
}

void CSceneOption::Render() {
	//�w�i
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(240, 240, 180));
	//��
	m_font.RenderString(10, 10, MOF_COLOR_BLACK, "�I�v�V�������");
	
	//���ʃA�C�R��
	RenderIcon();

	//���j���[�\��
	RenderMenu();

	//�{�����[���̃o�[�̕`��
	RenderVolume();

	//���ڂ̐���
	RenderDescription();

	CGraphicsUtilities::RenderString(m_howToText.x,m_howToText.y, MOF_COLOR_BLACK, "[����]�őI���@[����]�ŉ��ʒ����@[Space]�Ō���");

}

void CSceneOption::RenderDebug() {
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "�I�v�V�������");
}

void CSceneOption::Release() {
	m_voiceIcon.Release();
	m_font.Release();
}