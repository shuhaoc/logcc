#pragma once

#include "ControllerBase.h"

// LogCtrlController

class LogCtrlController : public ControllerBase
{
	DECLARE_DYNAMIC(LogCtrlController)

public:
	LogCtrlController(CWnd* parent);
	virtual ~LogCtrlController();

private:

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeCriteria();
};


