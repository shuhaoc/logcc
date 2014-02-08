#pragma once

#include "resource.h"
#include "afxwin.h"
#include "ColorSelect.h"

// HighLightPropPage 对话框

class HighLightPropPage : public CPropertyPage {
	DECLARE_DYNAMIC(HighLightPropPage)

public:
	HighLightPropPage();
	virtual ~HighLightPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_HIGHLIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CColorSelect textColorBtn;
	CColorSelect backColorBtn;
};
