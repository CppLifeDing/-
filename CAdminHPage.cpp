// CAdminHPage.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CAdminHPage.h"
#include "afxdialogex.h"


// CAdminHPage 对话框

IMPLEMENT_DYNAMIC(CAdminHPage, CDialogEx)

CAdminHPage::CAdminHPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINHPAGE, pParent)
{

}

CAdminHPage::~CAdminHPage()
{
}

void CAdminHPage::GetAdminNo(CString AdminNo)
{
	m_no = AdminNo;
}

void CAdminHPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminHPage, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_STUADMIN, &CAdminHPage::OnBnClickedStuadmin)
	ON_BN_CLICKED(IDC_STEADMIN, &CAdminHPage::OnBnClickedSteadmin)
	ON_BN_CLICKED(IDC_COUADMIN, &CAdminHPage::OnBnClickedCouadmin)
	ON_BN_CLICKED(IDC_ARELOGIN, &CAdminHPage::OnBnClickedArelogin)
	ON_BN_CLICKED(IDC_BTNSETCOU, &CAdminHPage::OnBnClickedBtnsetcou)
END_MESSAGE_MAP()


// CAdminHPage 消息处理程序






BOOL CAdminHPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CAdminHPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		CDialogEx::OnCancel();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CAdminHPage::OnBnClickedStuadmin()
{
	// TODO: 在此添加控件通知处理程序代码
	CManage stuAdmin(this,true);
	stuAdmin.DoModal();
}


void CAdminHPage::OnBnClickedSteadmin()
{
	// TODO: 在此添加控件通知处理程序代码
	CManage teaAdmin(this, false);
	teaAdmin.DoModal();
}


void CAdminHPage::OnBnClickedCouadmin()
{
	// TODO: 在此添加控件通知处理程序代码
	CCouAdmin couAdmin(this);
	couAdmin.DoModal();
}


void CAdminHPage::OnBnClickedArelogin()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(RELOGIN);
}


void CAdminHPage::OnBnClickedBtnsetcou()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetCourse setCou(this);
	setCou.DoModal();
}
