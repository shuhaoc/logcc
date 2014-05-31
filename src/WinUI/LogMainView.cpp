
// LogMainView.cpp : CLogMainView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LogCC.h"
#endif

#include "LogCCDoc.h"
#include "LogMainView.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"
#include "LogItem.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLogMainView

IMPLEMENT_DYNCREATE(CLogMainView, ListScrollView)

BEGIN_MESSAGE_MAP(CLogMainView, ListScrollView)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CLogMainView 构造/析构

CLogMainView::CLogMainView() : queryResult(nullptr) {
}

CLogMainView::~CLogMainView() {
}

// CLogMainView 绘制

void CLogMainView::OnInitialUpdate() {
	ListScrollView::OnInitialUpdate();

	SetTimer(0, 500, NULL);
	SetFocus();
}

void CLogMainView::onQueryResultChanged(const tstring& criteria, LogQueryResult* queryResult) {
	CFrameWnd* activeFrame = static_cast<CMainFrame*>(::AfxGetMainWnd())->GetActiveFrame();
	if (activeFrame == GetParentFrame()) {
		this->curCriteria = criteria;
		this->queryResult = queryResult;
		transformQueryResult();
	}
}

void CLogMainView::onFileChanged() {
	this->queryResult = getModel()->query(this->curCriteria, true);
	transformQueryResult();
}

// CLogMainView 消息处理程序

void CLogMainView::OnMouseMove(UINT nFlags, CPoint point) {
	if (GetForegroundWindow() == AfxGetMainWnd()) {
		SetFocus();
	}
	ListScrollView::OnMouseMove(nFlags, point);
}

void CLogMainView::OnTimer(UINT_PTR nIDEvent)
{
	getModel()->query(_T(""));
	KillTimer(0);

	ListScrollView::OnTimer(nIDEvent);
}

void CLogMainView::transformQueryResult() {
	clear();
	vector<LogItem*> logItems = queryResult->getRange(0, queryResult->getCount());
	for_each(logItems.begin(), logItems.end(), [=] (LogItem* li) {
		common::tstringstream ss;
		ss << li->line << _T(" ") << li->text;

		insert(ss.str(), reinterpret_cast<void*>(li));
	});
	update();
}

void CLogMainView::onSelectedChanged() {
	LogItem* li = queryResult->getIndex(getSelectedIndex());
	getModel()->setSelected(li);
}
