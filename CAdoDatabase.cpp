#include "CAdoDatabase.h"



CAdoDatabase::CAdoDatabase()
{
}


CAdoDatabase::~CAdoDatabase()
{
}

BOOL CAdoDatabase::Open()
{
	HRESULT nRet = m_pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(nRet)) {
		return FALSE;
	}
	CString strConn = "Dsn=32;uid=root";
	try
	{
		//ÄãµÄADO´úÂë
		nRet = m_pConn->Open(_bstr_t(strConn), "root", "Ding0713.", -1);
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("´íÎóÃèÊö£º%s\n´íÎóÏûÏ¢%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}

	return TRUE;
}

void CAdoDatabase::Close()
{
	m_pConn->Close();
}
