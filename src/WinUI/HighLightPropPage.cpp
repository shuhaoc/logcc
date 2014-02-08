// HighLightPropPage.cpp : 实现文件
//

#include "stdafx.h"
#include "HighLightPropPage.h"
#include "afxdialogex.h"
#include "ModelFactory.h"
#include "IPatternService.h"

// HighLightPropPage 对话框

IMPLEMENT_DYNAMIC(HighLightPropPage, CPropertyPage)

HighLightPropPage::HighLightPropPage()
	: CPropertyPage(HighLightPropPage::IDD) {

}

HighLightPropPage::~HighLightPropPage() {
}

void HighLightPropPage::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_COLOR, textColorBtn);
	DDX_Control(pDX, IDC_BACK_COLOR, backColorBtn);
}


BEGIN_MESSAGE_MAP(HighLightPropPage, CPropertyPage)
END_MESSAGE_MAP()


// HighLightPropPage 消息处理程序


BOOL HighLightPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	ModelFactory::GetInstance()->CreatePatternService()->all();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
