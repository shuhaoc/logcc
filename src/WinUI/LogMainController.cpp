// LogMainController.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LogMainController.h"
#include "LogCCDoc.h"
#include "LogItem.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"

// LogMainController

IMPLEMENT_DYNAMIC(LogMainController, CWnd)

LogMainController::LogMainController(CWnd* parent) : ControllerBase(parent)
{

}

LogMainController::~LogMainController()
{
}


BEGIN_MESSAGE_MAP(LogMainController, CWnd)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// LogMainController ��Ϣ�������


void LogMainController::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	const CLogCCDoc* viewData = static_cast<const CLogCCDoc*>(getViewData());
	unsigned i = (viewData->yScrollPos + point.y) / viewData->lineHeight;
	if (i < viewData->logQuery->getCurQueryResult()->getCount()) {
		LogItem* item = viewData->logQuery->getCurQueryResult()->getIndex(i);
		viewData->logQuery->setSelected(item);
		DEBUG_INFO(_T("ѡ���У�") << i);
	}
}