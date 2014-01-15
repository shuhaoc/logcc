#pragma once

#include "ILogQueryObserver.h"

// CLogDetailView 视图

class CLogDetailView : public CView, public ILogQueryObserver
{
	DECLARE_DYNCREATE(CLogDetailView)

protected:
	CLogDetailView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogDetailView();

public:
	CWinUIDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void NotifyGeneralDataChanged();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void PostNcDestroy();
};


#ifndef _DEBUG  // WinUIView.cpp 中的调试版本
inline CWinUIDoc* CLogDetailView::GetDocument() const
   { return reinterpret_cast<CWinUIDoc*>(m_pDocument); }
#endif
