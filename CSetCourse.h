#pragma once


// CSetCourse 对话框

class CSetCourse : public CDialogEx
{
	DECLARE_DYNAMIC(CSetCourse)

public:
	CSetCourse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetCourse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETCOU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CAdoDatabase m_db;
	CComboBox m_CBClassNo;
//	CComboBox m_CBCouId;
	CStatic m_StaCouName;
	afx_msg void OnCbnSelchangeCbclassno();
	afx_msg void OnBnClickedBtnsetdel();
	afx_msg void OnBnClickedBtnsetins();
	CButton m_BtnSetDel;
	CButton m_BtnSetIns;
	virtual BOOL OnInitDialog();
	void InitComBox();
	CComboBox m_CBCouNo;
	void ShowDate();
	afx_msg void OnBnClickedBtnquit();
	afx_msg void OnCbnSelchangeCbcouno();
	void setStaValue();
	void setCou(bool);
};
