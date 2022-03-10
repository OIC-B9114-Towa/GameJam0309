#pragma once
#include "SceneBase.h"

//�F�Ƃ��̐ݒ�ő�l
#define FF 255
//�J�[�\�������킹�Ă���Ƃ����ɔ�яo������
#define ON_CURSOR_SHIFT 10
//���j���[���̕����ʒu����
#define ADJUST_MENU_TEXT 5
//���j���[�̊Ԋu
#define MENU_INTERVAL 60
//�����x�X�V�^�C�~���O
#define WINDOW_ALPHA_START_TIMING 100
#define MENU_ALPHA_START_TIMING 60
//�g�̓����x�~�߂�^�C�~���O
#define WINDOW_ALPHA_STOP_TIMING 200

//�I�ׂ鍀�ڂ̗�
enum SelectMenu
{
	SELECTMENU_TOGAME,
	SELECTMENU_TOCOLLECTION,
	SELECTMENU_TOOPTION,
	SELECTMENU_QUIT,

	SELECTMENU_COUNT,
};

//3�F��`�p
struct RGB_Color
{
	int red;
	int green;
	int blue;
};

class CSceneTitle : public CSceneBase
{
private:
	CTexture m_titleLogo;
	CTexture m_titleBack;
	CTexture m_menuIcon[SELECTMENU_COUNT];

	CFont m_menuFont;
	//�t�H���g�T�C�Y
	const int m_fontSize = 40;

	//�F
	//�����g
	const RGB_Color m_descWindowBackColor = { 200,200,255 };
	const RGB_Color m_descWindowFrameColor = { 0,100,255 };
	//�A�C�R���g
	const RGB_Color m_iconWindowBackColor = { 200,200,210 };
	const RGB_Color m_iconWindowFrameColor = { 0,100,255 };
	//�I�΂�Ă����Ԃ̃��j���[
	const RGB_Color m_onMenuBackColor = { 255,180,100 };
	const RGB_Color m_onMenuFrameColor = { 0,0,0 };
	//�I�΂�Ă��Ȃ���Ԃ̃��j���[
	const RGB_Color m_offMenuBackColor = { 255,255,150 };
	const RGB_Color m_offMenuFrameColor = { 100,100,100 };
	//���j���[
	RGB_Color m_menuBackColor;
	RGB_Color m_menuFrameColor;
	//���j���[������
	const RGB_Color m_menuTextColor = { 0, 0, 0 };

	//�`��ʒu
	//�����g
	const CRectangle m_descWindowRect = CRectangle(500, 470, 800, 540);
	//�A�C�R���g
	const CRectangle m_iconWindowRect = CRectangle(490, 320, 810, 550);
	//���j���[
	CRectangle m_menuRect;
	const CRectangle m_initMenuRect = CRectangle(210, 320, 440, 370);
	//���S
	const CVector2 m_logoPos = CVector2(110, 70);
	//�A�C�R��
	const CVector2 m_iconPos = CVector2(525, 330);
	//����
	const CVector2 m_descPos = CVector2(510, 480);
	//������@
	const CVector2 m_howToTextPos = CVector2(320, 580);

	//�ǂ̍��ڂ�I�𒆂�
	int m_selectMenu;

	//�����x
	//���S
	int	m_logoAlpha;
	const int m_logoAlphaSpeed = 2;
	//���j���[
	int m_menuAlpha[SELECTMENU_COUNT];
	const int m_menuAlphaSpeed = 3;
	//�g
	int m_windowAlpha;
	const int m_windowAlphaSpeed = 2;

	//�e�L�X�g�ǂݍ��ݗp
	char* m_fileBuffer;
	char* m_menuDesc[SELECTMENU_COUNT];

	//���j���[������
	const char* m_menuName[SELECTMENU_COUNT] = { 
		"���C���Q�[��",
		" �R���N�V����",
		"  �I�v�V���� ",
		"    �����   " };

public:
	CSceneTitle();
	void LoadText();
	void Initialize(void);
	void UpdateAlpha();
	void UpdateMenu();
	void UpdateTransition();
	void Update(void);
	void UpdateDebug(void);
	void RenderMenu();
	void RenderIcon();
	void RenderMenuDescription();
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};


