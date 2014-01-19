#pragma once

class CLogCCDoc;

// CLogCtrlView 窗体视图

class CLogCtrlView : public CFormView
{
	DECLARE_DYNCREATE(CLogCtrlView)

protected:
	CLogCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogCtrlView();
	CLogCCDoc* GetDocument() const;

public:
	enum { IDD = IDD_LOGCTRLVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	// 搜索条件
	CString criteria;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeCriteria();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


#ifndef _DEBUG  // LogMainView.cpp 中的调试版本
inline CLogCCDoc* CLogCtrlView::GetDocument() const
   { return reinterpret_cast<CLogCCDoc*>(m_pDocument); }
#endif
