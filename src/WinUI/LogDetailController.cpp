// LogDetailController.cpp : 实现文件
//

#include "stdafx.h"
#include "LogDetailController.h"


// LogDetailController

IMPLEMENT_DYNAMIC(LogDetailController, CWnd)

LogDetailController::LogDetailController(CWnd* parent) : ControllerBase<ILogQuery, IDetailView>(parent) {

}

LogDetailController::~LogDetailController() {
}


BEGIN_MESSAGE_MAP(LogDetailController, CWnd)
END_MESSAGE_MAP()



// LogDetailController 消息处理程序


