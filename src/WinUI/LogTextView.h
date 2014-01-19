#pragma once

#include "ILogQueryObserver.h"
#include "afxwin.h"

// CLogTextView 窗体视图

class CLogTextView : public CFormView, public ILogQueryObserver
{
	DECLARE_DYNCREATE(CLogTextView)

protected:
	CLogTextView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogTextView();

public:
	CLogCCDoc* GetDocument() const;
	enum { IDD = IDD_LOGTEXTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void NotifyGeneralDataChanged();

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


#ifndef _DEBUG  // LogMainView.cpp 中的调试版本
inline CLogCCDoc* CLogTextView::GetDocument() const
   { return reinterpret_cast<CLogCCDoc*>(m_pDocument); }
#endif

