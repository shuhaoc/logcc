﻿
// LogMainView.h : CLogMainView 类的接口
//

#pragma once

#include "ViewBase.h"
#include "ILogQuery.h"
#include "ILogQueryObserver.h"
#include "MainViewData.h"

class CLogMainView : public CScrollView, public ViewBase<ILogQuery, MainViewData>, public ILogQueryObserver
{
protected: // 仅从序列化创建
	CLogMainView();
	DECLARE_DYNCREATE(CLogMainView)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual void onSubmit();
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

	CSize totalSize;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


