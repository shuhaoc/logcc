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
	: CFormView(CLogCtrlView::IDD) {

}

CLogCtrlView::~CLogCtrlView() {
}

void CLogCtrlView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CRITERIA, criteriaEdit);
}

tstring CLogCtrlView::getCriteria() {
	CString criteria;
	criteriaEdit.GetWindowText(criteria);
	return criteria.GetBuffer();
}

BEGIN_MESSAGE_MAP(CLogCtrlView, CFormView)
	ON_EN_CHANGE(IDC_CRITERIA, &CLogCtrlView::OnEnChangeCriteria)
END_MESSAGE_MAP()


// CLogCtrlView 消息处理程序

void CLogCtrlView::OnEnChangeCriteria()
{
	getModel()->query(getCriteria());
}
