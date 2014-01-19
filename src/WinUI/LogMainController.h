#pragma once

#include "ControllerBase.h"

// LogMainController

class LogMainController : public ControllerBase
{
	DECLARE_DYNAMIC(LogMainController)

public:
	LogMainController(CWnd* parent);
	virtual ~LogMainController();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


