#pragma once
#include "Mof.h"

enum SOUND_BGM
{
	BGM_TITLE,
	BGM_OPTION,
	BGM_COLLECTION,

	BGM_COUNT,
};


enum SOUND_SE
{
	SE_CLICK,
	SE_CURSOR,

	SE_COUNT,
};


class CSoundManager {
private:
	CSoundBuffer bgm[BGM_COUNT];
	CSoundBuffer se[SE_COUNT];

	const float maxSEVolume = 0.15f;
	const float maxBGMVolume = 0.03f;
	float Volume = maxBGMVolume;
	float SEVolume = maxSEVolume;

	CSoundManager() {
		
	}

public:

	void Load();

	float GetVolume() {
		return Volume;
	}

	float GetSEVolume() {
		return SEVolume;
	}

	void SetVolume(float vol);

	void SetSEVolume(float vol);

	void SaveVolume();

	void LoadVolume();

	void Release();

	CSoundBuffer& GetBGM(int i)
	{
		return bgm[i];
	}

	CSoundBuffer& GetSE(int i)
	{
		return se[i];
	}

	static CSoundManager& GetInstance()
	{
		static CSoundManager obj;
		return obj;
	}
};

