#pragma once


// CManage 对话框

class CManage : public CDialogEx
{
	DECLARE_DYNAMIC(CManage)

public:
	CManage(CWnd* pParent = nullptr, bool type = true);   // 标准构造函数
	virtual ~CManage();
	//bool m_type;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_tableName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStudelete();
	afx_msg void OnBnClickedStdinsert();
	void InitComBox();
	CAdoDatabase m_db;
	void ShowDate();
	CButton m_BtnDel;
	CButton m_BtnIns;
	void del();
	void ins();
	afx_msg void OnBnClickedCan();
	CEdit m_EditANo;
	CStatic m_StaAName;
	CEdit m_EditAName;
	CStatic m_StaAPasswd;
	CEdit m_EditAPasswd;
	CStatic m_StaAStuClass;
	CEdit m_EditAStuClass;
	CComboBox m_CBAStuClass;
	afx_msg void OnCbnSelchangeCbano();
	CComboBox m_CBANo;
	CStatic m_StaANo;
};
