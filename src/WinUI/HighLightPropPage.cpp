// HighLightPropPage.cpp : 实现文件
//

#include "stdafx.h"
#include "HighLightPropPage.h"
#include "afxdialogex.h"


// HighLightPropPage 对话框

IMPLEMENT_DYNAMIC(HighLightPropPage, CPropertyPage)

HighLightPropPage::HighLightPropPage()
	: CPropertyPage(HighLightPropPage::IDD) {

}

HighLightPropPage::~HighLightPropPage() {
}

void HighLightPropPage::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HighLightPropPage, CPropertyPage)
END_MESSAGE_MAP()


// HighLightPropPage 消息处理程序
