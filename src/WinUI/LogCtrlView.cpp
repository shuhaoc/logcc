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
	, criteria(_T(""))
{

}

CLogCtrlView::~CLogCtrlView()
{
}

void CLogCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRITERIA, criteria);
}

BEGIN_MESSAGE_MAP(CLogCtrlView, CFormView)
	ON_EN_CHANGE(IDC_CRITERIA, &CLogCtrlView::OnEnChangeCriteria)
END_MESSAGE_MAP()


#ifdef _DEBUG
CLogCCDoc* CLogCtrlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogCCDoc)));
	return (CLogCCDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogCtrlView 消息处理程序


void CLogCtrlView::OnEnChangeCriteria()
{
	UpdateData(TRUE);
	GetDocument()->criteria = criteria.GetBuffer();
}