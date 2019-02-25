#pragma once
#include "CAdoDatabase.h"
class CAdoRecordset
{
public:
	CAdoRecordset();
	~CAdoRecordset();
	BOOL OpenSql(CString strSql, CAdoDatabase* pDB);
	//��ȡ�ֶε�����
	long GetFieldCout();
	//��ȡָ���ֶε�����
	void GetFieldName(long nIndex, CString& strName);
	void GetFieldValue(long nIndex, CString& strValue);
	void MoveFirst();
	void MoveLast();
	void MovePrevious();
	void MoveNext();
	BOOL IsBOF();
	BOOL IsEOF();
	BOOL IsNULL();

public:
	_RecordsetPtr m_pSet;
};

