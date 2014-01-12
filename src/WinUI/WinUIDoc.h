
// WinUIDoc.h : CWinUIDoc ��Ľӿ�
//


#pragma once

class ILogQuery;

class CWinUIDoc : public CDocument
{
protected: // �������л�����
	CWinUIDoc();
	DECLARE_DYNCREATE(CWinUIDoc)

// ����
public:
	ILogQuery* logQuery;
	//vector<string> m_vecLines;

	//enum {
	//	UpdateView_FileOPen = 1			// ���ܴ�0��ʼ����ΪOnInitialUpdate�����OnUpdate
	//};

// ����
public:

// ��д
public:
	//virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CWinUIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
