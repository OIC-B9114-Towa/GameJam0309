#pragma once
#include <Mof.h>

typedef struct tag_LabelStatus {
	CVector2		Pos;
	CVector2		Size;
	std::string		Text;
	int				Justified;
	MofU32			TextColor;
	MofU32			SurfaceColor;
	MofU32			EdgeColor;

	tag_LabelStatus() :
		Pos(0, 0),
		Size(0, 0),
		Text(""),
		Justified(0),
		TextColor(MOF_ARGB(255, 255, 255, 255)),
		SurfaceColor(MOF_ARGB(0, 0, 0, 0)),
		EdgeColor(MOF_ARGB(0, 255, 255, 255)){
	}
}LabelStatus;

class CLabel
{
private:
	LabelStatus m_LStatus;
public:
	CLabel();
	~CLabel();

	void Initialize(const LabelStatus &bstatus);
	void ChangeText(std::string tex);
	void Render(CVector2 pos = CVector2(0, 0));
	void Release();
	LabelStatus GetLabelStatus() { return m_LStatus; }
	CRectangle GetRect(CVector2 pos = CVector2(0, 0)) {
		return CRectangle(m_LStatus.Pos.x + pos.x, m_LStatus.Pos.y + pos.y, m_LStatus.Pos.x + m_LStatus.Size.x + pos.x, m_LStatus.Pos.y + m_LStatus.Size.y + pos.y);
	}
};

