
// WinUIDoc.cpp : CWinUIDoc 类的实现
//

#include "stdafx.h"
#include "WinUIDoc.h"
#include "ModelFactory.h"
#include "ILogQuery.h"
#include "LogQueryResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MULTI_THREAD_GET_LINE

// CWinUIDoc

IMPLEMENT_DYNCREATE(CWinUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinUIDoc, CDocument)
END_MESSAGE_MAP()


// CWinUIDoc 构造/析构

CWinUIDoc::CWinUIDoc()
	: queryResult(NULL)
{
	logQuery = ModelFactory::GetInstance()->CreateLogQuery();
	queryResult = new LogQueryResult();
}

CWinUIDoc::~CWinUIDoc()
{
	delete logQuery;
	delete queryResult;
}

void CWinUIDoc::setQueryResult(LogQueryResult* queryResult) {
	delete this->queryResult;
	this->queryResult = queryResult;
}

BOOL CWinUIDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	m_strPathName = lpszPathName;
	clock_t begin = ::clock();
	logQuery->load(m_strPathName.GetBuffer());
	clock_t end = ::clock();
	DEBUG_INFO(end - begin);

	setQueryResult(logQuery->query(_T("")));

	return TRUE;
}

BOOL CWinUIDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}

// CWinUIDoc 命令
