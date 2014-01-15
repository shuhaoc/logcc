// LogDetailView.cpp : 实现文件
//

#include "stdafx.h"
#include "WinUI.h"
#include "WinUIDoc.h"
#include "LogDetailView.h"
#include "ILogQuery.h"
#include "LogPainterFactory.h"
#include "ILogItemPainter.h"

// CLogDetailView

IMPLEMENT_DYNCREATE(CLogDetailView, CView)

CLogDetailView::CLogDetailView()
{

}

CLogDetailView::~CLogDetailView()
{
}

BEGIN_MESSAGE_MAP(CLogDetailView, CView)
END_MESSAGE_MAP()


// CLogDetailView 绘图

void CLogDetailView::OnDraw(CDC* pDC)
{
	CWinUIDoc* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	LogItem* item = pDoc->logQuery->getSelected();
	if (item) {
		CRect clientRect;
		GetClientRect(clientRect);

		HFONT font = ::CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FIXED_PITCH, _T("新宋体"));
		HGDIOBJ oldFont = pDC->SelectObject(font);

		LogPainterFactory::GetInstance()->GetLineDetailPainter()->Draw(pDC->GetSafeHdc(), clientRect, *item);

		pDC->SelectObject(oldFont);
		::DeleteObject(font);
	}
}


// CLogDetailView 诊断

#ifdef _DEBUG
void CLogDetailView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogDetailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif

CWinUIDoc* CLogDetailView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinUIDoc)));
	return (CWinUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogDetailView 消息处理程序


void CLogDetailView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->logQuery->registerObserver(this);
}


void CLogDetailView::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	GetDocument()->logQuery->unregisterObserver(this);

	__super::PostNcDestroy();
}

void CLogDetailView::NotifyGeneralDataChanged()
{
	Invalidate();
}