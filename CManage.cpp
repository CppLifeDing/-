// CManage.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CManage.h"
#include "afxdialogex.h"


// CManage 对话框

IMPLEMENT_DYNAMIC(CManage, CDialogEx)

CManage::CManage(CWnd* pParent /*=nullptr*/, bool type /*=true*/)
	: CDialogEx(IDD_MANAGE, pParent)
{
	if (type) {
		m_tableName = "student";
	}
	else {
		m_tableName = "teacher";
	}
}

CManage::~CManage()
{
	m_db.Close();
}

void CManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	;
	DDX_Control(pDX, IDC_STUDELETE, m_BtnDel);
	DDX_Control(pDX, IDC_STDINSERT, m_BtnIns);
	DDX_Control(pDX, IDC_EDITANO, m_EditANo);
	DDX_Control(pDX, IDC_STAANAME, m_StaAName);
	DDX_Control(pDX, IDC_EDITANAME, m_EditAName);
	DDX_Control(pDX, IDC_STAAPASSWD, m_StaAPasswd);
	DDX_Control(pDX, IDC_EDITAPASSWD, m_EditAPasswd);
	DDX_Control(pDX, IDC_STAASTUCLASS, m_StaAStuClass);
	DDX_Control(pDX, IDC_EDITASTUCLASS, m_EditAStuClass);
	DDX_Control(pDX, IDC_CBASTUCLASS, m_CBAStuClass);
	DDX_Control(pDX, IDC_CBANO, m_CBANo);
	DDX_Control(pDX, IDC_STAANO, m_StaANo);
}


BEGIN_MESSAGE_MAP(CManage, CDialogEx)
	ON_BN_CLICKED(IDC_STUDELETE, &CManage::OnBnClickedStudelete)
	ON_BN_CLICKED(IDC_STDINSERT, &CManage::OnBnClickedStdinsert)
	ON_BN_CLICKED(IDC_CAN, &CManage::OnBnClickedCan)
	ON_CBN_SELCHANGE(IDC_CBANO, &CManage::OnCbnSelchangeCbano)
END_MESSAGE_MAP()


// CManage 消息处理程序


BOOL CManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	if (m_tableName == "student") {
		SetWindowText("学生管理");
		m_StaANo.SetWindowTextA("学生 I D:");
		m_StaAName.SetWindowTextA("学生姓名:");
		m_StaAPasswd.SetWindowTextA("学生密码:");
		m_StaAStuClass.ShowWindow(true);
	}
	else {
		SetWindowText("教师管理");
		m_StaANo.SetWindowTextA("教师 I D:");
		m_StaAName.SetWindowTextA("教师姓名:");
		m_StaAPasswd.SetWindowTextA("教师密码:");
	}
	InitComBox();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CManage::OnBnClickedStudelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	m_BtnDel.GetWindowTextA(text);
	if (text == "删除模式") {
		m_EditANo.ShowWindow(SW_HIDE);
		m_CBANo.ShowWindow(SW_SHOW);
		m_EditAName.SetReadOnly(true);
		m_EditAPasswd.SetReadOnly(true);
		InitComBox();
		m_BtnDel.SetWindowTextA("删除");
		m_BtnIns.EnableWindow(false);
	}
	else {
		del();
		InitComBox();
	}
}


void CManage::OnBnClickedStdinsert()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	m_BtnIns.GetWindowTextA(text);
	if(text == "添加模式"){
		m_EditANo.ShowWindow(SW_SHOW);
		m_CBANo.ShowWindow(SW_HIDE);
		m_EditAName.SetWindowTextA("");
		m_EditAPasswd.SetWindowTextA("");
		m_EditAName.SetReadOnly(false);
		m_EditAPasswd.SetReadOnly(false);
		m_BtnIns.SetWindowTextA("添加");
		m_BtnDel.EnableWindow(false);
		if (m_tableName == "student") {
			m_EditAStuClass.ShowWindow(false);
			m_CBAStuClass.ShowWindow(true);
		}
	}
	else {
		ins();
		InitComBox();
	}
}

