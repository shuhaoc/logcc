﻿
// LogMainView.h : CLogMainView 类的接口
//

#pragma once

#include "ILogQueryObserver.h"


class CLogMainView : public CScrollView, public ILogQueryObserver
{
protected: // 仅从序列化创建
	CLogMainView();
	DECLARE_DYNCREATE(CLogMainView)

// 特性
public:
	CLogCCDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void PostNcDestroy();
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLogMainView();
#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void NotifyGeneralDataChanged();
	virtual void NotifyQueryResultChanged();

private:
	void UpdateScroll();

	int length;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // LogMainView.cpp 中的调试版本
inline CLogCCDoc* CLogMainView::GetDocument() const
   { return reinterpret_cast<CLogCCDoc*>(m_pDocument); }
#endif
