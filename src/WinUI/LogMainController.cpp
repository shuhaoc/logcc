// LogMainController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogMainController.h"
#include "LogCCDoc.h"
#include "LogItem.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"

// LogMainController

IMPLEMENT_DYNAMIC(LogMainController, CWnd)

LogMainController::LogMainController(CWnd* parent) : ControllerBase(parent)
{

}

LogMainController::~LogMainController()
{
}


BEGIN_MESSAGE_MAP(LogMainController, CWnd)
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// LogMainController 消息处理程序


void LogMainController::OnLButtonUp(UINT nFlags, CPoint point)
{
	const CLogCCDoc* viewData = static_cast<const CLogCCDoc*>(getViewData());
	unsigned i = (viewData->yScrollPos + point.y) / viewData->lineHeight;
	if (i < viewData->logQuery->getCurQueryResult()->getCount()) {
		LogItem* item = viewData->logQuery->getCurQueryResult()->getIndex(i);
		viewData->logQuery->setSelected(item);
		DEBUG_INFO(_T("选中行：") << i);
	}
}

void LogMainController::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// UNDONE: 下面一行复用
	CLogCCDoc* viewData = static_cast<CLogCCDoc*>(getViewData());
	DEBUG_INFO(_T("滚动位置：") << viewData->yScrollPos);

	// NOTICE:	很奇怪的现象，CScrollView在OnInitUpdate之外函数SetScrollSizes，
	//			如果设置的高度小于ClientRect，虽然没有显示滚动条仍然可以滚动，这里特殊处理一下，禁止滚动
	if (viewData->clientRect.Height() >= viewData->length) return;


	if (::GetKeyState(VK_CONTROL) & 0x80000000)
	{
		if (nChar == VK_HOME)
		{
			// 跳到第一页
			viewData->yScrollPos = 0;
		}
		else if (nChar == VK_END)
		{
			// 跳到最后一页，多出没事
			viewData->yScrollPos = (viewData->logQuery->getCurQueryResult()->getCount()) * viewData->lineHeight;
		}
		else if (nChar == VK_UP)
		{
			// 向上1行
			viewData->yScrollPos -= viewData->lineHeight;
			viewData->yScrollPos = max(viewData->yScrollPos, 0);
		}
		else if (nChar == VK_DOWN)
		{
			// 向下1行
			viewData->yScrollPos += viewData->lineHeight;
		}
	}
	if (nChar == VK_PRIOR)
	{
		// 向上1页
		viewData->yScrollPos -= viewData->clientRect.Height() / viewData->lineHeight * viewData->lineHeight;
		viewData->yScrollPos = max(viewData->yScrollPos, 0);
	}
	else if (nChar == VK_NEXT)
	{
		// 向下1页
		viewData->yScrollPos += viewData->clientRect.Height() / viewData->lineHeight * viewData->lineHeight;
	}
	viewData->logQuery->scrollTo(viewData->yScrollPos);
}

BOOL LogMainController::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	DEBUG_INFO(_T("zDelta = ") << zDelta << _T(", x = ") << pt.x << _T(", y = ") << pt.y);
	
	CLogCCDoc* viewData = static_cast<CLogCCDoc*>(getViewData());
	DEBUG_INFO(_T("滚动位置：") << viewData->yScrollPos);
	
	if (viewData->clientRect.Height() >= viewData->length) return FALSE;

	int delta = viewData->clientRect.Height() / viewData->lineHeight / 2 * viewData->lineHeight;
	if (zDelta < 0)
	{
		// 向下半页
		viewData->yScrollPos += delta;
	}
	else
	{
		// 向上半页
		viewData->yScrollPos -= delta;
		viewData->yScrollPos = max(viewData->yScrollPos, 0);
	}
	viewData->logQuery->scrollTo(viewData->yScrollPos);
	return TRUE;
}
