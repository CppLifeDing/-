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
	int nReturn = login.DoModal();//����IDOK��IDCANCEL��������ص���IDCANCEL����Ҫ����WindowsCommDlgExtendedError������ȷ���Ƿ�����һ������IDOK��IDCANCEL���ǳ������������û�ѡ�����OK��ť����Cancel��ť
	if(nReturn == -1){
		AfxMessageBox(_T("���ڴ���ʧ�ܣ�"));
		return FALSE;
	}else if (nReturn == IDCANCEL)//����˳�
	{
		return FALSE;
	}
	if (login.account_type == USERTYPE_STU) {
		CStuHPage hPage;
		hPage.GetStuNo(login.m_name);
		nReturn = hPage.DoModal();
		if (nReturn == -1) {
			AfxMessageBox(_T("���ڴ���ʧ�ܣ�"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//����˳�
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
			AfxMessageBox(_T("���ڴ���ʧ�ܣ�"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//����˳�
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
			AfxMessageBox(_T("���ڴ���ʧ�ܣ�"));
			return FALSE;
		}
		else if (nReturn == IDCANCEL)//����˳�
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
	// TODO: �ڴ����ר�ô����/����û���
	CoUninitialize();
	return CWinApp::ExitInstance();
}
