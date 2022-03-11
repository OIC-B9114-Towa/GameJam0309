#include "SoundManager.h"

void CSoundManager::Load() {

	bgm[BGM_TITLE].Load("Sound\\TitleBGM.mp3");
	bgm[BGM_OPTION].Load("Sound\\OptionBGM.mp3");
	bgm[BGM_COLLECTION].Load("Sound\\CollectionBGM.mp3");

	for (int i = 0; i < BGM_COUNT; i++)
	{
		bgm[i].SetLoop(TRUE);
	}


	se[SE_CLICK].Load("Sound\\ClickSE.mp3");
	se[SE_CURSOR].Load("Sound\\CursorSE.mp3");

	for (int i = 0; i < SE_COUNT; i++)
	{
		se[i].SetLoop(FALSE);
	}

	LoadVolume();
}

void CSoundManager::LoadVolume() {
	FILE* fp = fopen("Sound\\Volume.dat", "rb");
	if (fp)
	{
		fread(&Volume, sizeof(float), 1, fp);
		fread(&SEVolume, sizeof(float), 1, fp);
		fclose(fp);
	}
	SetVolume(Volume);
	SetSEVolume(SEVolume);
}

void CSoundManager::SaveVolume() {
	FILE* fp = fopen("Sound\\Volume.dat", "wb");
	if (fp)
	{
		fwrite(&Volume, sizeof(float), 1, fp);
		fwrite(&SEVolume, sizeof(float), 1, fp);
		fclose(fp);
	}
	SetVolume(Volume);
}

void CSoundManager::SetVolume(float vol) {
	if (vol < 0)
		vol = 0;
	if (vol > maxBGMVolume)
		vol = maxBGMVolume;
	Volume = vol;
	for (int i = 0; i < BGM_COUNT; i++)
	{
		bgm[i].SetVolume(Volume);
	}
}

void CSoundManager::SetSEVolume(float vol) {
	if (vol < 0)
		vol = 0;
	if (vol > maxSEVolume)
		vol = maxSEVolume;
	SEVolume = vol;
	for (int i = 0; i < SE_COUNT; i++)
	{
		se[i].SetVolume(SEVolume);
	}
}

void CSoundManager::Release() {
	for (int i = 0; i < BGM_COUNT; i++)
	{
		bgm[i].Release();
	}
	for (int i = 0; i < SE_COUNT; i++)
	{
		se[i].Release();
	}
}