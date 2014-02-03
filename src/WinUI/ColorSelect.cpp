#include "StdAfx.h"
#include "ColorSelect.h"

CColorSelect::CColorSelect(void) {
}

CColorSelect::~CColorSelect(void) {
}
BEGIN_MESSAGE_MAP(CColorSelect, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CColorSelect::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	//绘制背景
	CRect rcOld;
	GetClientRect(rcOld);
	CPen pen(PS_SOLID,1,m_Color);
	CBrush bkgBrush(m_Color);
	CPen *oldpen = dc.SelectObject(&pen);
	dc.Rectangle(&rcOld);
	dc.FillRect(rcOld,&bkgBrush);
	dc.SelectObject(oldpen);
}
