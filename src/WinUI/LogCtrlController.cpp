// LogCtrlController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCtrlController.h"
#include "Resource.h"
#include "LogCCDoc.h"

// LogCtrlController

IMPLEMENT_DYNAMIC(LogCtrlController, CWnd)

LogCtrlController::LogCtrlController(CWnd* parent) : ControllerBase<ILogQuery, ICtrlView>(parent) {

}

LogCtrlController::~LogCtrlController() {
}


BEGIN_MESSAGE_MAP(LogCtrlController, CWnd)
	ON_EN_CHANGE(IDC_CRITERIA, &LogCtrlController::OnEnChangeCriteria)
END_MESSAGE_MAP()



// LogCtrlController 消息处理程序


void LogCtrlController::OnEnChangeCriteria() {
	DEBUG_INFO(getView()->getCriteria());
	getModel()->query(getView()->getCriteria());
}