#pragma once

#include "ControllerBase.h"
#include "ILogQuery.h"
#include "ICtrlView.h"

// LogCtrlController

class LogCtrlController : public ControllerBase<ILogQuery, ICtrlView> {
	DECLARE_DYNAMIC(LogCtrlController)

public:
	LogCtrlController(CWnd* parent);
	virtual ~LogCtrlController();

	enum { WM_COMMIT = WM_USER };

private:

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeCriteria();
};


