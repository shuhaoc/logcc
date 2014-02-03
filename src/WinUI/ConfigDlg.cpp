// ConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// ConfigDlg 对话框

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfigDlg::IDD, pParent) {

}

ConfigDlg::~ConfigDlg() {
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfigDlg 消息处理程序


BOOL ConfigDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	propSheet.AddPage(&highLightPage);
	propSheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	CRect rc;
	GetClientRect(rc);
	rc.bottom -= 40;
	propSheet.MoveWindow(rc);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
