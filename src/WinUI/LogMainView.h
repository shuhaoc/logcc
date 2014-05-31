
// LogMainView.h : CLogMainView 类的接口
//

#pragma once

#include "ViewBase.h"
#include "ILogQuery.h"
#include "ILogQueryObserver.h"
#include "IMainView.h"
#include "ListScrollView.h"

class CLogMainView : public ListScrollView, public ViewBase<ILogQuery, IMainView>, public ILogQueryObserver {
protected: // 仅从序列化创建
	CLogMainView();
	DECLARE_DYNCREATE(CLogMainView)

// 特性
public:

// 操作
public:

// 重写
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void PostNcDestroy();

// 实现
public:
	virtual ~CLogMainView();

protected:
	virtual void onGeneralDataChanged();
	virtual void onQueryResultChanged(const tstring& criteria, LogQueryResult* queryResult);
	virtual void onFileChanged();

	virtual void onSelectedChanged();

private:
	void transformQueryResult();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};

