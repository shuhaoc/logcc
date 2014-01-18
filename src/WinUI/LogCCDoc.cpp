
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
{
	logQuery = ModelFactory::GetInstance()->CreateLogQuery();
}

CWinUIDoc::~CWinUIDoc()
{
	delete logQuery;
}

// CWinUIDoc 命令

BOOL CWinUIDoc::OnOpenDocument(LPCTSTR lpszPathName)
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

BOOL CWinUIDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}
