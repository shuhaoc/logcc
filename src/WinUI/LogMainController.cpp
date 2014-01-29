// LogMainController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogMainController.h"
#include "LogCCDoc.h"
#include "LogItem.h"
#include "LogQueryResult.h"

// LogMainController

IMPLEMENT_DYNAMIC(LogMainController, CWnd)

LogMainController::LogMainController(CWnd* parent) : ControllerBase<ILogQuery, MainViewData>(parent) {

}

LogMainController::~LogMainController() {
}


BEGIN_MESSAGE_MAP(LogMainController, CWnd)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// LogMainController 消息处理程序


void LogMainController::OnLButtonUp(UINT /*nFlags*/, CPoint /*point*/) {
	if (getViewData()->queryResult && getViewData()->selectedLine < getViewData()->queryResult->getCount()) {
		LogItem* item = getViewData()->queryResult->getIndex(getViewData()->selectedLine);
		getModel()->setSelected(item);
		DEBUG_INFO(_T("选中行：") << getViewData()->selectedLine);
	}
}