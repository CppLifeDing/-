// CTeaHPage.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CTeaHPage.h"
#include "afxdialogex.h"


// CTeaHPage 对话框

IMPLEMENT_DYNAMIC(CTeaHPage, CDialogEx)

CTeaHPage::CTeaHPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEAHPAGE, pParent)
{

}

CTeaHPage::~CTeaHPage()
{
	m_db.Close();
}

void CTeaHPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_TEANO, m_No);
	DDX_Control(pDX, IDC_ALL, m_BtnAll);
	DDX_Control(pDX, IDC_STUNAME, m_BtnStuName);
	DDX_Control(pDX, IDC_COURSENAME, m_BtnCourseName);
	DDX_Control(pDX, IDC_FIND, m_ComBox);
	DDX_Control(pDX, IDC_TEALIST, m_TeaList);
}


BEGIN_MESSAGE_MAP(CTeaHPage, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGEPASSWD, &CTeaHPage::OnBnClickedChangepasswd)
	ON_BN_CLICKED(IDC_TRELOGIN2, &CTeaHPage::OnBnClickedTrylogin2)
	ON_BN_CLICKED(IDC_ALL, &CTeaHPage::OnBnClickedAll)
	ON_BN_CLICKED(IDC_STUNAME, &CTeaHPage::OnBnClickedStuname)
	ON_BN_CLICKED(IDC_COURSENAME, &CTeaHPage::OnBnClickedCoursename)
	ON_CBN_SELCHANGE(IDC_FIND, &CTeaHPage::OnCbnSelchangeFind)
	ON_BN_CLICKED(IDC_IUSCORE, &CTeaHPage::OnBnClickedIuscore)
END_MESSAGE_MAP()


// CTeaHPage 消息处理程序


BOOL CTeaHPage::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	m_BtnAll.SetCheck(TRUE);
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	CString sql;
	sql.Format("select teacher_name from teacher where teacher_no=%s",
		m_TeaNo);
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	CString TeaName;
	set.GetFieldValue(0, TeaName);
	m_No.SetWindowTextA(m_TeaNo);
	m_Name.SetWindowTextA(TeaName);
	//显示所有成绩
	OnBnClickedAll();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTeaHPage::GetTeaNo(CString TeaNo)
{
	m_TeaNo = TeaNo;
}

void CTeaHPage::OnBnClickedChangepasswd()
{
	// TODO: 在此添加控件通知处理程序代码
	CCPasswd CPasswd(m_TeaNo, USERTYPE_TEA, this);
	CPasswd.DoModal();
}


void CTeaHPage::OnBnClickedTrylogin2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(RELOGIN);
}



void CTeaHPage::OnBnClickedAll()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_findType) return;
	//显示成绩表所有的信息
	m_findType = 0;
	m_ComBox.ResetContent();
	m_ComBox.EnableWindow(FALSE);
	//m_ComBox.enable
	ShowDate(m_findType);
}




void CTeaHPage::OnBnClickedStuname()
{
	// TODO: 在此添加控件通知处理程序代码
	if (1 == m_findType) return;
	//显示此学生姓名的所有成绩
	m_findType = 1;
	m_ComBox.EnableWindow(TRUE);
	InitComBox();
	m_ComBox.SetCurSel(0);
	ShowDate(m_findType);
}


void CTeaHPage::OnBnClickedCoursename()
{
	// TODO: 在此添加控件通知处理程序代码
	if (-1 == m_findType) return;
	//显示此课程名称的所有成绩
	m_findType = -1;
	m_ComBox.EnableWindow(TRUE);
	InitComBox();
	m_ComBox.SetCurSel(0);
	ShowDate(m_findType);
}

void CTeaHPage::OnCbnSelchangeFind()
{
	if (m_BtnAll.GetCheck()) {
		ShowDate(0);
	}
	else if (m_BtnStuName.GetCheck()) {
		ShowDate(1);
	}
	else if (m_BtnCourseName.GetCheck()) {
		ShowDate(-1);
	}
	else{
		AfxMessageBox("ShowDate调用参数错误！");
	}
}


void CTeaHPage::ShowDate(int flags)
{
	// TODO: 在此处添加实现代码.
	CString sql;
	CString name;
	switch (flags)
	{
	case 0://all
		sql.Format("select r.class_no 班级,r.student_no 学号,student_name 学生姓名, c.course_no 课程编号,course_name 课程名称,score 成绩 "
			"from results r join course c on r.course_no=c.course_no "
			"join student s on r.student_no=s.student_no where r.teacher_no=%s;", m_TeaNo);
		break;
	case 1://student
		m_ComBox.GetLBText(m_ComBox.GetCurSel(), name);
		sql.Format("select r.student_no 学号,student_name 学生姓名,r.class_no 班级, course_name 课程名称,score 成绩 "
			"from results r join course c on r.course_no=c.course_no "
			"join student s on r.student_no=s.student_no where r.teacher_no=%s and student_name='%s';", m_TeaNo, name);
		break;
	case -1://course
		m_ComBox.GetLBText(m_ComBox.GetCurSel(), name);
		sql.Format("select r.course_no 课程编号,course_name 课程名称,r.class_no 班级,student_name 学生姓名,score 成绩 "
			"from results r join course c on r.course_no=c.course_no "
			"join student s on r.student_no=s.student_no where r.teacher_no=%s and course_name='%s';", m_TeaNo, name);
		break;
	default:
		AfxMessageBox("ShowDate函数参数错误");
		break;
	}
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	//AfxMessageBox(sql);
	int nCount = set.GetFieldCout();
	int nColumnCount = m_TeaList.GetHeaderCtrl()->GetItemCount();
	while (m_TeaList.DeleteColumn(0));
	m_TeaList.DeleteAllItems();
	CString strName;
	for (int i = 0; i < nCount; i++) {
		set.GetFieldName(i, strName);
		//AfxMessageBox(strName);
		m_TeaList.InsertColumn(i, strName, LVCFMT_LEFT, 100);
	}
	if (!set.IsBOF()) {
		set.MoveFirst();
	}
	CString strValue;
	int nItem = 0;
	while (!set.IsEOF()) {
		for (int i = 0; i < nCount; i++) {
			set.GetFieldValue(i, strValue);
			if (0 == i) {
				m_TeaList.InsertItem(nItem, strValue);
			}
			else {
				m_TeaList.SetItemText(nItem, i, strValue);
			}
		}
		nItem++;
		set.MoveNext();
	}

}


void CTeaHPage::InitComBox()
{
	// TODO: 在此处添加实现代码.
	m_ComBox.ResetContent();
	CString tableName;
	CString sql;
	if (1 == m_findType) {
		sql.Format("select student_name from setcourse se join course c on se.course_no=c.course_no join student s on se.student_no=s.student_no where teacher_no=%s group by se.student_no;",m_TeaNo);
		}
	else if (-1 == m_findType) {
		sql.Format("select course_name from course where teacher_no=%s;", m_TeaNo);
	}
	else{
		return;
	}
	CAdoRecordset set;
	set.OpenSql(sql, &m_db);
	if (!set.IsBOF()) {
		set.MoveFirst();
	}
	CString strValue;
	while (!set.IsEOF()) {
		set.GetFieldValue(0, strValue);
		m_ComBox.AddString(strValue);
		set.MoveNext();
	}
}


void CTeaHPage::OnBnClickedIuscore()
{
	// TODO: 在此添加控件通知处理程序代码
	CScore score(this);
	score.GetTeNo(m_TeaNo);
	score.DoModal();
	OnCbnSelchangeFind();
}


BOOL CTeaHPage::PreTranslateMessage(MSG* pMsg)
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