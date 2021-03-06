﻿// LogDetailView.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCC.h"
#include "LogCCDoc.h"
#include "LogDetailView.h"
#include "ILogQuery.h"
#include "LogItem.h"


// CLogDetailView

IMPLEMENT_DYNCREATE(CLogDetailView, CFormView)

CLogDetailView::CLogDetailView()
	: CFormView(CLogDetailView::IDD) {

}

CLogDetailView::~CLogDetailView() {
}

void CLogDetailView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LINE_TEXT, textEdit);
}

BEGIN_MESSAGE_MAP(CLogDetailView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLogDetailView 消息处理程序


void CLogDetailView::onGeneralDataChanged() {
	LogItem* item = getModel()->getSelected();
	if (item) {
		textEdit.SetWindowText(item->text.c_str());
	}
}

void CLogDetailView::OnSize(UINT nType, int cx, int cy) {
	CFormView::OnSize(nType, cx, cy);

	if (textEdit.GetSafeHwnd()) {
		textEdit.MoveWindow(0, 0, cx, cy);
	}
}
