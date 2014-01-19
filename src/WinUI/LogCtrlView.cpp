// LogCtrlView.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCC.h"
#include "LogCtrlView.h"
#include "LogCCDoc.h"
#include "ILogQuery.h"

// CLogCtrlView

IMPLEMENT_DYNCREATE(CLogCtrlView, CFormView)

CLogCtrlView::CLogCtrlView()
	: CFormView(CLogCtrlView::IDD)
	, criteria(_T(""))
{

}

CLogCtrlView::~CLogCtrlView()
{
}

void CLogCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRITERIA, criteria);
}

BEGIN_MESSAGE_MAP(CLogCtrlView, CFormView)
	ON_EN_CHANGE(IDC_CRITERIA, &CLogCtrlView::OnEnChangeCriteria)
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

CLogCCDoc* CLogCtrlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogCCDoc)));
	return (CLogCCDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogCtrlView 消息处理程序


void CLogCtrlView::OnEnChangeCriteria()
{
	UpdateData(TRUE);
	GetDocument()->criteria = criteria.GetBuffer();
}

BOOL CLogCtrlView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// UNDONE: 删除此函数
	return __super::PreTranslateMessage(pMsg);
}
