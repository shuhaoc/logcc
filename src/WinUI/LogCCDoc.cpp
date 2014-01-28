
// LogCCDoc.cpp : CLogCCDoc 类的实现
//

#include "stdafx.h"
#include "LogCCDoc.h"
#include "ModelFactory.h"
#include "LogQueryResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLogCCDoc

IMPLEMENT_DYNCREATE(CLogCCDoc, CDocument)

BEGIN_MESSAGE_MAP(CLogCCDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CLogCCDoc::OnUpdateFileSaveAs)
END_MESSAGE_MAP()


// CLogCCDoc 构造/析构

CLogCCDoc::CLogCCDoc() {
	logQuery = ModelFactory::GetInstance()->CreateLogQuery();
}

CLogCCDoc::~CLogCCDoc() {
	delete logQuery;
}

// CLogCCDoc 命令

BOOL CLogCCDoc::OnOpenDocument(LPCTSTR lpszPathName) {
	m_strPathName = lpszPathName;
#ifdef _DEBUG
	clock_t begin = ::clock();
#endif // _DEBUG
	logQuery->load(m_strPathName.GetBuffer());
#ifdef _DEBUG
	clock_t end = ::clock();
#endif // _DEBUG
	// UNDONE: 删除
	DEBUG_INFO(end - begin);

	logQuery->query(_T(""));

	return TRUE;
}

BOOL CLogCCDoc::OnSaveDocument(LPCTSTR /*lpszPathName*/) {
	// UNDONE: 另存为会进入此函数
	return TRUE;
}


BOOL CLogCCDoc::OnNewDocument() {
	// 禁用新建文档
	return FALSE;
}


void CLogCCDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI) {
	// UNDONE: 暂时禁用另存为，实现后去掉此函数
	pCmdUI->Enable(FALSE);
}
