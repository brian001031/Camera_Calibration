#pragma once

#define  STR_Main							 L"Main"
#define  STR_AppNum							 L"AppNum"   
#define  STR_XFApp0							 L"XFApp0"
#define  STR_XFApp1							 L"XFApp1"
#define  STR_XFApp2							 L"XFApp2"
#define  STR_XFApp3							 L"XFApp3"
#define  STR_CleanWindowState			     L"CleanWindowState"
#define  STR_CheckSN                         L"CheckSN"
#define  STR_WindowX                         L"WindowX"
#define  STR_WindowY                         L"WindowY"
#define  STR_WindowW                         L"WindowW"
#define  STR_WindowH                         L"WindowH"
#define  STR_WindowWB                        L"WindowWB"
#define  STR_WindowHB                        L"WindowHB"
#define  STR_WindowWR                        L"WindowWR"
#define  STR_WindowHR                        L"WindowHR"
#define  STR_ServerIP                        L"ServerIP"


class CFG
{
public:
	CFG();
	~CFG();

	static CString GetConfigPath();
};

