#include "text.h"

class CMyWinApp :public CWinApp {
	BOOL InitInstance();
public:
	virtual int ExitInstance();
};

class CMyFrameWnd :public CFrameWnd {

};
CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
	CoInitialize(NULL);
	CLoginDlg login;
	int nReturn = login.DoModal();//返回IDOK或IDCANCEL。如果返回的是IDCANCEL，则要调用WindowsCommDlgExtendedError函数来确定是否发生了一个错误。IDOK和IDCANCEL都是常量，它表明用户选择的是OK按钮还是Cancel按钮
	if(nReturn == -1){
		AfxMessageBox(_T("窗口创建失败！"));
		return FALSE;
	}else if (nReturn == IDCANCEL)//点击退出
	{
		return FALSE;
	}
	if (login.account_type == USERTYPE_STU) {
		CStuHPage hPage;
		hPage.GetStuNo(login.m_name);
		nReturn = hPage.DoModal();
		if (nReturn == -1) {
			AfxMessageBox(_T("窗口创建失败！"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//点击退出
		{
			return FALSE;
		}
		else if(nReturn == RELOGIN){
			InitInstance();
		}
	}
	if (login.account_type == USERTYPE_TEA) {
		CTeaHPage hPage;
		hPage.GetTeaNo(login.m_name);
		nReturn = hPage.DoModal();
		if (nReturn == -1) {
			AfxMessageBox(_T("窗口创建失败！"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//点击退出
		{
			return FALSE;
		}
		else if (nReturn == RELOGIN) {
			InitInstance();
		}
	}
	if (login.account_type == USERTYPE_ADM) {
		CAdminHPage hPage;
		hPage.GetAdminNo(login.m_name);
		nReturn = hPage.DoModal();
		if (nReturn == -1) {
			AfxMessageBox(_T("窗口创建失败！"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//点击退出
		{
			return FALSE;
		}
		else if (nReturn == RELOGIN) {
			InitInstance();
		}
	}
	CWinApp::InitInstance();

	return 0;
}

int CMyWinApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	CoUninitialize();
	return CWinApp::ExitInstance();
}
