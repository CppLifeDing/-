// CCouAdmin.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CCouAdmin.h"
#include "afxdialogex.h"

// CCouAdmin 对话框

IMPLEMENT_DYNAMIC(CCouAdmin, CDialogEx)

CCouAdmin::CCouAdmin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUADMIN, pParent)
{

}

CCouAdmin::~CCouAdmin()
{
	m_db.Close();
}

void CCouAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITCOUNO, m_EditCouNo);
	DDX_Control(pDX, IDC_CBCOUNO, m_CBCouNo);
	DDX_Control(pDX, IDC_STACOUTEA, m_StaCouTea);
	DDX_Control(pDX, IDC_CBCOUTEA, m_CBCouTea);
	//  DDX_Control(pDX, IDC_CBCLASS, m_CBClass);
	DDX_Control(pDX, IDC_BTNCOUDEL, m_BtnCouDel);
	DDX_Control(pDX, IDC_BTNCOUINS, m_BtnCouIns);
	DDX_Control(pDX, IDC_EDITCOUNAME, m_EditCouName);
}


BEGIN_MESSAGE_MAP(CCouAdmin, CDialogEx)
	ON_BN_CLICKED(IDC_BTNQUIT, &CCouAdmin::OnBnClickedBtnquit)
	ON_BN_CLICKED(IDC_BTNCOUDEL, &CCouAdmin::OnBnClickedBtncoudel)
	ON_BN_CLICKED(IDC_BTNCOUINS, &CCouAdmin::OnBnClickedBtncouins)
	ON_CBN_SELCHANGE(IDC_CBCOUNO, &CCouAdmin::OnCbnSelchangeCbcouno)
END_MESSAGE_MAP()

BOOL CCouAdmin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	InitShow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CCouAdmin::InitShow()
{
	// TODO: 在此处添加实现代码.
	m_CBCouNo.ShowWindow(SW_SHOW);
	m_EditCouNo.ShowWindow(SW_HIDE);
	m_EditCouName.SetReadOnly(true);
	m_EditCouName.ShowWindow(SW_SHOW);
	m_StaCouTea.ShowWindow(SW_SHOW);
	m_CBCouTea.ShowWindow(SW_HIDE);
	m_BtnCouDel.SetWindowTextA("删除模式");
	m_BtnCouIns.SetWindowTextA("添加模式");
	m_BtnCouDel.EnableWindow(TRUE);
	m_BtnCouIns.EnableWindow(TRUE);
	InitComBox(m_CBCouNo, "course");
	InitComBox(m_CBCouTea, "teacher");
	ShowDate();
}

void CCouAdmin::InitComBox(CComboBox& cb, const CString tableName)
{
	//AfxMessageBox(tableName);
	CString sql;
	sql.Format("select %s_no from %s;" , tableName, tableName);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	cb.ResetContent();
	set.MoveFirst();
	CString no;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, no);
		cb.AddString(no);
		set.MoveNext();
	}
	cb.SetCurSel(0);
}

void CCouAdmin::ShowDate()
{
	// TODO: 在此处添加实现代码.
	CString couNo;
	m_CBCouNo.GetLBText(m_CBCouNo.GetCurSel(), couNo);
	CString sql;
	sql.Format("select course_name,teacher_name from course c join teacher t on c.teacher_no=t.teacher_no where c.course_no=%s;", couNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString name;
	set.GetFieldValue(0, name);
	m_EditCouName.SetWindowTextA(name);
	set.GetFieldValue(1, name);
	m_StaCouTea.SetWindowTextA(name);
}


void CCouAdmin::OnCbnSelchangeCbcouno()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowDate();
}

void CCouAdmin::OnBnClickedBtnquit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text1;
	m_BtnCouDel.GetWindowTextA(text1);
	CString text2;
	m_BtnCouIns.GetWindowTextA(text2);
	if (text1 == "删除模式"  && text2 == "添加模式") {
		CDialogEx::OnCancel();
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	InitShow();
}


void CCouAdmin::OnBnClickedBtncoudel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	m_BtnCouDel.GetWindowTextA(text);
	if (text == "删除模式") {
		m_BtnCouDel.SetWindowTextA("删除");
		m_BtnCouIns.EnableWindow(FALSE);
	}
	else {
		del();
		InitShow();
	}
}


void CCouAdmin::OnBnClickedBtncouins()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	m_BtnCouIns.GetWindowTextA(text);
	if (text == "添加模式") {
		m_EditCouNo.ShowWindow(SW_SHOW);
		m_CBCouNo.ShowWindow(SW_HIDE);
		m_StaCouTea.ShowWindow(SW_HIDE);
		m_CBCouTea.ShowWindow(SW_SHOW);
		m_BtnCouIns.SetWindowTextA("添加");
		m_BtnCouDel.EnableWindow(FALSE);
		m_EditCouName.SetReadOnly(FALSE);
		m_EditCouName.SetWindowTextA("");
	}
	else {
		ins();
		InitShow();
	}
}




void CCouAdmin::del()
{
	// TODO: 在此处添加实现代码.
	CString no;
	m_CBCouNo.GetLBText(m_CBCouNo.GetCurSel(), no);
	CString sql;
	sql.Format("delete from results where course_no = %s", no);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	sql.Format("delete from setcourse where course_no = %s", no);
	set.OpenSql(sql, &m_db);
	sql.Format("delete from course where course_no = %s", no);
	set.OpenSql(sql, &m_db);
	AfxMessageBox("删除成功");
}


void CCouAdmin::ins()
{
	// TODO: 在此处添加实现代码.
	CString no;
	m_EditCouNo.GetWindowTextA(no);
	CString name;
	m_EditCouName.GetWindowTextA(name);
	CString teaNo;
	m_CBCouTea.GetLBText(m_CBCouTea.GetCurSel(), teaNo);
	CAdoRecordset set;
	CString sql;
	sql.Format("insert into course values(%s,'%s',%s);", no, name, teaNo);
	set.OpenSql(sql, &m_db);
	AfxMessageBox("添加成功");
}
