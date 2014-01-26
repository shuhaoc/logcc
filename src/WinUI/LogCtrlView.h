#pragma once
#include "afxwin.h"
#include "ViewBase.h"
#include "ILogQuery.h"
#include "CtrlViewData.h"

class CLogCCDoc;

// CLogCtrlView 窗体视图

class CLogCtrlView : public CFormView, public ViewBase<ILogQuery, CtrlViewData>
{
	DECLARE_DYNCREATE(CLogCtrlView)

protected:
	CLogCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogCtrlView();
	CLogCCDoc* GetDocument() const;
	
	virtual void onSubmit();

public:
	enum { IDD = IDD_LOGCTRLVIEW };

private:
	// 搜索条件
	CEdit criteriaEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//
	DECLARE_MESSAGE_MAP()
	// virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


#ifndef _DEBUG  // LogMainView.cpp 中的调试版本
inline CLogCCDoc* CLogCtrlView::GetDocument() const
   { return reinterpret_cast<CLogCCDoc*>(m_pDocument); }
#endif
