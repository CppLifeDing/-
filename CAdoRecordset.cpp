#include "CAdoRecordset.h"
#include <iostream>


CAdoRecordset::CAdoRecordset()
{
}


CAdoRecordset::~CAdoRecordset()
{
}

BOOL CAdoRecordset::OpenSql(CString strSql, CAdoDatabase * pDB)
{
	//创建记录集对象
	HRESULT nRet = m_pSet.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet)) {
		return FALSE;
	}
	//调用open
	try {
		nRet = m_pSet->Open(_variant_t(strSql), (IDispatch*)pDB->m_pConn,
			adOpenForwardOnly, adLockBatchOptimistic, adCmdText);
		if (FAILED(nRet)) {
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"),
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}
	return TRUE;
}

long CAdoRecordset::GetFieldCout()
{
	return m_pSet->Fields->GetCount();
}

void CAdoRecordset::GetFieldName(long nIndex, CString & strName)
{
	strName = (char*)m_pSet->Fields->GetItem(nIndex)->GetName();
}

void CAdoRecordset::GetFieldValue(long nIndex, CString & strValue)
{
	_variant_t varValue = m_pSet->Fields->GetItem(nIndex)->GetValue();
	if (varValue.vt == VT_NULL) {
		strValue = "";
	}
	else {
		strValue = (char*)(_bstr_t)varValue;
	}
}

void CAdoRecordset::MoveFirst()
{
	m_pSet->MoveFirst();
}

void CAdoRecordset::MoveLast()
{
	m_pSet->MoveLast();
}

void CAdoRecordset::MovePrevious()
{
	m_pSet->MovePrevious();
}

void CAdoRecordset::MoveNext()
{
	m_pSet->MoveNext();
}

BOOL CAdoRecordset::IsBOF()
{
	return m_pSet->BOF;
}

BOOL CAdoRecordset::IsEOF()
{
	return m_pSet->adoEOF;
}

BOOL CAdoRecordset::IsNULL()
{
	return IsEOF() && IsBOF();
}
