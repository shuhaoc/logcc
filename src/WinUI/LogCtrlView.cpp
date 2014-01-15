// LogCtrlView.cpp : 实现文件
//

#include "stdafx.h"
#include "WinUI.h"
#include "LogCtrlView.h"


// CLogCtrlView

IMPLEMENT_DYNCREATE(CLogCtrlView, CFormView)

CLogCtrlView::CLogCtrlView()
	: CFormView(CLogCtrlView::IDD)
{

}

CLogCtrlView::~CLogCtrlView()
{
}

void CLogCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogCtrlView, CFormView)
END_MESSAGE_MAP()


// CLogCtrlView 诊断

#ifdef _DEBUG
void CLogCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogCtrlView 消息处理程序
