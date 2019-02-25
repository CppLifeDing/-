#pragma once


// CCPasswd 对话框

class CCPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(CCPasswd)

public:
	CCPasswd(CString, int UserType = USERTYPE_STU, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCPasswd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCPASSWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedQuit();
	CAdoDatabase m_db;
	virtual BOOL OnInitDialog();
//	afx_msg void OnClose();
	CString m_id;
	CString m_UserType;
	CString m_EditOldPasswd;
	CString m_EditAgainPasswd;
	CString m_EditNewPasswd;
//	virtual void OnCancel();
//	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
