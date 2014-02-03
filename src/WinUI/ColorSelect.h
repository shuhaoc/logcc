#pragma once
#include "afxwin.h"

class CColorSelect :
	public CButton {
public:
	CColorSelect(void);
	~CColorSelect(void);

private:
	COLORREF m_Color;		//颜色
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
public:

	void SetColor(COLORREF color) {
		m_Color = color;
	}
};
