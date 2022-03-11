#pragma once
#include <Mof.h>

typedef struct tag_FlowerPartsStatus
{
	int PartsNo;
	CVector3 Scale;
	CVector3 Translate;
	CVector4 Color;

	tag_FlowerPartsStatus() :
		PartsNo(0),
		Scale(),
		Translate(),
		Color()
	{

	}
}FlowerPartsStatus;