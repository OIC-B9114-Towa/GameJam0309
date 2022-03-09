#pragma once
#include <Mof.h>

#define			MAXWINDPOWER			5
#define			FLOWERCOUNT				5

class CGameUIManager
{
private:
	CTexture	gScoreBackTexture;
	CTexture	gWindIconTexture;
	CTexture	gFlowerIconTexture;
	CTexture	gCurrentFlowerBackTexture;

	const float TargetPoint[FLOWERCOUNT] = {50, 50, 70, 70, 100};

	enum FlowerType
	{
		BLUE,
		RED,
		GREEN,

		TYPE_COUNT,
	};

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

	typedef struct s_Result
	{
		int			score;
		CVector3	FlowerPos[FLOWERCOUNT];
		int			FlowerColor[FLOWERCOUNT];
	}Result;

	typedef struct s_Wind
	{
		int				gWindDirect;
		int				gWindPower;
		CVector3		gWindPowerToVector;
	}Wind;

	Result			gScoreResult;
	Wind			gWind[FLOWERCOUNT];
public:

	CGameUIManager();
	~CGameUIManager();
	void Initialize();
	void UpdateUI();
	void RenderUI();
	void ReleaseUI();
};

