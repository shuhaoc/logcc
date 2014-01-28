// LogTextView.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCC.h"
#include "LogCCDoc.h"
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


void CLogTextView::onSubmit() {
}

// CLogTextView 消息处理程序


void CLogTextView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	getModel()->registerObserver(this);
}


void CLogTextView::PostNcDestroy()
{
	getModel()->unregisterObserver(this);

	CFormView::PostNcDestroy();
}

void CLogTextView::onGeneralDataChanged() {
	LogItem* item = getModel()->getSelected();
	if (item) {
		textEdit.SetWindowText(item->text.c_str());
	}
}

void CLogTextView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (textEdit.GetSafeHwnd())
	{
		CRect clientRect;
		GetClientRect(clientRect);
		textEdit.MoveWindow(0, 0, clientRect.Width(), clientRect.Height());
	}
}
