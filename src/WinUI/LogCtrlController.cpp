// LogCtrlController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCtrlController.h"
#include "Resource.h"
#include "LogCCDoc.h"

// LogCtrlController

IMPLEMENT_DYNAMIC(LogCtrlController, CWnd)

LogCtrlController::LogCtrlController(CWnd* parent) : ControllerBase<ILogQuery, CtrlViewData>(parent) {

}

LogCtrlController::~LogCtrlController() {
}


BEGIN_MESSAGE_MAP(LogCtrlController, CWnd)
	ON_EN_CHANGE(IDC_CRITERIA, &LogCtrlController::OnEnChangeCriteria)
	ON_MESSAGE(WM_COMMIT, &LogCtrlController::OnCommit)
END_MESSAGE_MAP()



// LogCtrlController 消息处理程序


void LogCtrlController::OnEnChangeCriteria() {
	OnCommit();
}

afx_msg LRESULT LogCtrlController::OnCommit(WPARAM wParam, LPARAM lParam) {
	updateViewData();
	DEBUG_INFO(getViewData()->criteria);
	getModel()->query(getViewData()->criteria);
	return 0;
}
