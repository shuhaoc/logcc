// LogCtrlController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogCtrlController.h"
#include "Resource.h"
#include "LogCCDoc.h"
#include "ILogQuery.h"

// LogCtrlController

IMPLEMENT_DYNAMIC(LogCtrlController, CWnd)

LogCtrlController::LogCtrlController(CWnd* parent) : ControllerBase(parent)
{

}

LogCtrlController::~LogCtrlController()
{
}


BEGIN_MESSAGE_MAP(LogCtrlController, CWnd)
	ON_EN_CHANGE(IDC_CRITERIA, &LogCtrlController::OnEnChangeCriteria)
END_MESSAGE_MAP()



// LogCtrlController 消息处理程序


void LogCtrlController::OnEnChangeCriteria()
{
	const CLogCCDoc* viewData = static_cast<const CLogCCDoc*>(getViewData());
	viewData->logQuery->query(viewData->criteria);
}