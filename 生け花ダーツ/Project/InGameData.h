#pragma once
#include <Mof.h>

class CInGameData
{
public:
	//�Ԃ̐F
	enum FlowerType
	{
		BLUE,
		RED,
		GREEN,

		TYPE_COUNT,
	};

	//������
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
};

