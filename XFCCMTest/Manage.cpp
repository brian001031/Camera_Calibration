// Manage.cpp : 实现文件
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "Manage.h"
#include "afxdialogex.h"


// CManage 对话框

IMPLEMENT_DYNAMIC(CManage, CDialogEx)

CManage::CManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManage::IDD, pParent)
{

}

CManage::~CManage()
{
}

void CManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManage, CDialogEx)
	ON_BN_CLICKED(IDOK, &CManage::OnBnClickedOk)
END_MESSAGE_MAP()


// CManage 消息处理程序
BOOL CManage::OnInitDialog()
{
	//CManage::OnInitDialog();
	strPasswordCheck = L"";
	LoadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CManage::LoadConfig()
{
	CString strPath;
	TCHAR section[500];
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	strPath = strPath + L"\\" + L"Project" + L"\\" + L"OTPConfig.ini";

	GetPrivateProfileStringW(_T("VCMSTEP"), _T("xxxxxx"), _T(""), section, sizeof(section), strPath);
	strPassword = section;
}

void CManage::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strPasswordCheck);
	CDialogEx::OnOK();
}
