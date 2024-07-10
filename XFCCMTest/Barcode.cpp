// Barcode.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "Barcode.h"
#include "afxdialogex.h"


// CBarcode �Ի���

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


// CBarcode ��Ϣ�������


BOOL CBarcode::OnInitDialog()
{
	CDialog::OnInitDialog();
	bBarcodeMode = FALSE;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	strBarcode = L"";
	m_Barcode.SetFocus(); 
	LoadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBarcode::OnEnChangeEditBarcode()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ����ר�ô����/����û���
	if ((pMsg->wParam == 0x60) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//�ƿ�����
		
		//AfxMessageBox(L"123");
		return TRUE;
	}
	if ((pMsg->wParam == 0x0d) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//�ƿ�����
		//OnOK();
		//AfxMessageBox(L"123");
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
