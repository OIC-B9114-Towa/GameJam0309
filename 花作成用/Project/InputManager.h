#pragma once
#include <Mof.h>

class CInputManager {
private:
	CXGamePad pad[4];

	typedef struct tag_Key {
		float Horizontal;
		float Vertical;

		bool now[10];
		bool prev[10];

		tag_Key() {
			Horizontal = 0;
			Vertical = 0;
			for (int i = 0; i < 10; i++)
			{
				now[i] = false;
				prev[i] = false;
			}
		}
	}Key;

	typedef struct tag_SelectNo {
		int					m_RemainVerticalGap;
		int					m_RemainHorizontalGap;
		int					m_ContinuousVerticalCount;
		int					m_ContinuousHorizontalCount;

		tag_SelectNo() {
			m_RemainVerticalGap = 0;
			m_RemainHorizontalGap = 0;
			m_ContinuousVerticalCount = 0;
			m_ContinuousHorizontalCount = 0;
		};
	}SelectNo;
	int					m_SelectGap[3] = { 25,15,5 };

	Key key[4];
	SelectNo			m_Select[4];

	CInputManager() :
		key(),
		m_Select()
	{
		XGAMEPADCREATEINFO cinfo;
		for (int i = 0; i < 4; i++)
		{
			cinfo.No = i;
			pad[i].Create(&cinfo);
		}
	}
public:
	float GetHorizontal(int i) {
		return key[i].Horizontal;
	}

	float GetVertical(int i) {
		return key[i].Vertical;
	}

	bool GetHold(int i, int btnno) {
		return key[i].now[btnno];
	}

	bool GetPush(int i, int btnno) {
		return !key[i].prev[btnno] && key[i].now[btnno];
	}

	bool GetPull(int i, int btnno) {
		return key[i].prev[btnno] && !key[i].now[btnno];
	}

	void SelectVertical(int p, int& no, int count, int min, bool loop = true);

	void SelectHorizontal(int p, int& no, int count, int min, bool loop = true);

	void Refresh();

	static CInputManager& GetInstance()
	{
		static CInputManager obj;
		return obj;
	}
};