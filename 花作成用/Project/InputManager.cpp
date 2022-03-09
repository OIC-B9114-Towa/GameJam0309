#include "InputManager.h"

void CInputManager::Refresh() {
	for (int i = 0; i < 4; i++)
	{
		pad[i].RefreshKey();
		key[i].Horizontal = 0;
		key[i].Vertical = 0;
		for (int j = 0; j < 10; j++)
		{
			key[i].prev[j] = key[i].now[j];
			key[i].now[j] = false;
		}

		if (pad[i].IsKeyHold(XINPUT_DP_LEFT))
		{
			key[i].Horizontal = -1;
		}
		else if (pad[i].IsKeyHold(XINPUT_DP_RIGHT))
		{
			key[i].Horizontal = 1;
		}
		else
		{
			key[i].Horizontal = pad[i].GetStickHorizontal();
		}

		if (pad[i].IsKeyHold(XINPUT_DP_UP))
		{
			key[i].Vertical = 1;
		}
		else if (pad[i].IsKeyHold(XINPUT_DP_DOWN))
		{
			key[i].Vertical = -1;
		}
		else
		{
			key[i].Vertical = pad[i].GetStickVertical();
		}

		key[i].now[0] = pad[i].IsKeyHold(XINPUT_A);
		key[i].now[1] = pad[i].IsKeyHold(XINPUT_B);
		key[i].now[2] = pad[i].IsKeyHold(XINPUT_X);
		key[i].now[3] = pad[i].IsKeyHold(XINPUT_Y);
		key[i].now[4] = pad[i].IsKeyHold(XINPUT_L_BTN);
		key[i].now[5] = pad[i].IsKeyHold(XINPUT_R_BTN);
		key[i].now[6] = pad[i].IsKeyHold(XINPUT_LS_PUSH);
		key[i].now[7] = pad[i].IsKeyHold(XINPUT_RS_PUSH);
		key[i].now[8] = pad[i].IsKeyHold(XINPUT_START);
		key[i].now[9] = pad[i].IsKeyHold(XINPUT_BACK);

		if (i == 0)
		{
			if (g_pInput->IsKeyHold(MOFKEY_LEFT))
			{
				key[i].Horizontal = -1;
			}
			else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
			{
				key[i].Horizontal = 1;
			}

			if (g_pInput->IsKeyHold(MOFKEY_UP))
			{
				key[i].Vertical = 1;
			}
			else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
			{
				key[i].Vertical = -1;
			}
			if (g_pInput->IsKeyHold(MOFKEY_X))
			{
				key[i].now[0] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_Z))
			{
				key[i].now[1] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_A))
			{
				key[i].now[2] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_S))
			{
				key[i].now[3] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_D))
			{
				key[i].now[4] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_C))
			{
				key[i].now[5] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_LSHIFT))
			{
				key[i].now[6] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_CAPSLOCK))
			{
				key[i].now[7] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_SPACE))
			{
				key[i].now[8] = true;
			}
			if (g_pInput->IsKeyHold(MOFKEY_RETURN))
			{
				key[i].now[9] = true;
			}
		}
	}
}

void CInputManager::SelectVertical(int p, int& no, int count, int min, bool loop) {
	if (GetVertical(p) < 0.25 && GetInstance().GetVertical(p) > -0.25)
	{
		m_Select[p].m_RemainVerticalGap = 0;
		m_Select[p].m_ContinuousVerticalCount = 0;
	}
	if (m_Select[p].m_RemainVerticalGap > 0)
	{
		m_Select[p].m_RemainVerticalGap--;
		return;
	}
	if (GetVertical(p) > 0.75)
	{
		m_Select[p].m_RemainVerticalGap = m_SelectGap[m_Select[p].m_ContinuousVerticalCount];
		m_Select[p].m_ContinuousVerticalCount++;
		if (m_Select[p].m_ContinuousVerticalCount >= 2)
			m_Select[p].m_ContinuousVerticalCount = 2;

		no--;
		if (no < min)
		{
			if (loop)
				no = (count - 1 < min) ? min : count - 1;
			else
				no = min;
		}
	}
	if (GetVertical(p) < -0.75)
	{
		m_Select[p].m_RemainVerticalGap = m_SelectGap[m_Select[p].m_ContinuousVerticalCount];
		m_Select[p].m_ContinuousVerticalCount++;
		if (m_Select[p].m_ContinuousVerticalCount >= 2)
			m_Select[p].m_ContinuousVerticalCount = 2;

		no++;
		if (no > count - 1)
		{
			if (loop)
				no = min;
			else
				no = count - 1;
		}
	}
}

void CInputManager::SelectHorizontal(int p, int& no, int count, int min, bool loop) {
	if (GetHorizontal(p) < 0.25 && GetHorizontal(p) > -0.25)
	{
		m_Select[p].m_RemainHorizontalGap = 0;
		m_Select[p].m_ContinuousHorizontalCount = 0;
	}
	if (m_Select[p].m_RemainHorizontalGap > 0)
	{
		m_Select[p].m_RemainHorizontalGap--;
		return;
	}
	if (GetHorizontal(p) > 0.75)
	{
		m_Select[p].m_RemainHorizontalGap = m_SelectGap[m_Select[p].m_ContinuousHorizontalCount];
		m_Select[p].m_ContinuousHorizontalCount++;
		if (m_Select[p].m_ContinuousHorizontalCount >= 2)
			m_Select[p].m_ContinuousHorizontalCount = 2;

		no++;
		if (no > count - 1)
		{
			if (loop)
				no = min;
			else
				no = count - 1;
		}
	}
	if (GetHorizontal(p) < -0.75)
	{
		m_Select[p].m_RemainHorizontalGap = m_SelectGap[m_Select[p].m_ContinuousHorizontalCount];
		m_Select[p].m_ContinuousHorizontalCount++;
		if (m_Select[p].m_ContinuousHorizontalCount >= 2)
			m_Select[p].m_ContinuousHorizontalCount = 2;

		no--;
		if (no < min)
		{
			if (loop)
				no = (count - 1 < min) ? min : count - 1;
			else
				no = min;
		}
	}
}