
// LogCCDoc.cpp : CLogCCDoc 类的实现
//

#include "stdafx.h"
#include "LogCCDoc.h"
#include "ModelFactory.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MULTI_THREAD_GET_LINE

// CLogCCDoc

IMPLEMENT_DYNCREATE(CLogCCDoc, CDocument)

BEGIN_MESSAGE_MAP(CLogCCDoc, CDocument)
END_MESSAGE_MAP()


// CLogCCDoc 构造/析构

CLogCCDoc::CLogCCDoc()
{
	logQuery = ModelFactory::GetInstance()->CreateLogQuery();
}

CLogCCDoc::~CLogCCDoc()
{
	delete logQuery;
}

// CLogCCDoc 命令

BOOL CLogCCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	m_strPathName = lpszPathName;
	clock_t begin = ::clock();
	logQuery->load(m_strPathName.GetBuffer());
	clock_t end = ::clock();
	DEBUG_INFO(end - begin);

	logQuery->query(_T(""));

	return TRUE;
}

BOOL CLogCCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// UNDONE: 另存为会进入此函数
	return TRUE;
}
