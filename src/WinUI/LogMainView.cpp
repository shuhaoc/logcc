
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
#include "ILogItemPainter.h"
#include "LogPainterFactory.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const unsigned LineHeight = 15;

// CLogMainView

IMPLEMENT_DYNCREATE(CLogMainView, CScrollView)

BEGIN_MESSAGE_MAP(CLogMainView, CScrollView)
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CLogMainView 构造/析构

CLogMainView::CLogMainView() {
}

CLogMainView::~CLogMainView() {
}

// CLogMainView 绘制

void CLogMainView::OnDraw(CDC* pDC) {
	CRect clientRect;
	GetClientRect(clientRect);
	DEBUG_INFO(_T("客户区区域：") << clientRect.left << ", " << clientRect.top << ", "
	           << clientRect.right << ", " << clientRect.bottom);

	HDC memDC = ::CreateCompatibleDC(pDC->GetSafeHdc());

	HBITMAP memBmp = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), clientRect.Width(), clientRect.Height());
	HGDIOBJ oldBmp = ::SelectObject(memDC, memBmp);

	HBRUSH bkgdBrush = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	::FillRect(memDC, clientRect, bkgdBrush);

	HFONT font = ::CreateFont(LineHeight - 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                          DEFAULT_QUALITY, FIXED_PITCH, _T("新宋体"));
	HGDIOBJ oldFont = ::SelectObject(memDC, font);

	DEBUG_INFO(_T("重绘"));

	CPoint scrollPosition = GetScrollPosition();
	DEBUG_INFO(_T("滚动条位置：") << scrollPosition.x << ", " << scrollPosition.y);

	if (queryResult) {
		// 顶部可以显示半行
		int yLogLineStart = scrollPosition.y % LineHeight == 0 ? 0 : (scrollPosition.y % LineHeight) * -1;
		unsigned beginLine = scrollPosition.y / LineHeight;
		// +1是为了底部能显示半行
		unsigned endLine = (scrollPosition.y + clientRect.Height()) / LineHeight + 1;
		endLine = min(endLine, queryResult->getCount());
		DEBUG_INFO(_T("行号区间：") << beginLine << ", " << endLine);

		vector<LogItem*> vecLines = queryResult->getRange(beginLine, endLine);
		for (unsigned i = 0; i < vecLines.size(); i++) {
			LogItem* item = vecLines[i];
			CRect rect = clientRect;
			rect.top = yLogLineStart + i * LineHeight;
			rect.bottom = rect.top + LineHeight;
			LogPainterFactory::GetInstance()->GetSingleLinePainter()->Draw(memDC, rect, *item);
		}
	}

	::BitBlt(pDC->GetSafeHdc(), scrollPosition.x, scrollPosition.y, clientRect.Width(), clientRect.Height(),
	         memDC, 0, 0, SRCCOPY);

	::SelectObject(memDC, oldFont);
	::DeleteObject(font);
	::SelectObject(memDC, oldBmp);
	::DeleteObject(memBmp);
	::DeleteDC(memDC);
}

void CLogMainView::OnInitialUpdate() {
	CScrollView::OnInitialUpdate();

	getModel()->registerObserver(this);

	ResetScrollSize();
	SetFocus();
}

void CLogMainView::PostNcDestroy() {
	getModel()->unregisterObserver(this);
	__super::PostNcDestroy();
}

void CLogMainView::ResetScrollSize() {
	CRect clientRect;
	GetClientRect(clientRect);
	totalSize.cx = 0;
	// 加1是为了最后一行一定可见
	totalSize.cy = (queryResult ? queryResult->getCount() + 1 : 0) * LineHeight;
#define LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
#ifdef LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
	CSize pageSize(clientRect.Width(), clientRect.Height() / LineHeight * LineHeight);
	CSize lineSize(clientRect.Width(), LineHeight);
	SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
#else
	SetScrollSizes(MM_TEXT, totalSize);
#endif
#define LOGCC_WINUI_SCROLL_TO_END_ON_UPDATE
#ifdef LOGCC_WINUI_SCROLL_TO_END_ON_UPDATE
	int y = totalSize.cy - clientRect.Height();
	ScrollToPosition(CPoint(0, max(y, 0)));
#endif
}

void CLogMainView::onGeneralDataChanged() {
	Invalidate();
}

void CLogMainView::onQueryResultChanged(const tstring& criteria, LogQueryResult* queryResult) {
	CFrameWnd* activeFrame = static_cast<CMainFrame*>(::AfxGetMainWnd())->GetActiveFrame();
	if (activeFrame == GetParentFrame()) {
		this->curCriteria = criteria;
		this->queryResult = queryResult;
		ResetScrollSize();
		Invalidate();
	}
}

