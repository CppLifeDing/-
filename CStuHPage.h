#pragma once
#include "stdafx.h"
#include "CCPasswd.h"
// CStuHPage 对话框

class CStuHPage : public CDialogEx
{
	DECLARE_DYNAMIC(CStuHPage)

public:
	CStuHPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStuHPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUHPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChangepasswd();
	afx_msg void OnBnClickedListscore();
	virtual BOOL OnInitDialog();
	void GetStuNo(CString);
public:
	int m_UserType;
	CString m_no;
	CAdoDatabase m_db;
	CListCtrl m_List;
	CStatic m_ClassName;
	CStatic m_StuName;
	CStatic m_StuNo;
	afx_msg void OnBnClickedSrelogin();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
