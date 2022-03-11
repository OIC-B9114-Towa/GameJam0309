#include "FlowerPartsLoder.h"

void CFlowerPartsLoder::Load() {
	CUtilities::SetCurrentDirectory("FlowerModel");
	FILE* fp = fopen("BoxList.txt", "rb");
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

	int count = atoi(pstr);
	pstr = strtok(NULL, ",");

	std::vector<std::string> pass;

	for (int i = 0; i < count; i++)
	{
		pass.push_back(pstr);
		pstr = strtok(NULL, ",");
	}
	fclose(fp);
	free(pBuffer);

	for (int i = 0; i < count; i++)
	{
		m_Set.push_back(PartsSet());
		m_Set[i].Load(pass[i]);
	}
	CUtilities::SetCurrentDirectory("../");
}

PartsSet CFlowerPartsLoder::GetBoxStatus(FlowerType type) {
	switch (type)
	{
	case FT_BLUE:
		return m_Set[0];
	case FT_RED:
		return m_Set[1];
	case FT_GREEN:
		return m_Set[2];
	default:
		break;
	}
	return m_Set[0];
}

PartsSet CFlowerPartsLoder::GetBoxStatus(int type) {
	switch (type)
	{
	case 0:
		return m_Set[0];
	case 1:
		return m_Set[1];
	case 2:
		return m_Set[2];
	default:
		break;
	}
	return m_Set[0];
}

PartsSet CFlowerPartsLoder::GetRandomBoxStatus() {
	int no = rand() % m_Set.size();
	return m_Set[no];
}