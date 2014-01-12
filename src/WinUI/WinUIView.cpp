
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LINE_HEIGHT 15

// CWinUIView

IMPLEMENT_DYNCREATE(CWinUIView, CScrollView)

BEGIN_MESSAGE_MAP(CWinUIView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CWinUIView 构造/析构

CWinUIView::CWinUIView()
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

	HDC memDC = ::CreateCompatibleDC(pDC->GetSafeHdc());

	HBITMAP memBmp = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), clientRect.Width(), clientRect.Height());
	::SelectObject(memDC, memBmp);

	::SetBkMode(memDC, TRANSPARENT);

	HBRUSH bkgdBrush = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	::FillRect(memDC, clientRect, bkgdBrush);

	HFONT font = ::CreateFont(LINE_HEIGHT - 1, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH, _T("新宋体"));
	HGDIOBJ oldFont = ::SelectObject(memDC, font);

	// TODO: 在此处为本机数据添加绘制代码
	//DEBUG_INFO("重绘");

	CPoint scrollPosition = GetScrollPosition();
	//DEBUG_INFO(scrollPosition.x << ", " << scrollPosition.y);

	unsigned beginLine = scrollPosition.y / LINE_HEIGHT;
	unsigned endLine = (scrollPosition.y + clientRect.Height()) / LINE_HEIGHT;

	//DEBUG_INFO(beginLine << ", " << endLine);

	vector<string>& vecLines = GetDocument()->m_vecLines;
	for (size_t i = beginLine; i < min(endLine, vecLines.size()); i++)
	{
		ostringstream oss;
		oss << i + 1 << " " << vecLines[i];
		string line = oss.str();

		::TextOutA(memDC, 0, (i - beginLine) * LINE_HEIGHT, line.c_str(), line.size());
	}

	::BitBlt(pDC->GetSafeHdc(), scrollPosition.x, scrollPosition.y, clientRect.Width(), clientRect.Height(),
		memDC, 0, 0, SRCCOPY);

	//wostringstream ossLoad;
	//ossLoad << pDoc->m_nLoadTimespan;
	//wstring load = ossLoad.str();
	//pDC->TextOut(100, 0, load.c_str(), load.size());

	::DeleteObject(font);
	::DeleteObject(memBmp);
	::DeleteDC(memDC);
}

void CWinUIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 计算此视图的合计大小
	UpdateScroll();
	SetTimer(0, 500, NULL);
}

void CWinUIView::UpdateScroll()
{
	CRect clientRect;
	GetClientRect(clientRect);
	CSize totalSize;
	totalSize.cx = clientRect.Width();
	totalSize.cy = GetDocument()->m_vecLines.size() * LINE_HEIGHT;
	//CSize pageSize(clientRect.Width(), LINE_HEIGHT * 30);
	//CSize lineSize(clientRect.Width(), LINE_HEIGHT);
	//SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
	SetScrollSizes(MM_TEXT, totalSize);
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
void CWinUIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate();
	CScrollView::OnTimer(nIDEvent);
}


BOOL CWinUIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

//void CWinUIView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	if (lHint == CWinUIDoc::UpdateView_FileOPen) {
//		//CReadFileThread* thread = static_cast<CReadFileThread*>(
//		//	::AfxBeginThread(RUNTIME_CLASS(CReadFileThread), 0, 0, CREATE_SUSPENDED));
//		//thread->m_strFilePath = GetDocument()->GetPathName();
//		//thread->m_hwndCallback = GetSafeHwnd();
//		//thread->ResumeThread();
//	}
//}
