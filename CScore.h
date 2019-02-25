#pragma once


// CScore 对话框

class CScore : public CDialogEx
{
	DECLARE_DYNAMIC(CScore)

public:
	CScore(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScore();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnquit();
	CAdoDatabase m_db;
	afx_msg void OnBnClickedBtninsert();
	afx_msg void OnBnClickedBtnupdate();
	virtual BOOL OnInitDialog();
	CComboBox m_ComBoxStuNo;
	CStatic m_StaStuName;
	CComboBox m_ComBoxCourseNo;
	CStatic m_StaCourseName;
	CEdit m_EditScore;
	void GetTeNo(CString);
	CString m_TeaNo;
	void InitComBoxStuNo();
	afx_msg void OnCbnSelchangeCombocourseno();
	afx_msg void OnCbnSelchangeCombostuno();
	void InitStaticText();
	void InitScore(CString,CString);
	CString m_oldScore;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
