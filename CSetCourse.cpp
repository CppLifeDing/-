// CSetCourse.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CSetCourse.h"
#include "afxdialogex.h"


// CSetCourse 对话框

IMPLEMENT_DYNAMIC(CSetCourse, CDialogEx)

CSetCourse::CSetCourse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETCOU, pParent)
{

}

CSetCourse::~CSetCourse()
{
	m_db.Close();
}

void CSetCourse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBCLASSNO, m_CBClassNo);
	//  DDX_Control(pDX, IDC_CBCOUID, m_CBCouId);
	DDX_Control(pDX, IDC_STACOUNAME, m_StaCouName);
	DDX_Control(pDX, IDC_BTNSETDEL, m_BtnSetDel);
	DDX_Control(pDX, IDC_BTNSETINS, m_BtnSetIns);
	DDX_Control(pDX, IDC_CBCOUNO, m_CBCouNo);
}


BEGIN_MESSAGE_MAP(CSetCourse, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CBCLASSNO, &CSetCourse::OnCbnSelchangeCbclassno)
	ON_BN_CLICKED(IDC_BTNSETDEL, &CSetCourse::OnBnClickedBtnsetdel)
	ON_BN_CLICKED(IDC_BTNSETINS, &CSetCourse::OnBnClickedBtnsetins)
	ON_BN_CLICKED(IDC_BTNQUIT, &CSetCourse::OnBnClickedBtnquit)
	ON_CBN_SELCHANGE(IDC_CBCOUNO, &CSetCourse::OnCbnSelchangeCbcouno)
END_MESSAGE_MAP()


// CSetCourse 消息处理程序


void CSetCourse::OnCbnSelchangeCbclassno()
{
	ShowDate();
}


BOOL CSetCourse::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	InitComBox();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSetCourse::InitComBox()
{
	// TODO: 在此处添加实现代码.
	m_BtnSetDel.EnableWindow(TRUE);
	m_BtnSetIns.EnableWindow(TRUE);
	m_BtnSetDel.SetWindowTextA("删除模式");
	m_BtnSetIns.SetWindowTextA("添加模式");
	CString sql;
	sql.Format("select class_no from classes;");
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	m_CBClassNo.ResetContent();
	set.MoveFirst();
	CString no;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, no);
		m_CBClassNo.AddString(no);
		set.MoveNext();
	}
	m_CBClassNo.SetCurSel(0);
	ShowDate();
	
}


void CSetCourse::ShowDate()
{
	CString sql;
	m_CBClassNo.GetLBText(m_CBClassNo.GetCurSel(), sql);
	sql.Format("select course_no from setcourse se join student s on se.student_no=s.student_no where class_no=%s group by course_no;", sql);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	if (set.IsNULL()) {
		OnBnClickedBtnsetins();
		return;
	}
	m_CBCouNo.ResetContent();
	set.MoveFirst();
	CString couNo;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, couNo);
		m_CBCouNo.AddString(couNo);
		set.MoveNext();
	}
	m_CBCouNo.SetCurSel(0);
	setStaValue();
}


void CSetCourse::OnBnClickedBtnquit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text1;
	m_BtnSetDel.GetWindowTextA(text1);
	CString text2;
	m_BtnSetIns.GetWindowTextA(text2);
	if (text1 == "删除模式"  && text2 == "添加模式") {
		CDialogEx::OnCancel();
		return;
	}
	InitComBox();
}


void CSetCourse::OnCbnSelchangeCbcouno()
{
	setStaValue();
}


void CSetCourse::setStaValue()
{
	CString sql;
	m_CBCouNo.GetLBText(m_CBCouNo.GetCurSel(), sql);
	CAdoRecordset set;
	sql.Format("select course_name from course where course_no=%s;", sql);
	set.OpenSql(sql, &m_db);
	CString couName;
	set.GetFieldValue(0, couName);
	m_StaCouName.SetWindowTextA(couName);
}


void CSetCourse::OnBnClickedBtnsetdel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	m_BtnSetDel.GetWindowTextA(text);
	if (text == "删除模式") {
		m_BtnSetDel.SetWindowTextA("删除");
		m_BtnSetIns.EnableWindow(FALSE);
	}
	else {
		setCou(false);
		InitComBox();
	}
}


void CSetCourse::OnBnClickedBtnsetins()
{
	CString text;
	m_BtnSetIns.GetWindowTextA(text);
	if (text == "添加模式") {
		m_BtnSetIns.SetWindowTextA("添加");
		m_BtnSetDel.EnableWindow(FALSE);
		CString sql;
		sql.Format("select course_no from course;");
		CAdoRecordset set;
		set.OpenSql(sql, &m_db);
		m_CBCouNo.ResetContent();
		set.MoveFirst();
		CString couNo;
		while (!set.IsEOF()) {
			set.GetFieldValue(0, couNo);
			m_CBCouNo.AddString(couNo);
			set.MoveNext();
		}
		m_CBCouNo.SetCurSel(0);
	}
	else {
		setCou(true);
		InitComBox();
	}
}

void CSetCourse::setCou(bool type) {
	CString classNo;
	m_CBClassNo.GetLBText(m_CBClassNo.GetCurSel(), classNo);
	CString couNo;
	m_CBCouNo.GetLBText(m_CBCouNo.GetCurSel(), couNo);
	CString sql;
	sql.Format("select student_no from student where class_no=%s", classNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString stuNo;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, stuNo);
		CAdoRecordset setCou;
		if (type) {
			sql.Format("select * from setcourse where student_no=%s and course_no=%s;", stuNo, couNo);
			setCou.OpenSql(sql, &m_db);
			if (!setCou.IsNULL()) {
				AfxMessageBox("此课程以被添加到该班级，请重新选择！");
				return;
			}
			sql.Format("insert into setcourse values(%s,%s);", stuNo, couNo);
		}
		else {
			sql.Format("delete from setcourse where student_no=%s and course_no=%s;", stuNo, couNo);
		}
		setCou.OpenSql(sql, &m_db);
		set.MoveNext();
	}
	if (type) {
		AfxMessageBox("添加成功");
	}
	else {
		AfxMessageBox("删除成功");
	}
}
