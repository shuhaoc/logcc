
// LogCCDoc.h : CLogCCDoc 类的接口
//


#pragma once

#include "IModelFactory.h"
#include "ILogQuery.h"


class CLogCCDoc : public CDocument, public IModelFactory<ILogQuery>
{
protected: // 仅从序列化创建
	CLogCCDoc();
	DECLARE_DYNCREATE(CLogCCDoc)

// 特性
public:
	ILogQuery* logQuery;

// 操作
public:

// 重写
public:
	virtual ILogQuery* getModel() { return logQuery; }

	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// 实现
public:
	virtual ~CLogCCDoc();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
};
