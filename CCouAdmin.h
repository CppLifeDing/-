#pragma once


// CCouAdmin 对话框

class CCouAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CCouAdmin)

public:
	CCouAdmin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCouAdmin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CAdoDatabase m_db;
	afx_msg void OnBnClickedBtnquit();
	CEdit m_EditCouNo;
	CComboBox m_CBCouNo;
	CStatic m_StaCouTea;
	CComboBox m_CBCouTea;
//	CComboBox m_CBClass;
	afx_msg void OnBnClickedBtncoudel();
	afx_msg void OnBnClickedBtncouins();
//	afx_msg void OnBnClickedBtnsetcourse();
	virtual BOOL OnInitDialog();
	void InitComBox(CComboBox&, CString);
	CButton m_BtnCouDel;
	CButton m_BtnCouIns;
	CEdit m_EditCouName;
	void InitShow();
	void ShowDate();
	afx_msg void OnCbnSelchangeCbcouno();
	CButton m_BtnSetCourse;
	void ins();
	void del();
};
