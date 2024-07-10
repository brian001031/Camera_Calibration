#include "stdafx.h"
#include "CFG.h"


CFG::CFG()
{
}


CFG::~CFG()
{
}

CString CFG::GetConfigPath()
{
	CString str;
	GetModuleFileName(NULL, str.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	str.ReleaseBuffer();
	int pos = str.ReverseFind('\\');
	str = str.Left(pos);
	str += "\\XFConfig.ini";

	return str;
}
