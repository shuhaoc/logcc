#pragma once

#include "ControllerBase.h"
#include "ILogQuery.h"
#include "DetailViewData.h"

// LogDetailController

class LogDetailController : public ControllerBase<ILogQuery, DetailViewData>
{
	DECLARE_DYNAMIC(LogDetailController)

public:
	LogDetailController(CWnd* parent);
	virtual ~LogDetailController();

protected:
	DECLARE_MESSAGE_MAP()
};


