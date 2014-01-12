
// WinUIView.cpp : CWinUIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CWinUIView ����/����

CWinUIView::CWinUIView()
{
	// TODO: �ڴ˴���ӹ������

}

CWinUIView::~CWinUIView()
{
}

BOOL CWinUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CWinUIView ����

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
		DEFAULT_QUALITY, FIXED_PITCH, _T("������"));
	HGDIOBJ oldFont = ::SelectObject(memDC, font);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//DEBUG_INFO("�ػ�");

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

	// TODO: �������ͼ�ĺϼƴ�С
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


// CWinUIView ��ӡ


void CWinUIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CWinUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CWinUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CWinUIView ���

#ifdef _DEBUG
void CWinUIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWinUIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinUIDoc* CWinUIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinUIDoc)));
	return (CWinUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinUIView ��Ϣ�������
void CWinUIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate();
	CScrollView::OnTimer(nIDEvent);
}


BOOL CWinUIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

//void CWinUIView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	if (lHint == CWinUIDoc::UpdateView_FileOPen) {
//		//CReadFileThread* thread = static_cast<CReadFileThread*>(
//		//	::AfxBeginThread(RUNTIME_CLASS(CReadFileThread), 0, 0, CREATE_SUSPENDED));
//		//thread->m_strFilePath = GetDocument()->GetPathName();
//		//thread->m_hwndCallback = GetSafeHwnd();
//		//thread->ResumeThread();
//	}
//}
