#include "EditSubMenuObject.h"

void CEditSubMenuObject::Initialize()
{
	m_MStatus.Pos = CVector2(20, 20);
	m_MStatus.Size = CVector2(180, 620);
	m_MStatus.Type = 1;
	m_MStatus.SurfaceColor = MOF_XRGB(120, 120, 120);

	CMenu::Initialize(m_MStatus);
}
