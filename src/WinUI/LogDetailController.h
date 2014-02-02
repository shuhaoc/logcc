#pragma once

#include "ControllerBase.h"
#include "ILogQuery.h"
#include "IDetailView.h"

// LogDetailController

class LogDetailController : public ControllerBase<ILogQuery, IDetailView> {
	DECLARE_DYNAMIC(LogDetailController)

public:
	LogDetailController(CWnd* parent);
	virtual ~LogDetailController();

protected:
	DECLARE_MESSAGE_MAP()
};


