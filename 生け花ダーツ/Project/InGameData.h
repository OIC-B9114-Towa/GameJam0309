#pragma once
#include <Mof.h>

	//�Ԃ̐F
	enum FlowerType
	{
		FT_BLUE,
		FT_RED,
		FT_GREEN,

		FLOWERTYPE_COUNT,
	};

	//������
	enum WindDirect
	{
		WD_RIGHT,
		WD_UPPERRIGHT,
		WD_UPPERMIDDLE,
		WD_UPPERLEFT,
		WD_LEFT,
		WD_LOWERLEFT,
		WD_LOWERMIDDLE,
		WD_LOWERRIGHT,

		WINDDIRECT_COUNT,
	};
	typedef struct s_Result			//���U���g�p�\����
	{
		int			score;
		CVector3*	FlowerPos;
		int*		FlowerColor;
	}Result;

	typedef struct s_Wind			//���f�[�^
	{
		int				gWindDirect;
		int				gWindPower;
		CVector3		gWindPowerToVector;
	}Wind;

	const float TargetPoint[3] = { 50, 70, 100 };		//���_

	enum PauseMenu 
	{
		PM_RETURNGAME,
		PM_RETRY,
		PM_GAMEEND,

		PM_COUNT,
	};
