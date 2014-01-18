
// WinUIDoc.h : CWinUIDoc 类的接口
//


#pragma once

class ILogQuery;
class LogQueryResult;

class CWinUIDoc : public CDocument
{
protected: // 仅从序列化创建
	CWinUIDoc();
	DECLARE_DYNCREATE(CWinUIDoc)

// 特性
public:

	ILogQuery* logQuery;

// 操作
public:

// 重写
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// 实现
public:
	virtual ~CWinUIDoc();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};
