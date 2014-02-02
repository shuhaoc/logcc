#pragma once
#include "afxwin.h"
#include "ViewBase.h"
#include "ILogQuery.h"
#include "ICtrlView.h"

class CLogCCDoc;

// CLogCtrlView 窗体视图

class CLogCtrlView : public CFormView, public ViewBase<ILogQuery, ICtrlView> {
	DECLARE_DYNCREATE(CLogCtrlView)

protected:
	CLogCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogCtrlView();

	virtual tstring getCriteria();

public:
	enum { IDD = IDD_LOGCTRLVIEW };

private:
	// 搜索条件
	CEdit criteriaEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
