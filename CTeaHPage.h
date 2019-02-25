#pragma once
#include "CScore.h"
class CTeaHPage : public CDialogEx
{
	DECLARE_DYNAMIC(CTeaHPage)

public:
	CTeaHPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeaHPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEAHPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_TeaNo;
	CAdoDatabase m_db;
	void GetTeaNo(CString);
	CStatic m_No;
	CStatic m_Name;
	CButton m_BtnAll;
	CButton m_BtnStuName;
	CButton m_BtnCourseName;
	afx_msg void OnBnClickedChangepasswd();
	afx_msg void OnBnClickedTrylogin2();
	CComboBox m_ComBox;
	afx_msg void OnBnClickedAll();
	int m_findType;
	afx_msg void OnBnClickedStuname();
	afx_msg void OnBnClickedCoursename();
	afx_msg void OnCbnSelchangeFind();
	void ShowDate(int);
	void InitComBox();
	CListCtrl m_TeaList;
	afx_msg void OnBnClickedIuscore();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
