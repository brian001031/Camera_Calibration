// Manage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "Manage.h"
#include "afxdialogex.h"


// CManage �Ի���

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


// CManage ��Ϣ�������
BOOL CManage::OnInitDialog()
{
	//CManage::OnInitDialog();
	strPasswordCheck = L"";
	LoadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strPasswordCheck);
	CDialogEx::OnOK();
}