void CLogMainView::onFileChanged() {
	this->queryResult = getModel()->query(this->curCriteria, true);
	ResetScrollSize();
	Invalidate();
}

// CLogMainView 消息处理程序

BOOL CLogMainView::OnEraseBkgnd(CDC* /*pDC*/) {
#ifdef LOGCC_WINUI_USE_DEFAULT_ERASE_BACKGROUND
	return CScrollView::OnEraseBkgnd(pDC);
#else
	return TRUE;
#endif
}

void CLogMainView::OnVScroll(UINT nSBCode, UINT /*nPos*/, CScrollBar* /*pScrollBar*/) {
	// 以下代码源自：http://blog.csdn.net/xiaji2007/article/details/5744111
	// 并予以修改
	SCROLLINFO si = { 0 };
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_VERT, &si);
	int lastPos = si.nPos;
	switch (nSBCode) {
	case SB_TOP:
		si.nPos = si.nMin;
		break;
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;
	case SB_LINEUP:
		si.nPos -= LineHeight;
		break;
	case SB_LINEDOWN:
		si.nPos += LineHeight;
		break;
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
	default:
		break;
	}
	si.fMask = SIF_POS;
	SetScrollInfo(SB_VERT, &si);
	if (lastPos!=si.nPos) {
		::ScrollWindow(m_hWnd, 0, lastPos - si.nPos, NULL, NULL);
	}
	Invalidate();
}

void CLogMainView::OnMouseMove(UINT nFlags, CPoint point) {
	if (GetForegroundWindow() == AfxGetMainWnd()) {
		SetFocus();
	}
	__super::OnMouseMove(nFlags, point);
}

void CLogMainView::onSubmit() {
}

BOOL CLogMainView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CRect clientRect;
	GetClientRect(clientRect);

	int yScrollPos = GetScrollPosition().y;
	if (clientRect.Height() >= totalSize.cy) return FALSE;

	int delta = 3 * LineHeight;
	if (zDelta < 0) {
		// 向下3行
		yScrollPos += delta;
	} else {
		// 向上3行
		yScrollPos -= delta;
		yScrollPos = max(yScrollPos, 0);
	}
	ScrollToPosition(CPoint(0, yScrollPos));
	DEBUG_INFO(_T("滚动位置：") << yScrollPos);
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}


void CLogMainView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CRect clientRect;
	GetClientRect(clientRect);

	if (nChar == VK_UP) {
		// 选中上一行
		LogItem* item = getModel()->getSelected();
		if (item) {
			unsigned i = queryResult->findIndex(item);
			if (i > 0 && i != 0xFFFFFFFF) {
				i--;
				getModel()->setSelected(queryResult->getIndex(i));
			}
		}
	} else if (nChar == VK_DOWN) {
		// 选中下一行
		LogItem* item = getModel()->getSelected();
		if (item) {
			unsigned i = queryResult->findIndex(item);
			if (i != 0xFFFFFFFF && i < queryResult->getCount() - 1) {
				i++;
				getModel()->setSelected(queryResult->getIndex(i));
			}
		}
	} else {
		// 以下是滚动的情况
		// NOTICE:	很奇怪的现象，CScrollView在OnInitUpdate之外函数SetScrollSizes，
		//			如果设置的高度小于ClientRect，虽然没有显示滚动条仍然可以滚动，这里特殊处理一下，禁止滚动
		if (clientRect.Height() >= totalSize.cy) return;

		int yScrollPos = GetScrollPosition().y;
		if (::GetKeyState(VK_CONTROL) & 0x80000000) {
			if (nChar == VK_HOME) {
				// 跳到第一页
				yScrollPos = 0;
			} else if (nChar == VK_END) {
				// 跳到最后一页，多出没事
				yScrollPos = (queryResult->getCount()) * LineHeight;
			} else if (nChar == VK_UP) {
				// 向上1行
				yScrollPos -= LineHeight;
				yScrollPos = max(yScrollPos, 0);
			} else if (nChar == VK_DOWN) {
				// 向下1行
				yScrollPos += LineHeight;
			}
		}
		if (nChar == VK_PRIOR) {
			// 向上1页
			yScrollPos -= clientRect.Height() / LineHeight * LineHeight;
			yScrollPos = max(yScrollPos, 0);
		} else if (nChar == VK_NEXT) {
			// 向下1页
			yScrollPos += clientRect.Height() / LineHeight * LineHeight;
		}
		ScrollToPosition(CPoint(0, yScrollPos));
		DEBUG_INFO(_T("滚动位置：") << yScrollPos);
	}
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLogMainView::OnLButtonUp(UINT nFlags, CPoint point) {
	int yScrollPos = GetScrollPosition().y;
	DEBUG_INFO(yScrollPos);
	this->selectedLine = (yScrollPos + point.y) / LineHeight;
	__super::OnLButtonUp(nFlags, point);
}
