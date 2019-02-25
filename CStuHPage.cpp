// CStuHPage.cpp: 实现文件
//

#include "stdafx.h"
#include "text.h"
#include "CStuHPage.h"
#include "afxdialogex.h"


// CStuHPage 对话框

IMPLEMENT_DYNAMIC(CStuHPage, CDialogEx)

CStuHPage::CStuHPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUHPAGE, pParent)
{

}

CStuHPage::~CStuHPage()
{
	m_db.Close();
}

void CStuHPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_CLASS_NAME, m_ClassName);
	DDX_Control(pDX, IDC_NAME, m_StuName);
	DDX_Control(pDX, IDC_NUBER, m_StuNo);
}


BEGIN_MESSAGE_MAP(CStuHPage, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGEPASSWD, &CStuHPage::OnBnClickedChangepasswd)
	ON_BN_CLICKED(IDC_LISTSCORE, &CStuHPage::OnBnClickedListscore)
	ON_BN_CLICKED(IDC_SRELOGIN, &CStuHPage::OnBnClickedSrelogin)
	ON_BN_CLICKED(IDC_SRELOGIN, &CStuHPage::OnBnClickedSrelogin)
END_MESSAGE_MAP()


// CStuHPage 消息处理程序


void CStuHPage::OnBnClickedChangepasswd()
{
	// TODO: 在此添加控件通知处理程序代码
	CCPasswd CPasswd(m_no, USERTYPE_STU, this);
	CPasswd.DoModal();
}


void CStuHPage::OnBnClickedListscore()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List.DeleteAllItems();
	while (m_List.DeleteColumn(0));
	CAdoRecordset set;
	CString sql;
	sql.Format("select c.course_no 课程编号,course_name 课程名称,teacher_name 教师名称,score 成绩 "
		"from results r join course c on r.course_no=c.course_no "
		"join teacher t on c.teacher_no=t.teacher_no where r.student_no=%s;", m_no);
	set.OpenSql(sql, &m_db);
	int nCount = set.GetFieldCout();
	CString strName;
	for (int i = 0; i < nCount; i++) {
		set.GetFieldName(i, strName);
		//AfxMessageBox(strName);
		m_List.InsertColumn(i, strName, LVCFMT_CENTER, 100);
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
				m_List.InsertItem(nItem, strValue);
			}
			else {
				m_List.SetItemText(nItem, i, strValue);
			}
		}
		nItem++;
		set.MoveNext();
	}
}


BOOL CStuHPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_db.Open()) {
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	CString sql;
	CAdoRecordset set;
	sql.Format("select s.student_name,c.class_name "
				"from student s join classes c on s.class_no=c.class_no where student_no=%s",
					m_no);
	set.OpenSql(sql, &m_db);
	CString StuName;
	set.GetFieldValue(0, StuName);
	CString ClassName;
	set.GetFieldValue(1, ClassName);
	m_StuName.SetWindowTextA(StuName);
	m_StuNo.SetWindowTextA(m_no);
	m_ClassName.SetWindowTextA(ClassName);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CStuHPage::GetStuNo(CString StuNo)
{
	m_no = StuNo;
}



void CStuHPage::OnBnClickedSrelogin()
{
	EndDialog(RELOGIN);
}


BOOL CStuHPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
