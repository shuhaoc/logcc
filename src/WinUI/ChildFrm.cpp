
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "LogCC.h"

#include "ChildFrm.h"
#include "LogCCDoc.h"
#include "LogCtrlView.h"
#include "LogMainView.h"
#include "LogTextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
	: m_bSplitterCreated(false)
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
#define LOGCC_WINUI_USE_SPLIT_VIEW
#ifndef LOGCC_WINUI_USE_SPLIT_VIEW
	m_wndSplitter.Create(this,
		2, 2,			// TODO: 调整行数和列数
		CSize(10, 10),	// TODO: 调整最小窗格大小
		pContext);
#else
	m_wndSplitter.CreateStatic(this, 3, 1);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLogCtrlView), CSize(10, 10), pContext);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CLogMainView), CSize(10, 10), pContext);
	m_wndSplitter.CreateView(2, 0, RUNTIME_CLASS(CLogTextView), CSize(10, 10), pContext);
	m_bSplitterCreated = true;
#endif
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetWindowRect(&rect);
	if(m_bSplitterCreated)  // m_bSplitterCreated set in OnCreateClient
	{
		m_wndSplitter.SetColumnInfo(0, rect.Width(), 10);
		m_wndSplitter.SetRowInfo(0, 50, 10); 
		m_wndSplitter.SetRowInfo(1, max(rect.Height() - 200, 10), 10); 
		m_wndSplitter.SetRowInfo(2, 150, 10); 
		m_wndSplitter.RecalcLayout();
	}
}
