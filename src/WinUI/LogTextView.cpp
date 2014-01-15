// LogTextView.cpp : 实现文件
//

#include "stdafx.h"
#include "WinUI.h"
#include "WinUIDoc.h"
#include "LogTextView.h"
#include "ILogQuery.h"
#include "LogItem.h"


// CLogTextView

IMPLEMENT_DYNCREATE(CLogTextView, CFormView)

CLogTextView::CLogTextView()
	: CFormView(CLogTextView::IDD)
{

}

CLogTextView::~CLogTextView()
{
}

void CLogTextView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LINE_TEXT, textEdit);
}

BEGIN_MESSAGE_MAP(CLogTextView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLogTextView 诊断

#ifdef _DEBUG
void CLogTextView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogTextView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

CWinUIDoc* CLogTextView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinUIDoc)));
	return (CWinUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogTextView 消息处理程序


void CLogTextView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->logQuery->registerObserver(this);
}


void CLogTextView::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->logQuery->unregisterObserver(this);

	CFormView::PostNcDestroy();
}

void CLogTextView::NotifyGeneralDataChanged()
{
	LogItem* item = GetDocument()->logQuery->getSelected();
	if (item) {
		textEdit.SetWindowText(item->text.c_str());
	}
}

void CLogTextView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (textEdit.GetSafeHwnd())
	{
		CRect clientRect;
		GetClientRect(clientRect);
		textEdit.MoveWindow(0, 0, clientRect.Width(), clientRect.Height());
	}
}
