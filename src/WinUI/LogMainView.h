
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
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void PostNcDestroy();

// 实现
public:
	virtual ~CLogMainView();

protected:
	virtual void onGeneralDataChanged();
	virtual void onQueryResultChanged();
	virtual void onScrollPositionChanged(int yPosition);

private:
	void UpdateScroll();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // LogMainView.cpp 中的调试版本
inline CLogCCDoc* CLogMainView::GetDocument() const
   { return reinterpret_cast<CLogCCDoc*>(m_pDocument); }
#endif

