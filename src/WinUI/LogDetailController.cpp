// LogDetailController.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LogDetailController.h"


// LogDetailController

IMPLEMENT_DYNAMIC(LogDetailController, CWnd)

LogDetailController::LogDetailController(CWnd* parent) : ControllerBase<ILogQuery, DetailViewData>(parent) {

}

LogDetailController::~LogDetailController() {
}


BEGIN_MESSAGE_MAP(LogDetailController, CWnd)
END_MESSAGE_MAP()



// LogDetailController ��Ϣ�������


