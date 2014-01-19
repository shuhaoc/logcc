
// LogCCDoc.h : CLogCCDoc 类的接口
//


#pragma once

class ILogQuery;
class LogQueryResult;

class CLogCCDoc : public CDocument
{
protected: // 仅从序列化创建
	CLogCCDoc();
	DECLARE_DYNCREATE(CLogCCDoc)

// 特性
public:

	mutable ILogQuery* logQuery;
	tstring criteria;

// 操作
public:

// 重写
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// 实现
public:
	virtual ~CLogCCDoc();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};
