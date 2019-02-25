// CCPasswd.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CCPasswd.h"
#include "afxdialogex.h"


// CCPasswd 对话框

IMPLEMENT_DYNAMIC(CCPasswd, CDialogEx)



CCPasswd::CCPasswd(CString id, int UserType, CWnd * pParent)
	: CDialogEx(IDD_CCPASSWD, pParent), m_id(id)
	, m_EditOldPasswd(_T(""))
	, m_EditAgainPasswd(_T(""))
	, m_EditNewPasswd(_T(""))
{
	if (UserType == USERTYPE_STU) {
		m_UserType = "student";
	}
	else if(UserType == USERTYPE_TEA){
		m_UserType = "teacher";
	}
	else if (UserType == USERTYPE_ADM) {
		m_UserType = "admin";
	}
}

CCPasswd::~CCPasswd()
{
	m_db.Close();
}

void CCPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OLDPASSWD, m_EditOldPasswd);
	DDX_Text(pDX, IDC_AGAINPASSWD, m_EditAgainPasswd);
	DDX_Text(pDX, IDC_NEWPASSWD, m_EditNewPasswd);
}


BEGIN_MESSAGE_MAP(CCPasswd, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGE, &CCPasswd::OnBnClickedChange)
	ON_BN_CLICKED(IDC_QUIT, &CCPasswd::OnBnClickedQuit)
END_MESSAGE_MAP()


// CCPasswd 消息处理程序


void CCPasswd::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_EditNewPasswd != m_EditAgainPasswd) {
		AfxMessageBox(_T("两次新密码不一致"));
		return;
	}
	CAdoRecordset set;
	CString sql;
	sql.Format(_T("select %s_passwd from %s where %s_no=%s and %s_passwd=%s"), m_UserType, m_UserType, m_UserType, m_id,m_UserType, m_EditOldPasswd);
	set.OpenSql(sql, &m_db);
	if (set.IsNULL()) {
		AfxMessageBox(_T("原密码不正确！"));
		return;
	}
	sql.Format(_T("update %s set %s_passwd=%s where %s_no=%s"), m_UserType, m_UserType, m_EditNewPasswd, m_UserType, m_id);
	set.OpenSql(sql, &m_db);
	AfxMessageBox(_T("密码修改成功"));
	CDialog::OnCancel();
}

void CCPasswd::OnBnClickedQuit()
{
	CDialogEx::OnCancel();
}






BOOL CCPasswd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//连接数据库
	if (!m_db.Open()) {
		AfxMessageBox(_T("数据库连接失败"));
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CCPasswd::PreTranslateMessage(MSG* pMsg)
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
