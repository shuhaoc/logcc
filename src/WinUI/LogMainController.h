﻿#pragma once

#include "ControllerBase.h"
#include "ILogQuery.h"
#include "MainViewData.h"

// LogMainController

class LogMainController : public ControllerBase<ILogQuery, MainViewData>
{
	DECLARE_DYNAMIC(LogMainController)

public:
	LogMainController(CWnd* parent);
	virtual ~LogMainController();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


