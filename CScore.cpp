// CScore.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CScore.h"
#include "afxdialogex.h"


// CScore 对话框

IMPLEMENT_DYNAMIC(CScore, CDialogEx)

CScore::CScore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCORE, pParent)
{
	m_oldScore = "";
}

CScore::~CScore()
{
}

void CScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOSTUNO, m_ComBoxStuNo);
	DDX_Control(pDX, IDC_STATICSTUNAME, m_StaStuName);
	DDX_Control(pDX, IDC_COMBOCOURSENO, m_ComBoxCourseNo);
	DDX_Control(pDX, IDC_STATICCOURSENAME, m_StaCourseName);
	DDX_Control(pDX, IDC_EDITSCORE, m_EditScore);
}


BEGIN_MESSAGE_MAP(CScore, CDialogEx)
	ON_BN_CLICKED(IDC_BTNQUIT, &CScore::OnBnClickedBtnquit)
	ON_BN_CLICKED(IDC_BTNINSERT, &CScore::OnBnClickedBtninsert)
	ON_BN_CLICKED(IDC_BTNUPDATE, &CScore::OnBnClickedBtnupdate)
	ON_CBN_SELCHANGE(IDC_COMBOCOURSENO, &CScore::OnCbnSelchangeCombocourseno)
	ON_CBN_SELCHANGE(IDC_COMBOSTUNO, &CScore::OnCbnSelchangeCombostuno)
END_MESSAGE_MAP()


// CScore 消息处理程序

void CScore::OnBnClickedBtnquit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

BOOL CScore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_db.Open()) {
		AfxMessageBox(_T("数据库连接失败"));
		return FALSE;
	}
	CString sql;
	sql.Format("select course_no from course c join teacher t on c.teacher_no=t.teacher_no "
					"where t.teacher_no=%s;", m_TeaNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	if (!set.IsBOF()) {
		set.MoveFirst();
	}
	CString strValue;
	int nItem = 0;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, strValue);
		m_ComBoxCourseNo.AddString(strValue);
		set.MoveNext();
	}
	m_ComBoxCourseNo.SetCurSel(0);
	InitComBoxStuNo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CScore::GetTeNo(CString TeaNo)
{
	m_TeaNo = TeaNo;
}

void CScore::InitComBoxStuNo()
{
	m_ComBoxStuNo.ResetContent();
	CString cur;
	m_ComBoxCourseNo.GetLBText(m_ComBoxCourseNo.GetCurSel(), cur);
	cur.Format("select student_no from setcourse where course_no=%s;", cur);
	CAdoRecordset set;
	set.OpenSql(cur, &m_db);
	if (!set.IsBOF()) {
		set.MoveFirst();
	}
	CString strValue;
	int nItem = 0;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, strValue);
		m_ComBoxStuNo.AddString(strValue);
		set.MoveNext();
	}
	m_ComBoxStuNo.SetCurSel(0);
	InitStaticText();
}


void CScore::OnCbnSelchangeCombocourseno()
{
	// TODO: 在此添加控件通知处理程序代码
	InitComBoxStuNo();
	
}


void CScore::OnCbnSelchangeCombostuno()
{
	// TODO: 在此添加控件通知处理程序代码
	InitStaticText();
}

void CScore::InitStaticText()
{
	CString CourseNo;
	m_ComBoxCourseNo.GetLBText(m_ComBoxCourseNo.GetCurSel(), CourseNo);
	CString StuNo;
	m_ComBoxStuNo.GetLBText(m_ComBoxStuNo.GetCurSel(), StuNo);
	CString sql;
	//AfxMessageBox(CourseNo);
	//AfxMessageBox(StuNo);
	sql.Format("select course_name from course where course_no=%s;", CourseNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString Name;
	set.GetFieldValue(0, Name);
	m_StaCourseName.SetWindowTextA(Name);
	sql.Format("select student_name from student where student_no=%s;", StuNo);
	set.OpenSql(sql, &m_db);
	set.GetFieldValue(0, Name);
	m_StaStuName.SetWindowTextA(Name);
	InitScore(CourseNo, StuNo);
}

void CScore::InitScore(CString CourseNo, CString StuNo)
{
	m_EditScore.SetWindowTextA("");
	CString sql;
	sql.Format("select score from results where student_no=%s and course_no=%s;", StuNo, CourseNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	if (!set.IsNULL()) {
		//AfxMessageBox("text");
		CString score;
		set.GetFieldValue(0, score);
		m_EditScore.SetWindowTextA(score);
		m_oldScore = score;
	}
	else {
		m_oldScore = "";
	}
}

void CScore::OnBnClickedBtninsert()
{
	// TODO: 在此添加控件通知处理程序代码
	CString curScore;
	m_EditScore.GetWindowTextA(curScore);
	//AfxMessageBox(text);
	if (m_oldScore != "") {
		AfxMessageBox("当前已有成绩，请点击修改成绩");
		return;
	}
	CString StuNo;
	m_ComBoxStuNo.GetLBText(m_ComBoxStuNo.GetCurSel(), StuNo);
	//AfxMessageBox(StuNo);
	CString CourseNo;
	m_ComBoxCourseNo.GetLBText(m_ComBoxCourseNo.GetCurSel(), CourseNo);
	CString sql;
	sql.Format("select class_no from student where student_no=%s;", StuNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString ClassNo;
	set.GetFieldValue(0, ClassNo);
	sql.Format("insert into results values(%s,%s,%s,%s,%s)", ClassNo, StuNo, CourseNo, m_TeaNo, curScore);
	set.OpenSql(sql, &m_db);
	AfxMessageBox("添加成绩成功！");
	CDialogEx::OnOK();
}


void CScore::OnBnClickedBtnupdate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString curScore;
	m_EditScore.GetWindowTextA(curScore);
	if (m_oldScore == "") {
		AfxMessageBox("当前无成绩，请点击添加成绩");
		return;
	}
	CString StuNo;
	m_ComBoxStuNo.GetLBText(m_ComBoxStuNo.GetCurSel(), StuNo);
	CString CourseNo;
	m_ComBoxCourseNo.GetLBText(m_ComBoxCourseNo.GetCurSel(), CourseNo);
	CString sql;
	sql.Format("select class_no from student where student_no=%s;", StuNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	sql.Format("update results set score=%s where student_no=%s and course_no=%s;", curScore, StuNo, CourseNo);
	set.OpenSql(sql, &m_db);
	AfxMessageBox("修改成绩成功！");
	CDialogEx::OnOK();
}


BOOL CScore::PreTranslateMessage(MSG* pMsg)
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
