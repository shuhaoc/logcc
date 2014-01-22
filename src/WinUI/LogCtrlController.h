#pragma once

#include "ControllerBase.h"

// LogCtrlController

class LogCtrlController : public ControllerBase
{
	DECLARE_DYNAMIC(LogCtrlController)

public:
	LogCtrlController(CWnd* parent);
	virtual ~LogCtrlController();

	enum { WM_COMMIT = WM_USER };

private:

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeCriteria();
	afx_msg LRESULT OnCommit(WPARAM wParam = 0, LPARAM lParam = 0);
};