void CManage::InitComBox()
{
	m_BtnDel.SetWindowTextA("删除模式");
	m_BtnIns.SetWindowTextA("添加模式");
	m_BtnDel.EnableWindow(true);
	m_BtnIns.EnableWindow(true);
	m_CBANo.ShowWindow(SW_SHOW);
	m_EditANo.ShowWindow(SW_HIDE);
	m_EditAName.SetReadOnly(true);
	m_EditAPasswd.SetReadOnly(true);
	CString sql;
	sql.Format("select %s_no from %s;", m_tableName, m_tableName);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	m_CBANo.ResetContent();
	set.MoveFirst();
	CString no;
	while(!set.IsEOF()) {
		set.GetFieldValue(0, no);
		m_CBANo.AddString(no);
		set.MoveNext();
	}
	m_CBANo.SetCurSel(0);
	if (m_tableName == "student") {
		m_EditAStuClass.ShowWindow(true);
		m_CBAStuClass.ShowWindow(false);
		sql.Format("select class_no from classes;");
		set.OpenSql(sql, &m_db);
		m_CBAStuClass.ResetContent();
		set.MoveFirst();
		CString no;
		while (!set.IsEOF()) {
			set.GetFieldValue(0, no);
			m_CBAStuClass.AddString(no);
			set.MoveNext();
		}
		m_CBAStuClass.SetCurSel(0);
	}
	ShowDate();
}

void CManage::OnCbnSelchangeCbano()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowDate();
}
	

void CManage::ShowDate() {
	CString no;
	m_CBANo.GetLBText(m_CBANo.GetCurSel(), no);
	CString sql;
	sql.Format("select %s_name,%s_passwd from %s where %s_no=%s;", m_tableName, m_tableName, m_tableName, m_tableName, no);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString name;
	set.GetFieldValue(0, name);
	m_EditAName.SetWindowTextA(name);
	CString passwd;
	set.GetFieldValue(1, passwd);
	m_EditAPasswd.SetWindowTextA(passwd);
	if (m_tableName == "student") {
		sql.Format("select class_no from student where student_no=%s;", no);
		set.OpenSql(sql, &m_db);
		CString stuClass;
		set.GetFieldValue(0, stuClass);
		m_EditAStuClass.SetWindowTextA(stuClass);
	}
}

void CManage::OnBnClickedCan()
{
	CString text1;
	m_BtnDel.GetWindowTextA(text1);
	CString text2;
	m_BtnIns.GetWindowTextA(text2);
	if (text1 == "删除模式"  && text2 == "添加模式") {
		CDialogEx::OnCancel();
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	InitComBox();

}

void CManage::del()
{
	//AfxMessageBox("删除");
	CString no;
	m_CBANo.GetLBText(m_CBANo.GetCurSel(), no);
	CString sql;
	if (m_tableName == "student") {
		sql.Format("delete from setcourse where student_no=%s", no);
	}
	else {
		sql.Format("delete from course where teacher_no=%s", no);
	}
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	sql.Format("delete from results where %s_no=%s", m_tableName, no);
	set.OpenSql(sql, &m_db);
	sql.Format("delete from %s where %s_no=%s", m_tableName, m_tableName, no);
	set.OpenSql(sql, &m_db);
	AfxMessageBox("删除成功");
}

void CManage::ins()
{
	CString no;
	m_EditANo.GetWindowTextA(no);
	CString name;
	m_EditAName.GetWindowTextA(name);
	CString passwd;
	m_EditAPasswd.GetWindowTextA(passwd);
	CString sql;
	if (m_tableName == "student") {
		CString classNo;
		m_CBAStuClass.GetLBText(m_CBAStuClass.GetCurSel(), classNo);
		sql.Format("insert into student values(%s,'%s',%s, %s);", no, name, passwd, classNo);
	}
	else {
		sql.Format("insert into teacher values(%s,'%s',%s);", no, name, passwd);
	}
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	AfxMessageBox("添加成功");
}



