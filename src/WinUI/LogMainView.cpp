
// WinUIView.cpp : CWinUIView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WinUI.h"
#endif

#include "WinUIDoc.h"
#include "WinUIView.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"
#include "LogItem.h"
#include "ILogItemPainter.h"
#include "LogPainterFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const unsigned LineHeight = 15;

// CWinUIView

IMPLEMENT_DYNCREATE(CWinUIView, CScrollView)

BEGIN_MESSAGE_MAP(CWinUIView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CWinUIView 构造/析构

CWinUIView::CWinUIView() : length(0)
{
	// TODO: 在此处添加构造代码

}

CWinUIView::~CWinUIView()
{
}

BOOL CWinUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CWinUIView 绘制

void CWinUIView::OnDraw(CDC* pDC)
{
	CWinUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(clientRect);
	DEBUG_INFO(_T("客户区区域：") << clientRect.left << ", " << clientRect.top << ", "
		<< clientRect.right << ", " << clientRect.bottom);

	HDC memDC = ::CreateCompatibleDC(pDC->GetSafeHdc());

	HBITMAP memBmp = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), clientRect.Width(), clientRect.Height());
	HGDIOBJ oldBmp = ::SelectObject(memDC, memBmp);

	HBRUSH bkgdBrush = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	::FillRect(memDC, clientRect, bkgdBrush);

	HFONT font = ::CreateFont(LineHeight - 1, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH, _T("新宋体"));
	HGDIOBJ oldFont = ::SelectObject(memDC, font);

	// TODO: 在此处为本机数据添加绘制代码
	DEBUG_INFO(_T("重绘"));

	CPoint scrollPosition = GetScrollPosition();
	DEBUG_INFO(_T("滚动条位置：") << scrollPosition.x << ", " << scrollPosition.y);

	// 顶部可以显示半行
	int yLogLineStart = scrollPosition.y % LineHeight == 0 ? 0 : scrollPosition.y % LineHeight - LineHeight;
	unsigned beginLine = scrollPosition.y / LineHeight;
	// +1是为了底部能显示半行
	unsigned endLine = (scrollPosition.y + clientRect.Height()) / LineHeight + 1;
	endLine = min(endLine, GetDocument()->logQuery->getCurQueryResult()->getCount());
	DEBUG_INFO(_T("行号区间：") << beginLine << ", " << endLine);

	vector<LogItem*> vecLines = GetDocument()->logQuery->getCurQueryResult()->getRange(beginLine, endLine);
	for (unsigned i = 0; i < vecLines.size(); i++) {
		LogItem* item = vecLines[i];
		CRect rect = clientRect;
		rect.top = yLogLineStart + i * LineHeight;
		rect.bottom = rect.top + LineHeight;
		LogPainterFactory::GetInstance()->GetSingleLinePainter()->Draw(memDC, rect, *item);
	}

	::BitBlt(pDC->GetSafeHdc(), scrollPosition.x, scrollPosition.y, clientRect.Width(), clientRect.Height(),
		memDC, 0, 0, SRCCOPY);

	::SelectObject(memDC, oldFont);
	::DeleteObject(font);
	::SelectObject(memDC, oldBmp);
	::DeleteObject(memBmp);
	::DeleteDC(memDC);
}

void CWinUIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	GetDocument()->logQuery->registerObserver(this);

	UpdateScroll();
	SetFocus();
}

void CWinUIView::PostNcDestroy()
{
	GetDocument()->logQuery->unregisterObserver(this);
	__super::PostNcDestroy();
}

void CWinUIView::UpdateScroll()
{
	CRect clientRect;
	GetClientRect(clientRect);
	CSize totalSize;
	totalSize.cx = clientRect.Width();
	// 加1是为了最后一行一定可见
	totalSize.cy = length = (GetDocument()->logQuery->getCurQueryResult()->getCount() + 1) * LineHeight;
#define LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
#ifdef LOGCC_WINUI_CUSTOMIZE_PAGE_SIZE_LINE_SIZE
	CSize pageSize(clientRect.Width(), clientRect.Height() / LineHeight * LineHeight);
	CSize lineSize(clientRect.Width(), LineHeight);
	SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
#else
	SetScrollSizes(MM_TEXT, totalSize);
#endif
}

