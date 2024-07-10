
// JXCCMTest.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "MainFrm.h"
#include "Cfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJXCCMTestApp

BEGIN_MESSAGE_MAP(CJXCCMTestApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CJXCCMTestApp::OnAppAbout)
END_MESSAGE_MAP()


// CJXCCMTestApp ����

CJXCCMTestApp::CJXCCMTestApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("JXCCMTest.AppID.NoVersion"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CJXCCMTestApp ����

CJXCCMTestApp theApp;


// CJXCCMTestApp ��ʼ��

BOOL CJXCCMTestApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	 AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��

	int AppNum = GetPrivateProfileInt(STR_Main, STR_AppNum, 0, CFG::GetConfigPath());

	if (AppNum == 0)
	{	
		SetRegistryKey(STR_XFApp0);
	}
	else if (AppNum == 1)
	{
		SetRegistryKey(STR_XFApp1);
	}
	else if (AppNum == 2)
	{
		SetRegistryKey(STR_XFApp2);
	}
	else if (AppNum == 3)
	{
		SetRegistryKey(STR_XFApp3);
	}



	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);



	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CJXCCMTestApp::ExitInstance()
{
	//TODO:  �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	int State = GetPrivateProfileInt(STR_Main, STR_CleanWindowState, 0, CFG::GetConfigPath());
	if (State)
	{
		CleanState();
		m_bSaveState = FALSE;
	}


	return CWinAppEx::ExitInstance();
}

// CJXCCMTestApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEngMode();
	afx_msg void OnCentreCross();
	afx_msg void OnUpdateCross(CCmdUI *pCmdUI);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CJXCCMTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CJXCCMTestApp::LoadCustomState()
{
	//m_bSaveState = FALSE;
}

void CJXCCMTestApp::SaveCustomState()
{
	//m_bSaveState = FALSE;
}

// CJXCCMTestApp ��Ϣ�������



