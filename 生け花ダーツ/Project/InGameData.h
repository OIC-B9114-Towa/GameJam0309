#pragma once
#include <Mof.h>

class CInGameData
{
public:
	//花の色
	enum FlowerType
	{
		BLUE,
		RED,
		GREEN,

		TYPE_COUNT,
	};

	//風向き
	enum WindDirect
	{
		RIGHT,
		UPPERRIGHT,
		UPPERMIDDLE,
		UPPERLEFT,
		LEFT,
		LOWERLEFT,
		LOWERMIDDLE,
		LOWERRIGHT,

		DIRECT_COUNT,
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
};

