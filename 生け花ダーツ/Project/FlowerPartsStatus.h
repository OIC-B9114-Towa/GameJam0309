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
		Color() {
	}
}FlowerPartsStatus;

typedef struct tag_PartsSet
{
	int Count;
	FlowerPartsStatus Parts[30];

	tag_PartsSet() :
		Count(0),
		Parts() {
	}

	void Load(std::string ps)
	{
		FILE* fp = fopen(ps.c_str(), "rb");
		if (!fp) { return; }

		fseek(fp, 0, SEEK_END);
		long fSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		//ファイルサイズ分だけのメモリを確保する
		char* pBuffer = (char*)malloc(fSize + 1);
		//ファイルを全てバッファに読み込む
		fSize = fread(pBuffer, 1, fSize, fp);
		pBuffer[fSize] = '\0';
		char* pstr;

		pstr = strtok(pBuffer, ",");

		Count = atoi(pstr);
		pstr = strtok(NULL, ",");

		Count = min(30, Count);

		for (int i = 0; i < Count; i++)
		{
			Parts[i].PartsNo = i;
			Parts[i].Scale.x = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Scale.y = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Scale.z = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Translate.x = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Translate.y = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Translate.z = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Color.x = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Color.y = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Color.z = atof(pstr);
			pstr = strtok(NULL, ",");
			Parts[i].Color.w = 1;
		}

		fclose(fp);
		free(pBuffer);
	}
}PartsSet;