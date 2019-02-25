// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_passwd(_T(""))
	, m_name(_T(""))
{
}

CLoginDlg::~CLoginDlg()
{
	m_db.Close();
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSWD, m_passwd);
	DDV_MaxChars(pDX, m_passwd, 32);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Control(pDX, IDC_LOGIN, m_BLogin);
	DDX_Control(pDX, IDC_STUDENT, m_BStu);
	DDX_Control(pDX, IDC_TEACHER, m_BTea);
	DDX_Control(pDX, IDC_ADMIN, m_BAdmin);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_EN_CHANGE(IDC_NAME, &CLoginDlg::OnEnChangeName)
	ON_BN_CLICKED(IDC_CANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_PASSWD, &CLoginDlg::OnEnChangePasswd)
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

void CLoginDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CLoginDlg::OnEnChangePasswd()
{
	UpdateData(true);
	if (m_name != "" && m_passwd != "") {
		m_BLogin.EnableWindow(1);
	}

}

void CLoginDlg::OnEnChangeName()
{
	UpdateData(true);
	if (m_name != "" && m_passwd != "") {
		m_BLogin.EnableWindow(1);
	}

}

void CLoginDlg::OnBnClickedLogin()
{
	CString tableName = "";
	CString hint = "";
	if (m_BStu.GetCheck()) {
		account_type = USERTYPE_STU;
		tableName = "student";
		hint = "同学";
	}
	else if (m_BTea.GetCheck()) {
		account_type = USERTYPE_TEA;
		tableName = "teacher";
		hint = "老师";
	}
	else if (m_BAdmin.GetCheck()) {
		account_type = USERTYPE_ADM;
		tableName = "admin";
		hint = "管理员";
	}
	else {
		AfxMessageBox("账号类型出错！");
	}
	//AfxMessageBox(tableName);
	//打开记录及获取数据，将用户名和密码传输给服务器进行确认
	//以下为简化版本
	UpdateData(true);
	CString sql;
	sql.Format("select * from %s where %s_no=%s and %s_passwd=%s;",
		tableName, tableName, m_name, tableName, m_passwd);
	CAdoRecordset set;
	//执行sql语句
	set.OpenSql(sql, &m_db);
	//获取记录集是否为空
	if(set.IsNULL()){
		AfxMessageBox("用户名或密码出错！");
	}
	else {
		if (account_type == USERTYPE_ADM) {
			CDialogEx::OnOK();
			AfxMessageBox("欢迎管理员上线");
			return;
		}
		CString welcome;
		UpdateData(true);
		sql.Format("select %s_name from %s where %s_no=%s;", tableName, tableName, tableName, m_name);
		set.OpenSql(sql, &m_db);
		CString name;
		set.GetFieldValue(0, name);
		welcome.Format("欢迎%s%s!", name, hint);
		AfxMessageBox(welcome);
		CDialogEx::OnOK();
		return;
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_BStu.SetCheck(TRUE);
	// TODO:  在此添加额外的初始化
	//连接数据库
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		CDialogEx::OnCancel();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		UpdateData(true);
		if (m_name != "" && m_passwd != "") {
			OnBnClickedLogin();
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
