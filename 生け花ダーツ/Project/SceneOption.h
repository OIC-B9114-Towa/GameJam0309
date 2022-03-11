#pragma once
#include "SceneBase.h"

#define MENU_INIT_POS	200
#define MENU_INTERVAL	150
#define MENU_SHIFT		15

enum VOLUME_NUM
{
	VOLUME_MUTE,
	VOLUME_S,
	VOLUME_M,
	VOLUME_L,

	VOLUME_COUNT,
};

enum OPTION_MENU
{
	OPTION_SE,
	OPTION_BGM,
	OPTION_TOTITLE,

	OPTION_COUNT,
};

class CSceneOption : public CSceneBase
{
private:
	CTexture m_voiceIcon;

	CFont m_font;

	//アイコン表示位置
	const CVector2 m_seVoiceIconPos = {300,170};
	const CVector2 m_bgmVoiceIconPos = { 300,320 };

	//アイコン表示範囲
	const CRectangle m_voiceIconShowRect = CRectangle(0,0,100,100);
	const CRectangle m_muteVoiceIconShowRect = CRectangle(100,0,200,100);

	//音量の棒　位置
	const CRectangle m_seVolumeSRect = CRectangle(370, 200, 380, 235);
	const CRectangle m_seVolumeMRect = CRectangle(390, 195, 400, 240);
	const CRectangle m_seVolumeLRect = CRectangle(410, 190, 420, 245);

	const CRectangle m_bgmVolumeSRect = CRectangle(370, 350, 380, 385);
	const CRectangle m_bgmVolumeMRect = CRectangle(390, 345, 400, 390);
	const CRectangle m_bgmVolumeLRect = CRectangle(410, 340, 420, 395);

	//操作説明
	const CVector2 m_howToText = CVector2(250, 650);
	//項目説明　位置
	const CVector2 m_descPos = CVector2(600, 200);

	const float m_seVolume[VOLUME_COUNT] = { 0.0f,0.05f,0.1f,0.15f };
	const float m_bgmVolume[VOLUME_COUNT] = { 0.0f,0.01f,0.02f,0.03f };

	int m_seNum;
	int m_bgmNum;

	int m_optionMenuSelect;
public:
	CSceneOption();
	void Initialize(void);
	void UpdateVolume();
	void UpdateMenu();
	void UpdateTransition();
	void Update(void);
	void UpdateDebug(void);
	void RenderIcon();
	void RenderMenu();
	void RenderVolume();
	void RenderDescription();
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

