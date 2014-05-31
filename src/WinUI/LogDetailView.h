#pragma once

#include "afxwin.h"
#include "ViewBase.h"
#include "ILogQuery.h"
#include "ILogQueryObserver.h"
#include "IDetailView.h"

// CLogDetailView 窗体视图

class CLogDetailView : public CFormView, public ViewBase<ILogQuery, IDetailView>, public ILogQueryObserver {
	DECLARE_DYNCREATE(CLogDetailView)

protected:
	CLogDetailView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogDetailView();

public:
	enum { IDD = IDD_LOGTEXTVIEW };

	virtual void onGeneralDataChanged();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void PostNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CEdit textEdit;
};

