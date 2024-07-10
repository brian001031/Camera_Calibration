// Barcode.cpp : 实现文件
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "Barcode.h"
#include "afxdialogex.h"


// CBarcode 对话框

IMPLEMENT_DYNAMIC(CBarcode, CDialog)

CBarcode::CBarcode(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcode::IDD, pParent)
{

}

CBarcode::~CBarcode()
{
}

void CBarcode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BARCODE, m_Barcode);
}


BEGIN_MESSAGE_MAP(CBarcode, CDialog)
	ON_EN_CHANGE(IDC_EDIT_BARCODE, &CBarcode::OnEnChangeEditBarcode)
END_MESSAGE_MAP()


// CBarcode 消息处理程序


BOOL CBarcode::OnInitDialog()
{
	CDialog::OnInitDialog();
	bBarcodeMode = FALSE;
	// TODO:  在此添加额外的初始化
	strBarcode = L"";
	m_Barcode.SetFocus(); 
	LoadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBarcode::OnEnChangeEditBarcode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
 	CString str;
 	m_Barcode.GetWindowTextW(str);
	if (str.GetLength() == mBarcodeLength)
	{
 		strBarcode = str;
		CDialog::OnOK();
	}
}
void CBarcode::LoadConfig()
{
	CString strPath;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	strPath = strPath + L"\\" +  L"Project" + L"\\" + L"OTPConfig.ini";;

	mBarcodeLength = GetPrivateProfileInt(_T("BARCODE"), _T("BarcodeLenght"), 0, strPath);
	bBarcodeMode = GetPrivateProfileInt(_T("BARCODE"), _T("BarcodeMode"), 0, strPath);

}



BOOL CBarcode::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if ((pMsg->wParam == 0x60) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//移开焦点
		
		//AfxMessageBox(L"123");
		return TRUE;
	}
	if ((pMsg->wParam == 0x0d) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//移开焦点
		//OnOK();
		//AfxMessageBox(L"123");
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
