#include "SceneOption.h"

CSceneOption::CSceneOption():
	m_optionMenuSelect(0),
	m_seNum(0),
	m_bgmNum(0)
{

}

void CSceneOption::Initialize() {
	m_voiceIcon.Load("Texture\\VoiceIcon.png");

	//一番上の項目がSEの設定のため
	m_optionMenuSelect = OPTION_SE;

	m_font.Create(40, "MS 明朝");

	m_seNum = 0; 
	m_bgmNum = 0;
	//音量の読み込み
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

	//BGMの再生
	CSoundManager::GetInstance().GetBGM(BGM_OPTION).Play();

}

void CSceneOption::UpdateVolume()
{
	//音量の調整
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
	//音量の更新
	CSoundManager::GetInstance().SetSEVolume(m_seVolume[m_seNum]);
	CSoundManager::GetInstance().SetVolume(m_bgmVolume[m_bgmNum]);
}

void CSceneOption::UpdateMenu()
{
	//項目の選択
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
	//タイトルへ遷移する
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		if (m_optionMenuSelect == OPTION_TOTITLE)
		{
			CSoundManager::GetInstance().GetSE(SE_CLICK).Play();

			//遷移する前に　SetVolume　で音量の保存
			CSoundManager::GetInstance().SaveVolume();

			//BGMのストップ
			CSoundManager::GetInstance().GetBGM(BGM_OPTION).Stop();

			//遷移先
			m_NextScene = SCENETYPE_TITLE;
			//シーンを閉じる
			m_bEnd = true;
		}
	}
}

void CSceneOption::Update() {

	//遷移する
	UpdateTransition();

	//音量の更新
	UpdateVolume();

	//項目の選択
	UpdateMenu();

}

void CSceneOption::UpdateDebug() {



}

//音量アイコン
void CSceneOption::RenderIcon()
{
	//音量アイコン
	if (m_seNum == VOLUME_MUTE)
		m_voiceIcon.Render(m_seVoiceIconPos.x, m_seVoiceIconPos.y, m_muteVoiceIconShowRect);
	else
		m_voiceIcon.Render(m_seVoiceIconPos.x, m_seVoiceIconPos.y, m_voiceIconShowRect);

	if (m_bgmNum == VOLUME_MUTE)
		m_voiceIcon.Render(m_bgmVoiceIconPos.x, m_bgmVoiceIconPos.y, m_muteVoiceIconShowRect);
	else
		m_voiceIcon.Render(m_bgmVoiceIconPos.x, m_bgmVoiceIconPos.y, m_voiceIconShowRect);
}

//メニュー表示
void CSceneOption::RenderMenu()
{
	//メニュー表示
	if (m_optionMenuSelect == OPTION_SE)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS, MOF_COLOR_RED, " SE");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS, MOF_COLOR_BLACK, " SE");

	if (m_optionMenuSelect == OPTION_BGM)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS + MENU_INTERVAL, MOF_COLOR_RED, "BGM");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS + MENU_INTERVAL, MOF_COLOR_BLACK, "BGM");

	if (m_optionMenuSelect == OPTION_TOTITLE)
		m_font.RenderString(MENU_INIT_POS - MENU_SHIFT, MENU_INIT_POS + MENU_INTERVAL * 2, MOF_COLOR_RED, "タイトルへ");
	else
		m_font.RenderString(MENU_INIT_POS, MENU_INIT_POS + MENU_INTERVAL * 2, MOF_COLOR_BLACK, "タイトルへ");
}

//ボリュームのバーの描画
void CSceneOption::RenderVolume()
{
	//SE音量のバー
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
	//BGM音量のバー
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

//項目の説明
void CSceneOption::RenderDescription()
{
	//枠
	CGraphicsUtilities::RenderFillRect(590, 189, 900, 240, MOF_ARGB(100, 100, 120, 255));
	CGraphicsUtilities::RenderRect(590, 189, 900, 240, MOF_ARGB(150, 10, 20, 255));
	//項目の説明
	if (m_optionMenuSelect == OPTION_SE)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "SEの音量を調整できます");
	if (m_optionMenuSelect == OPTION_BGM)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "BGMの音量を調整できます");
	if (m_optionMenuSelect == OPTION_TOTITLE)
		CGraphicsUtilities::RenderString(m_descPos.x, m_descPos.y, MOF_COLOR_BLACK, "タイトルに戻ります");
}

void CSceneOption::Render() {
	//背景
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(240, 240, 180));
	//題
	m_font.RenderString(10, 10, MOF_COLOR_BLACK, "オプション画面");
	
	//音量アイコン
	RenderIcon();

	//メニュー表示
	RenderMenu();

	//ボリュームのバーの描画
	RenderVolume();

	//項目の説明
	RenderDescription();

	CGraphicsUtilities::RenderString(m_howToText.x,m_howToText.y, MOF_COLOR_BLACK, "[↑↓]で選択　[←→]で音量調整　[Space]で決定");

}

void CSceneOption::RenderDebug() {
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "オプション画面");
}

void CSceneOption::Release() {
	m_voiceIcon.Release();
	m_font.Release();
}