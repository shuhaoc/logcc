#pragma once

#include "resource.h"
#include "HighLightPropPage.h"

// ConfigDlg 对话框

class ConfigDlg : public CDialogEx {
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ConfigDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG };

private:
	CPropertySheetEx propSheet;
	HighLightPropPage highLightPage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
