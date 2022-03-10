#pragma once
#include <Mof.h>

	//花の色
	enum FlowerType
	{
		FT_BLUE,
		FT_RED,
		FT_GREEN,

		FLOWERTYPE_COUNT,
	};

	//風向き
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
	typedef struct s_Result			//リザルト用構造体
	{
		int			score;
		CVector3*	FlowerPos;
		int*		FlowerColor;
	}Result;

	typedef struct s_Wind			//風データ
	{
		int				gWindDirect;
		int				gWindPower;
		CVector3		gWindPowerToVector;
	}Wind;

	const float TargetPoint[3] = { 50, 70, 100 };		//得点

	enum PauseMenu 
	{
		PM_RETURNGAME,
		PM_RETRY,
		PM_GAMEEND,

		PM_COUNT,
	};
