#pragma once

class CWinUIDoc;

// CLogCtrlView 窗体视图

class CLogCtrlView : public CFormView
{
	DECLARE_DYNCREATE(CLogCtrlView)

protected:
	CLogCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogCtrlView();
	CWinUIDoc* GetDocument() const;

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
};


#ifndef _DEBUG  // WinUIView.cpp 中的调试版本
inline CWinUIDoc* CLogCtrlView::GetDocument() const
   { return reinterpret_cast<CWinUIDoc*>(m_pDocument); }
#endif
