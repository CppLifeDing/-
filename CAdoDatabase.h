#pragma once
#include "stdafx.h"
class CAdoDatabase
{
public:
	CAdoDatabase();
	~CAdoDatabase();
	BOOL Open();
	void Close();
public:
	_ConnectionPtr m_pConn;
};

