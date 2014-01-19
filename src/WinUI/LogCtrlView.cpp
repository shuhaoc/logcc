// LogCtrlView.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCC.h"
#include "LogCtrlView.h"
#include "LogCCDoc.h"
#include "ILogQuery.h"

// CLogCtrlView

IMPLEMENT_DYNCREATE(CLogCtrlView, CFormView)

CLogCtrlView::CLogCtrlView()
	: CFormView(CLogCtrlView::IDD)
{

}

CLogCtrlView::~CLogCtrlView()
{
}

void CLogCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CRITERIA, criteriaEdit);
}

BEGIN_MESSAGE_MAP(CLogCtrlView, CFormView)
END_MESSAGE_MAP()

#ifdef _DEBUG
CLogCCDoc* CLogCtrlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogCCDoc)));
	return (CLogCCDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogCtrlView 消息处理程序


BOOL CLogCtrlView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CString criteria;
	criteriaEdit.GetWindowText(criteria);
	GetDocument()->criteria = criteria.GetBuffer();
	DEBUG_INFO(GetDocument()->criteria);

	return CFormView::OnCommand(wParam, lParam);
}