void CWinUIView::NotifyQueryResultChanged()
{
	UpdateScroll();
	Invalidate();
}

// CWinUIView 打印


void CWinUIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CWinUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CWinUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CWinUIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinUIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinUIView 诊断

#ifdef _DEBUG
void CWinUIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWinUIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinUIDoc* CWinUIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinUIDoc)));
	return (CWinUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinUIView 消息处理程序

BOOL CWinUIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
#ifdef LOGCC_WINUI_USE_DEFAULT_ERASE_BACKGROUND
	return CScrollView::OnEraseBkgnd(pDC);
#else
	return TRUE;
#endif
}

void CWinUIView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint scrollPosition = GetScrollPosition();
	unsigned i = (scrollPosition.y + point.y) / LineHeight;
	if (i < GetDocument()->logQuery->getCurQueryResult()->getCount()) {
		LogItem* item = GetDocument()->logQuery->getCurQueryResult()->getIndex(i);
		GetDocument()->logQuery->setSelected(item);
		DEBUG_INFO(_T("选中行：") << i);
	}
	// UNDONE: 使用Model驱动而不是Controller
	Invalidate();

	CScrollView::OnLButtonUp(nFlags, point);
}


void CWinUIView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	UpdateScroll();
}

void CWinUIView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nSBCode == SB_ENDSCROLL)
	{
		Invalidate();
	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CWinUIView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint curPosition = GetScrollPosition();
	DEBUG_INFO(_T("滚动位置：") << curPosition.x << _T(", ") << curPosition.y);

	// NOTICE: 很奇怪的现象，CScrollView在OnInitUpdate之外函数SetScrollSizes，
	//			如果设置的高度小于ClientRect，虽然没有显示滚动条仍然可以滚动，这里特殊处理一下，禁止滚动
	CRect rect;
	GetClientRect(rect);
	if (rect.Height() >= length) return;


	if (::GetKeyState(VK_CONTROL) & 0x80000000)
	{
		if (nChar == VK_HOME)
		{
			// 跳到第一页
			curPosition.y = 0;
		}
		else if (nChar == VK_END)
		{
			// 跳到最后一页，多出没事
			curPosition.y = (GetDocument()->logQuery->getCurQueryResult()->getCount()) * LineHeight;
		}
		else if (nChar == VK_UP)
		{
			// 向上1行
			curPosition.y -= LineHeight;
			curPosition.y = max(curPosition.y, 0);
		}
		else if (nChar == VK_DOWN)
		{
			// 向下1行
			curPosition.y += LineHeight;
		}
	}
	if (nChar == VK_PRIOR)
	{
		// 向上1页
		CRect clientRect;
		GetClientRect(clientRect);
		curPosition.y -= clientRect.Height() / LineHeight * LineHeight;
		curPosition.y = max(curPosition.y, 0);
	}
	else if (nChar == VK_NEXT)
	{
		// 向下1页
		CRect clientRect;
		GetClientRect(clientRect);
		curPosition.y += clientRect.Height() / LineHeight * LineHeight;
	}
	ScrollToPosition(curPosition);

	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CWinUIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DEBUG_INFO(_T("zDelta = ") << zDelta << _T(", x = ") << pt.x << _T(", y = ") << pt.y);

	CPoint curPosition = GetScrollPosition();
	DEBUG_INFO(_T("滚动位置：") << curPosition.x << _T(", ") << curPosition.y);

	CRect rect;
	GetClientRect(rect);
	if (rect.Height() >= length) return CScrollView::OnMouseWheel(nFlags, zDelta, pt);

	if (zDelta < 0)
	{
		// 向下10行
		curPosition.y += LineHeight * 10;
	}
	else
	{
		// 向上10行
		curPosition.y -= LineHeight * 10;
		curPosition.y = max(curPosition.y, 0);
	}
	ScrollToPosition(curPosition);

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}