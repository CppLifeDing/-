#pragma once
#include "CManage.h"
#include "CCouAdmin.h"
#include "CSetCourse.h"

// CAdminHPage 对话框

class CAdminHPage : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminHPage)

public:
	CAdminHPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminHPage();
	void GetAdminNo(CString);
	CString m_no;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINHPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedStuadmin();
	afx_msg void OnBnClickedSteadmin();
	afx_msg void OnBnClickedCouadmin();
	afx_msg void OnBnClickedArelogin();
	afx_msg void OnBnClickedBtnsetcou();
};
