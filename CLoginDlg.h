#pragma once
#include "stdafx.h"

#include "CAdoDatabase.h"
#include "CAdoRecordset.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();
	CAdoDatabase m_db;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int account_type;
	afx_msg void OnEnChangeName();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangePasswd();
	CString m_passwd;
	CString m_name;
	CButton m_BLogin;
	afx_msg void OnBnClickedLogin();
	
	CButton m_BStu;
	CButton m_BTea;
	CButton m_BAdmin;
	virtual BOOL OnInitDialog();
//	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual void OnCancel();
//	afx_msg void OnClose();
};
