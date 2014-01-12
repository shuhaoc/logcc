
// WinUIDoc.cpp : CWinUIDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WinUI.h"
#endif

#include "WinUIDoc.h"

#include <propkey.h>

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
	// TODO: 在此添加一次性构造代码

}

CWinUIDoc::~CWinUIDoc()
{
}

//BOOL CWinUIDoc::OnNewDocument()
//{
//	if (!CDocument::OnNewDocument())
//		return FALSE;
//
//	// TODO: 在此添加重新初始化代码
//	// (SDI 文档将重用该文档)
//
//	return TRUE;
//}

// CWinUIDoc 序列化

void CWinUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CWinUIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CWinUIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CWinUIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWinUIDoc 诊断

#ifdef _DEBUG
void CWinUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinUIDoc 命令


BOOL CWinUIDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	m_strPathName = lpszPathName;
	clock_t begin = ::clock();
	ifstream file(m_strPathName, ios_base::in | ios_base::binary);
	if (!file.good()) {
		return FALSE;
	}

	file.seekg(0, ios_base::end);
	size_t length = static_cast<size_t>(file.tellg());
	file.seekg(0, ios_base::beg);

#ifdef MULTI_THREAD_GET_LINE

	size_t length1 = length / 2;
	size_t length2 = length - length1;

	char* buffer1 = new char[length1 + 1];
	char* buffer2 = new char[length2];

	streamsize read = 0;
	while (file.good() && length1 - read) {
		file.read(buffer1 + read, length1 - read);
		read += file.gcount();
	}
	buffer1[read] = 0;
	assert(read == length1);

	read = 0;
	while (file.good() && length2 - read) {
		file.read(buffer2 + read, length2 - read);
		read += file.gcount();
	}
	buffer2[read] = 0;
	assert(read == length2);

	vector<string> lines1, lines2;

	boost::thread_group workers;

	auto f = [] (char* buffer, vector<string>* lines) {
		istringstream iss(buffer);

		string line;
		while (iss.good()) {
			std::getline(iss, line);
			lines->push_back(line);
		}
	};

	workers.create_thread([f, buffer1, &lines1] () { f(buffer1, &lines1); });
	workers.create_thread([f, buffer2, &lines2] () { f(buffer2, &lines2); });
	workers.join_all();

	m_vecLines.insert(m_vecLines.end(), lines1.begin(), lines1.end());
	if (lines1.size() && lines1.rbegin()->size() && *m_vecLines.rbegin()->rbegin() != '\n') {
		m_vecLines.rbegin()->append(*lines2.begin());
		m_vecLines.insert(m_vecLines.end(), lines2.begin() + 1, lines2.end());
	} else {
		m_vecLines.insert(m_vecLines.end(), lines2.begin(), lines2.end());
	}
#else
	char* buffer = new char[length];
	streamsize read = 0;
	while (file.good() && length - read) {
		file.read(buffer + read, length - read);
		read += file.gcount();
	}
	buffer[read] = 0;
	assert(read == length);

	istringstream iss(buffer);

	string line;
	while (iss.good())
	{
		std::getline(iss, line);
		m_vecLines.push_back(line);
	}
#endif
	clock_t end = ::clock();
	DEBUG_INFO(end - begin);

	UpdateAllViews(NULL, UpdateView_FileOPen);
	return TRUE;
}


BOOL CWinUIDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CDocument::OnSaveDocument(lpszPathName);
	return TRUE;
}
