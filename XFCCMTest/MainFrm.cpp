
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "MainFrm.h"
#include "Cfg.h"
#include <string.h>  
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") //���û�����У������link����

TCHAR section[1024];
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_LOAD, &CMainFrame::OnLoad)
	ON_COMMAND_RANGE(IDC_START, IDC_START + 100, OnClick)  //ע���Զ�������
	ON_MESSAGE(WM_MY_MESSAGE, &CMainFrame::MyMessage)
	ON_WM_TIMER()
	ON_COMMAND(ID_MISC, &CMainFrame::OnShowConfigDlg)
	ON_COMMAND(ID_CALC_WINDOW, &CMainFrame::OnCalcWindow)
	ON_COMMAND(ID_SAVE_WINDOW, &CMainFrame::OnSaveWindow)
	ON_COMMAND(ID_WINDOW_LOG, &CMainFrame::OnWindowLog)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_LOG, &CMainFrame::OnUpdateWindowLog)
	ON_COMMAND(ID_WINDOW_TEST_ITEM, &CMainFrame::OnWindowTestItem)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TEST_ITEM, &CMainFrame::OnUpdateWindowTestItem)
	ON_WM_PAINT()
	ON_COMMAND(ID_SAVE_PIC, &CMainFrame::OnSavePic)
	ON_COMMAND(ID_PLAY_CAM, &CMainFrame::OnPlayCam)
	ON_COMMAND(ID_EngMode, &CMainFrame::OnEngMode)
	ON_UPDATE_COMMAND_UI(ID_EngMode, &CMainFrame::OnUpdateEngMode)
	ON_UPDATE_COMMAND_UI(ID_Blemish, &CMainFrame::OnUpdateBlemish)
	ON_UPDATE_COMMAND_UI(ID_PLAY_CAM, &CMainFrame::OnUpdatePlayCam)
	//ON_COMMAND(ID_CHECK3000K, &CMainFrame::OnCheck3000k)
	ON_COMMAND(ID_CHECK4000K, &CMainFrame::OnCheck4000k)
	ON_COMMAND(ID_CHECK5100K, &CMainFrame::OnCheck5100k)
	ON_COMMAND(ID_CHECK_MTF, &CMainFrame::OnCheckMtf)
	ON_UPDATE_COMMAND_UI(IDC_DLG, &CMainFrame::OnEnableGenMenu)
	ON_UPDATE_COMMAND_UI(IDC_DLG + 1, &CMainFrame::OnEnableItemMenu)
	ON_UPDATE_COMMAND_UI(IDC_DLG + 2, &CMainFrame::OnEnableOTPMenu)
	ON_UPDATE_COMMAND_UI(IDC_DLG + 3, &CMainFrame::OnEnableSenMenu)
	ON_UPDATE_COMMAND_UI(IDC_DLG + 4, &CMainFrame::OnEnablePOGMenu)
	ON_UPDATE_COMMAND_UI(IDC_START, &CMainFrame::OnEnableTestMenu)

	
	ON_COMMAND(ID_Blemish, &CMainFrame::OnBlemish)
	ON_COMMAND(ID_Cross, &CMainFrame::OnCommondCross)
	ON_UPDATE_COMMAND_UI(ID_Cross, &CMainFrame::OnUpdateCross)
	ON_COMMAND(ID_AWB, &CMainFrame::OnAwb)
	ON_UPDATE_COMMAND_UI(ID_AWB, &CMainFrame::OnUpdateAwb)
	ON_BN_CLICKED(IDC_TEST_INFO, &CMainFrame::OnBnClickedTestInfo)
END_MESSAGE_MAP()

// CMainFrame ����/����

static UINT indicators[] =
{
	//  	ID_SEPARATOR,           // ״̬��ָʾ��
	//  	ID_INDICATOR_CAPS,
	//  	ID_INDICATOR_NUM,
	// 	ID_INDICATOR_SCRL,

	ID_SEPARATOR,           // status line indicator   
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,           // status line indicator   
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2003);
	m_pApi = NULL;
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndMenuBar.EnableCustomizeButton(TRUE, -1, _T(""));
	//m_wndMenuBar.EnableHelpCombobox(1, _T(""), 80);
	//m_wndMenuBar.EnableMenuShadows();




	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_NORMAL, 0);
	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, 170);
	m_wndStatusBar.SetPaneInfo(2, ID_SEPARATOR, SBPS_NORMAL, 95);
	m_wndStatusBar.SetPaneInfo(3, ID_SEPARATOR, SBPS_NORMAL, 95);
	m_wndStatusBar.SetPaneInfo(4, ID_SEPARATOR, SBPS_NORMAL, 110);
	m_wndStatusBar.SetPaneInfo(5, ID_SEPARATOR, SBPS_NORMAL, 90);
	m_wndStatusBar.SetPaneInfo(6, ID_SEPARATOR, SBPS_NORMAL, 90);
	m_wndStatusBar.SetPaneInfo(7, ID_SEPARATOR, SBPS_NORMAL, 90);
	m_wndStatusBar.SetPaneInfo(8, ID_SEPARATOR, SBPS_NORMAL, 90);
	m_wndStatusBar.SetPaneInfo(9, ID_SEPARATOR, SBPS_NORMAL, 70);


	// TODO:  �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
	CDockingManager::SetDockingMode(DT_SMART);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);


	int State = GetPrivateProfileInt(STR_Main, STR_CleanWindowState, 0, CFG::GetConfigPath());
	int AppNum = GetPrivateProfileInt(STR_Main, STR_AppNum, 0, CFG::GetConfigPath());
	if (State)
	{
		int x = GetPrivateProfileInt(STR_Main, STR_WindowX, 0, CFG::GetConfigPath());
		int y = GetPrivateProfileInt(STR_Main, STR_WindowY, 0, CFG::GetConfigPath());
		int w = GetPrivateProfileInt(STR_Main, STR_WindowW, 0, CFG::GetConfigPath());
		int h = GetPrivateProfileInt(STR_Main, STR_WindowH, 0, CFG::GetConfigPath());
		if (AppNum == 0)
		{
			SetWindowPos(NULL, x, y, w, h, SWP_NOACTIVATE | SWP_NOZORDER);
		}
		else if (AppNum == 1)
		{
			SetWindowPos(NULL, x, y, w, h, SWP_NOACTIVATE | SWP_NOZORDER);
		}
		else if (AppNum == 2)
		{
			SetWindowPos(NULL, x, y, w, h, SWP_NOACTIVATE | SWP_NOZORDER);
		}
		else
		{
			SetWindowPos(NULL, x, y, w, h, SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndTestItem.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTestItem);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);


	// ���ÿ���(��ס Alt �϶�)�������Զ���
//	CMFCToolBar::EnableQuickCustomization();
	//m_bIsEngMode = TRUE;//��������ģʽ
	int offset = 250;
	m_bIsTest = FALSE;
	m_bIsPlay = FALSE;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP;
	CWnd *pWnd = CWnd::FromHandle(m_wndMenuBar.m_hWnd);
	m_btnPlay.Create(_T("����"), dwStyle, CRect(offset, 0, offset + 40, 20), pWnd, IDC_START);
	pWnd = CWnd::FromHandle(m_wndView.m_hWnd);
	dwStyle = WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER;

	m_wndView.m_DisplayCtrl.Create(_T(""), dwStyle, CRect(0, 0, 0, 0), pWnd, 2000);
	m_wndView.m_DisplayCtrl.SetTransparent(TRUE);
	SetDisplayCtrlText(L"");

	AppInfo appInfo;
	appInfo.AppNum = GetPrivateProfileInt(STR_Main, STR_AppNum, 0, CFG::GetConfigPath());
	appInfo.hMain = m_hWnd;
	appInfo.hDisplay = m_wndView.m_DisplayCtrl.m_hWnd;
	appInfo.hTestInfo = m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.m_hWnd;
	
	m_pApi = XFApiCreate(appInfo);//�����豸

	CString strTemp;
	strTemp.Format(L"  ������(%d)   ", appInfo.AppNum + 1);
	SetWindowText(m_pApi->m_pInterface->pST->SoftVersion + strTemp);

	LoadTestItem();

	CMenu *pMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (pMenu == NULL) return 0;
	CMenu *pPopMenu = pMenu->GetSubMenu(2);
	pPopMenu->RemoveMenu(0, MF_BYPOSITION);

	CStringArray *pDlgName = m_pApi->m_pUI->GetDlgName();
	for (int i = 0; i < pDlgName->GetSize(); i++)
	{
		pPopMenu->AppendMenu(MF_POPUP, IDC_DLG + i, pDlgName->GetAt(i)); // ���DLG�˵�
	}
	m_bIsEngMode = m_pApi->m_pInterface->ReadConfigInt(L"Main", L"bIsEngMode", 0);
	//��ʼ���߳̾��
	m_hManualTest = NULL;
	m_hAutoTestFlag = NULL;
	if (m_pApi->m_pInterface->GetConfig()->bIsMachine&&(!m_pApi->m_pInterface->pST->ManualTest))
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(0, 0, 0));
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.ShowWindow(SW_HIDE);
		SetTimer(2, 1500, NULL);
	}
	else
	{

		SetButtonFont();
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(120, 120, 120));
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(330);
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"�������");
		//���ڲ���ʱ����濨�������������߳�
		bIsProcess = FALSE;
		bManualTestFlag = TRUE;
		m_bIsManualTest = FALSE;
		m_hManualTest = CreateEvent(NULL, TRUE, FALSE, NULL);
		AfxBeginThread(MuaualTestThead, this);

		//ɨ���ĵ��߳�
		m_hAutoTestFlag = CreateEvent(NULL, TRUE, FALSE, NULL);
		AfxBeginThread(AutoTestThead, this);
		bAutoTestFlag = TRUE;
		SetTimer(3, 3000, NULL);

	}

	m_pApi->m_pInterface->pST->bIsBlemish = FALSE;//��ʼ������flag
	m_pApi->m_pInterface->m_bCross = FALSE;//��ʼ������ʮ�ּ�
	m_pApi->m_pInterface->m_AWBEN1 = FALSE;//��ʼ������ʮ�ּ�
	m_pApi->m_pInterface->m_AWBEN1 = FALSE;//��ʼ������ʮ�ּ�
	m_LogLenght = 0;

	m_Run_Usc_Count = 1;

	//ȡ��RAW��D�O��
	m_save_Raw_Multi = m_pApi->m_pInterface->ReadConfigInt(L"SavePic", L"m_Raw_More", 0);
	save_Raw_Num = m_pApi->m_pInterface->ReadConfigInt(L"SavePic", L"m_Raw_Number", 0);

	if (!m_save_Raw_Multi){
		m_pApi->m_pInterface->Raw_Multi = false;
		m_pApi->m_pInterface->Raw_Num = 1;
	}
	else{
		m_pApi->m_pInterface->Raw_Multi = m_save_Raw_Multi;
		m_pApi->m_pInterface->Raw_Num = save_Raw_Num;
	}

	//ȡ��RAW�yԇ���x�_��
	Run_Raw_dis_Script  = m_pApi->m_pInterface->ReadConfigInt(L"Raw_Distance", L"m_Run_distance", 0);
	m_pApi->m_pInterface->Raw_dis_test = Run_Raw_dis_Script;

	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	// �����������

	int w;
	int h;
	int State = GetPrivateProfileInt(STR_Main, STR_CleanWindowState, 0, CFG::GetConfigPath());

	if (State)
	{
		w = GetPrivateProfileInt(STR_Main, STR_WindowWB, 0, CFG::GetConfigPath());
		h = GetPrivateProfileInt(STR_Main, STR_WindowHB, 0, CFG::GetConfigPath());
	}
	else
	{
		w = 800;
		h = 200;
	}

	if (!m_wndOutput.Create(L"���", this, CRect(0, 0, w, h), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	if (State)
	{
		w = GetPrivateProfileInt(STR_Main, STR_WindowWR, 0, CFG::GetConfigPath());
		h = GetPrivateProfileInt(STR_Main, STR_WindowHR, 0, CFG::GetConfigPath());
	}
	else
	{
		w = 260;
		h = 800;
	}

	if (!m_wndTestItem.Create(L"������Ŀ", this, CRect(0, 0, w, h), TRUE, 10010, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������Ϣ\n");
		return FALSE; // δ�ܴ���
	}
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->Create();
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


BOOL CMainFrame::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (m_hManualTest != NULL)
	{
		bManualTestFlag = FALSE;
		WaitForSingleObject(m_hManualTest, 3000);
		CloseHandle(m_hManualTest);
	}
	if (m_hAutoTestFlag!=NULL)
	{
		bAutoTestFlag = FALSE;
		WaitForSingleObject(m_hAutoTestFlag, 3000);
		CloseHandle(m_hAutoTestFlag);
	}


	m_pApi->StopTestThread();
	m_pApi->FreeResource();

	return CFrameWndEx::DestroyWindow();
}



void CMainFrame::OnLoad()
{
	// TODO:  �ڴ���������������

	Stop();
	CFileDialog fileDlg(TRUE, L"xf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"xf�ļ�(*.xf)|*xf|ini�ļ�(*.ini)|*.ini||");

	if (fileDlg.DoModal() == IDOK)
	{
		if (m_pApi->m_pInterface->LoadSensorConfig(fileDlg.GetPathName()) == FALSE)
		{
			AddLog(L"ERROR:����Sensor�����ļ�ʧ��", COLOR_RED);
		}
		else
		{
			int pos;
			CString temp;
			CString str;
			temp = fileDlg.GetPathName();
			pos = temp.ReverseFind('\\');
			temp = temp.Right(temp.GetLength() - pos - 1);

			if (fileDlg.GetFileExt() == L"ini")
			{
				temp.Replace(L"ini", L"xf");
			}

			CopyFile(fileDlg.GetPathName(), m_pApi->m_pInterface->GetProjectDir() + temp, TRUE);

			WritePrivateProfileString(STR_Main, STR_ProjectFile, L"Project\\" + temp, m_pApi->m_pInterface->GetConfigPath());
			AddLog(fileDlg.GetPathName() + L" �Ѽ���");
		}

	}

}


void CMainFrame::OnShowConfigDlg()
{
	// TODO:  �ڴ���������������
}

void CMainFrame::StartTest()
{
	m_pApi->StartTestThread();
}

void CMainFrame::StopTest()
{
	m_bIsTest = FALSE;
	m_pApi->StopTestThread();
	//m_pApi->m_pInterface->CloseCamera();
	m_btnPlay.SetWindowText(L"��ʼ");

	for (UINT i = 0; i < m_pApi->m_ProjectRun.size(); i++)
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestItem.SetItemText(i, 2, L"");
	}
	CleanText();

}

void CMainFrame::OnClick(UINT uID)  //��ť���� 5000-5050,�˵����� 5050-5100
{
	CString str;
	if (uID >= IDC_DLG) //�˵����¼�
	{
		if (uID > IDC_DLG)
		{
			if (m_bIsTest)
			{
				StopTest();
			}
		}
		m_pApi->m_pUI->ShowDlg(uID - IDC_DLG);
		return;
	}

	switch (uID)   //��ť�¼�
	{
	case ID_PLAY_CAM:

		if (m_bIsTest)
		{
			StopTest();
		}

		if (m_bIsPlay)
		{
			CleanText();
			KillTimer(1);
			m_pApi->m_pInterface->StopPreview();
			m_pApi->m_pInterface->CloseCamera();
			SetDisplayCtrlText(L"");
			m_bIsPlay = FALSE;
		}
		else
		{
			m_pApi->m_pInterface->InitTestTime();
			//m_pApi->m_pInterface->SwitchSensorTable(0);//�л���һ������ͷ
			if (m_pApi->m_pInterface->OpenCamera())
			{
				m_bIsPlay = TRUE;
				SetDisplayCtrlText(L"");
				m_pApi->m_pInterface->PlayVideo();
				m_pApi->m_pInterface->StartPreview();
				SetTimer(1, 0, NULL);  //֡�ʼ�ʱ��
			}
		}



		break;
	case IDC_START:
		if (m_pApi->m_pInterface->GetSensor() == NULL)
		{
			SetDisplayCtrlText(L"оƬ�����ļ�����ʧ��!!!", COLOR_RED);
			break;
		}

		str.Format(L"uID=%d", uID);
		AddLog(str);
		if (!m_bIsPlay)
		{
			if (m_pApi->m_pInterface->CameraIsPlay())
			{
				m_pApi->m_pInterface->StopPreview();
				m_pApi->m_pInterface->CloseCamera();
			}

			m_pApi->m_pInterface->OpenCamera();

			if (m_pApi->m_ProjectRun.size() == 0)
			{
				AddLog(L"δ����κβ�����Ŀ,����Ӳ�����Ŀ", COLOR_RED);
				m_pApi->m_pInterface->CloseCamera();
				break;
			}
			else
			{
				m_pApi->m_pInterface->PlayVideo();

				//setVCM
				m_pApi->m_pInterface->pST->SetVCMStep(0);
				SetTimer(1, 1000, NULL);  //֡�ʼ�ʱ��
				SetDisplayCtrlText(L"");
				// 				bool mExp = m_pApi->m_pInterface->ExposureEx(130, 5, 0, NULL, EXP_Y, m_pApi->m_pInterface->GetSensor()->width / 2, m_pApi->m_pInterface->GetSensor()->height / 2, 10, 3);
				// 				if (!mExp)
				// 				{
				// 					AddLog(L"AE�ع�NG", COLOR_RED);
				// 					m_btnPlay.SetWindowText(L"����");
				// 					m_bIsPlay = TRUE;
				// 					m_IsFocus = FALSE;
				// 					SetDisplayCtrlText(L"");
				// 					break;
				// 				}
				m_btnPlay.SetWindowText(L"ֹͣ");
				m_bIsPlay = TRUE;
				m_IsFocus = TRUE;
				AddLog(L"����");
			}
		}
		else
		{
			//m_pApi->m_pInterface->StopPreview();
			m_pApi->m_pInterface->CloseCamera();
			AddLog(L"ֹͣͼ��", COLOR_BROWN);
			m_btnPlay.SetWindowText(L"����");
			m_bIsPlay = FALSE;
			m_IsFocus = FALSE;
			SetDisplayCtrlText(L"");
			break;
		}
	default:
		break;
	}

}


void CMainFrame::Stop()
{
	if (m_bIsTest)
	{
		StopTest();
	}

	if (m_bIsPlay)
	{
		KillTimer(1);
		m_pApi->m_pInterface->StopPreview();
		m_pApi->m_pInterface->CloseCamera();
		m_bIsPlay = FALSE;
	}
}

void CMainFrame::AddLog(CString text, COLORREF color, int yHeight)
{
	m_wndOutput.m_wndOutputLog.AddLog(text, color, yHeight);
}

void CMainFrame::AddLog(WPARAM wParam)
{
	TextInfo* textInfo = (TextInfo*)wParam;
	m_wndOutput.m_wndOutputLog.AddLog(textInfo->text, textInfo->textColor, textInfo->textHeight);
}

void CMainFrame::SetDisplayCtrlText(CString text, COLORREF BackColor, COLORREF textColor, int FontSize)
{
	m_wndView.m_DisplayCtrl.SetTextColor(textColor);
	m_wndView.m_DisplayCtrl.SetBackColor(BackColor);
	m_wndView.m_DisplayCtrl.SetFontSize(FontSize);
	m_wndView.m_DisplayCtrl.SetWindowText(text);
}
void CMainFrame::SetDisplayCtrlText(WPARAM wParam)
{
	TextInfo* textInfo = (TextInfo*)wParam;
	m_wndView.m_DisplayCtrl.SetBackColor(textInfo->backColor);
	m_wndView.m_DisplayCtrl.SetFontSize(textInfo->textHeight);
	m_wndView.m_DisplayCtrl.SetTextColor(textInfo->textColor);
	m_wndView.m_DisplayCtrl.SetWindowText(textInfo->text);
}


void CMainFrame::ShowTestItemDlg(UINT item)
{
	if (item >= m_pApi->m_ProjectRun.size())
	{
		AddLog(L"��ǰ������Ŀδ֧������", COLOR_RED);
		return;
	}


	
	if (m_pApi->m_ProjectRun[item].Instance->m_DlghWnd != NULL)
	{
	//	m_pApi->HideAllDlg();

	//	HWND hDlg = m_pApi->m_ProjectRun[item].Instance->m_DlghWnd;
	//	CWnd::FromHandle(hDlg)->ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, 0);
	//	CWnd::FromHandle(hDlg)->ModifyStyle(WS_POPUP | WS_SIZEBOX | WS_THICKFRAME | WS_CAPTION | DS_MODALFRAME, WS_CHILD);
	//	::SetParent(hDlg, m_pApi->m_pUI->GetConfigDlgHWND());
		
	//	CRect wndRect;

	//	::GetClientRect(m_pApi->m_pUI->GetConfigDlgHWND(), &wndRect);
	//	::MoveWindow(hDlg, wndRect.left, wndRect.top, wndRect.Width(), wndRect.Height(), TRUE);
	//	::ShowWindow(hDlg, SW_SHOW);

		m_pApi->m_ProjectRun[item].Instance->ShowSpecDlg();
	//	HWND hwnd = m_pApi->m_ProjectRun[item].Instance->m_DlghWnd;
 		//::SetWindowPos(hwnd, NULL, 100, 100, 640, 480, SWP_NOZORDER);
	}
	else
	{
		AfxMessageBox(L"��ǰ������Ŀδ��Ӵ���");
	}
}


LRESULT CMainFrame::MyMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class 
	
	switch (lParam)
	{
	case MyMessage::PLAY_VIDEO:                //����  
		OnClick(ID_PLAY_CAM);	
		break;
	case MyMessage::STOP_VIDEO:                //ֹͣ
		OnClick(ID_PLAY_CAM);
		break;
	case MyMessage::ADDLOG:                    //���LOG�����Ϣ
		AddLog(wParam);
		break;
	case MyMessage::SET_DISPLAYCTRL_TEXT:      //����CChildView������ʾ�ؼ����ַ�����ɫ
		SetDisplayCtrlText(wParam);
		break;
	case MyMessage::LOAD_ITEM:                 //���ݲ�����Ŀ�������ز�����Ŀ
		DeleteTestItem();                      //���ز�����Ŀǰ,����Ѿ��Ѽ��صĲ�����Ŀ
		m_pApi->InitPlugins();                 //���³�ʼ��������Ŀ����
		LoadTestItem();
		break;
	case MyMessage::DBCLICK_TEST:               //��Ӧ������Ŀ�ؼ�˫���¼�
		ClickTestBtn(*(UINT*)wParam);
		break;
	case MyMessage::CREATE_TEST_THREAD:         //����������Ŀ�߳�
		m_pApi->StartTestThread();
		break;
	case MyMessage::SET_TEST_ITEM_TIME:         //������Ŀ���ʱ��
		SetTestItemTime(wParam);
		break;
	case MyMessage::SHOW_TEST_ITEM_DLG:         //��ʾ������Ŀ�Ի���
		ShowTestItemDlg(*(UINT*)wParam);
		break;
	case MyMessage::FlowTEST:         //��ʾ������Ŀ�Ի���
		StartFlowTest();
		break;
	}
	return TRUE;
}

void CMainFrame::ReplaceBarcodeString(CString strIdentify, CString strBarcode)
{
	CStdioFile file;
	CString contents =_T("") ,rightstr = _T("");
	CString strText = strIdentify, strPath = _T(""), str_infoTXT = _T(""), str_barcode_right = _T("");
	int pos_read = 0, title_len = strText.GetLength();
	int size;
	DWORD dwPos = 0;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);	
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	//str_infoTXT = strPath + L"\\Tof_Calib_release_20210311\\TestData\\inFo.txt";
	str_infoTXT = strPath + L"\\"+ m_pApi->m_pInterface->stof_cali_bat + L"\\TestData\\inFo.txt";
	 	
	if (file.Open(str_infoTXT, CFile::modeRead))
	{
		//size = file.GetLength();
		//file.Seek(pos_read + size, CFile::begin); 			
		while (file.ReadString(contents))		
		{				 
			int found = contents.Find(strText);					
			if (found != -1){
				pos_read = file.GetPosition();//��¼��������һ��;
				
				if (found >= 0 )
				{
					str_barcode_right = contents.Right(contents.GetLength() - title_len);					
					size = str_barcode_right.GetLength();
					/*
					for (int del = title_len; del <= title_len + size; del++)
						contents.Delete(del, title_len*2);					 
					contents.Insert(title_len+1, str_barcode_right);
					file.WriteString(contents);*/				 					 
					dwPos = (DWORD)file.GetPosition() + title_len -3 - (_tcslen(contents) + _tcslen(_T("\r\n")));
					break;
				}					
			}				
		}
		file.Close();
		file.Open(str_infoTXT, CFile::modeWrite);
		file.Seek(dwPos, CFile::begin);
		file.WriteString(strBarcode);
		file.Close();
		AddLog(L"�Ѹ���У���l�a->" + strBarcode, COLOR_RED);
	}else{
		AddLog(L"�x�n Calib_release TestData inFo.txt", COLOR_RED);
		return;	
	}
	return;
}


BOOL CMainFrame::MakeMulitBarcodeDirPath(LPWSTR  szPath)
{
	char copy_path[1024];
	//memset(copy_path,'\0' , sizeof(copy_path));
	int len = 0, len2 = 0;
	char *last_mozi = NULL;
	//char *mozi = NULL;
	wchar_t d_buf[1024], dd_buf[1024];
	memset(d_buf, '\0', sizeof(d_buf));
	memset(dd_buf, '\0', sizeof(dd_buf));

	//sprintf_s(copy_path, sizeof(copy_path), szPath);
	//len = strlen(copy_path);
	len = wcslen(szPath);
	char *resultStr = new char[len + 1];
	wsprintfA(resultStr, "%S", szPath);
	last_mozi = resultStr;
	//last_mozi = CharPrev(resultStr, &resultStr[len]);

	if (last_mozi == (&resultStr[len - 1]))
	{
		if (resultStr[len - 1] == '\\' || resultStr[len - 1] == '/')
		{
			resultStr[len - 1] = 0x00;
		}
	}

#if defined(UNICODE) 
	//void CommonFun::TC2C(const PTCHAR tc, char * c)
	WideCharToMultiByte(CP_ACP, 0, szPath, -1, resultStr, wcslen(szPath), 0, 0);
	resultStr[wcslen(szPath)] = 0;
#else 
	lstrcpy((PTSTR)c, (PTSTR)tc);
#endif 
	//memset(copy_path, '\0', len);
	//sprintf(copy_path, len, szPath);
	const WCHAR *pwcsName; //LPCWSTR
	const size_t cSize = strlen(resultStr) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, resultStr, cSize);
	_bstr_t b(wc);
	const char* c = b;

	// required size
	int size = MultiByteToWideChar(CP_ACP, 0, c, -1, NULL, 0);
	// allocate it
	pwcsName = new WCHAR[cSize];
	MultiByteToWideChar(CP_ACP, 0, c, -1, (LPWSTR)pwcsName, size);
	 
	//LPTSTR lpsz = (LPTSTR)pwcsName;
	CharPrev(pwcsName, pwcsName);
	LPTSTR mozi = CharNext(pwcsName);

	while (*mozi != '\0')
	{
		if (*mozi == '\\' || *mozi == '/')
		{
			char output[256];
			memset(d_buf, '\0', sizeof(d_buf));
			memcpy(d_buf, copy_path, mozi - pwcsName);
			sprintf(output, "%s", d_buf);

			const size_t cSize2 = strlen(output) + 1;
			wchar_t* wc2 = new wchar_t[cSize2];
			mbstowcs(wc2, output, cSize2);

			if (!PathFileExists(wc2))
			{
				if (!CreateDirectory(wc2, NULL))
				{
					return FALSE;
				}
			}
		}
		mozi = CharNext(pwcsName);
	}


	char outputFinal[256];
	sprintf(outputFinal, "%s", mozi);

	const size_t cSizefinal = strlen(outputFinal) + 1;
	wchar_t* create_sub = new wchar_t[cSizefinal];
	mbstowcs(create_sub, outputFinal, cSizefinal);

	if (!PathFileExists(create_sub))
	{
		if (!CreateDirectory(create_sub, NULL))
		{
			return FALSE;
		}
	}

	return TRUE;
}



void CMainFrame::StartFlowTest(void)
{
	/*****�ֶ�ɨ��20190307*****/
	//һ��������ɨ�벻��ͬʱ����

	if (m_pApi->m_pInterface->pST->bBarcodeMode == 1)
	{
		m_pApi->m_pInterface->pST->strBarcode = L"";
		pDlg.strBarcode.MakeUpper();
		AddLog(L"��ά��ɨ�����BarCode: " + pDlg.strBarcode, COLOR_BROWN);
		m_pApi->m_pInterface->pST->strBarcode = pDlg.strBarcode;
		if (pDlg.strBarcode.GetLength() != m_pApi->m_pInterface->pST->m_BCLenght)
		{
			AddLog(L"��ά��ɨ�賤�ȴ���,����ɨ��... ", COLOR_RED);
			OnTimer(4);
			return;
		}
	}
			
	CString str_xini = m_pApi->m_pInterface->GetConfigPath();
	GetPrivateProfileStringW(STR_BATPROFILE, STR_TOFIQC, _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->stof_iqc_bat = section;
	GetPrivateProfileStringW(STR_BATPROFILE, STR_TOFCALI, _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->stof_cali_bat = section;
	GetPrivateProfileStringW(STR_BATPROFILE, STR_TOFOQC, _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->stof_oqc_bat = section;
	GetPrivateProfileStringW(STR_BACKUPPATH, STR_BACKUPPROFILE, _T(""), section, sizeof(section), str_xini);
	CString strBackUp_Profile = section;
	GetPrivateProfileStringW(STR_BACKUPPATH, STR_BACKUPDISTANCERAW, _T(""), section, sizeof(section), str_xini);
	CString strBackUp_Dis_Raw = section;

	

	//�o䛶���x��܉�Ƅ�CM
	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_1"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_1_array = section;	
	sCy1 = m_pApi->m_pInterface->s_Cycle_1_array;
	   
	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_2"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_2_array = section;
	sCy2 = m_pApi->m_pInterface->s_Cycle_2_array;

	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_Cali_All"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_3_cali_array = section;
	sCy_Cali = m_pApi->m_pInterface->s_Cycle_3_cali_array;


	//����x�yԇ�����ж����	 
	GetPrivateProfileStringW(L"Mulit_Direction_Status", _T("m_direction_St"), _T(""), section, sizeof(section), str_xini);
	_mulit_status = m_pApi->m_pInterface->Mulit_Ack_Status = _wtoi(section);
	 		 
	//����EEPROM �ռ��Y�τ����Δ�
	GetPrivateProfileStringW( L"Eeprom_Ack_Mode", _T("m_eeprom_acknum"), _T(""), section, sizeof(section), str_xini);
	_eeprom_ack  = m_pApi->m_pInterface->Eeprom_Ack_Num = _wtoi(section);
		 	 	  

	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_2"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_2_array = section;
	

	//���l�a���݌���XFConfig.ini 2021.03.12	
	WritePrivateProfileString(STR_BARCODE_RECORD, STR_BARCODE_PATH, m_pApi->m_pInterface->pST->strBarcode, str_xini);



	//���Ԅӻ����
	if (_eeprom_ack == 2){		
		GetPrivateProfileStringW(STR_BARCODE_RECORD, STR_IDENTIFY_BARCODE, _T(""), section, sizeof(section), str_xini);
		m_pApi->m_pInterface->s_Identify_barcode = section;
		
		CString  sIdent = m_pApi->m_pInterface->s_Identify_barcode;
		int idencheck_len = sizeof(sIdent)+1;
		CString  subbarcode = m_pApi->m_pInterface->pST->strBarcode.Left(idencheck_len);   //�Ҍ�����(EX:AT004,BT001)

		//�����Ȍ����`
		if (sIdent.Compare(subbarcode) == -1 || sIdent.Compare(subbarcode) == 1)
		{			
			AddLog(L"�l�a�Ȍ�NG!,���e�_�^��:" + subbarcode, COLOR_RED);
			OnTimer(4);
			return;
		}
		else{
			//OK
			AddLog(L"�l�a�Ȍ�OK,�_�^������:" + subbarcode, COLOR_BLUE);
			ReplaceBarcodeString(m_pApi->m_pInterface->s_Identify_barcode, m_pApi->m_pInterface->pST->strBarcode);
		}				
	}
		
	// �����l�a�Y�ϊA
#if 0

	CString str = m_pApi->m_pInterface->pST->strBarcode;
	USES_CONVERSION; 
	LPWSTR pwStr = new wchar_t[str.GetLength() + 1];
	wcscpy(pwStr, T2W((LPTSTR)(LPCTSTR)str));
	if (MakeMulitBarcodeDirPath(pwStr))
		return;
#else	
	//Run IQC,Calibration,OQC
	if (m_pApi->m_pInterface->Raw_dis_test == 0 || m_pApi->m_pInterface->Raw_dis_test == 3){
		CString  strBarcode = m_pApi->m_pInterface->pST->strBarcode;
		CString strAll = _T(""), strPro_IQC = _T(""), strPro_Cali = _T(""), strPro_OQC = _T("");
		CFileFind finder;
	

		if (PathIsDirectory(strBackUp_Profile) == FALSE)
			CreateDirectory(strBackUp_Profile, NULL);

		//�����ӗl�a�Y�ϊA
		strBackUp_Profile += L"\\" + strBarcode;

		m_pApi->m_pInterface->sbackUp = strBackUp_Profile;
		m_pApi->m_pInterface->sbackUp_IQC = strPro_IQC = strBackUp_Profile + L"\\IQC";
		m_pApi->m_pInterface->sbackUp_Cali = strPro_Cali = strBackUp_Profile + L"\\Calibration";
		m_pApi->m_pInterface->sbackUp_OQC = strPro_OQC = strBackUp_Profile + L"\\OQC";

		if (PathIsDirectory(strBackUp_Profile) == FALSE)
			CreateDirectory(strBackUp_Profile, NULL);

		if (PathIsDirectory(strPro_IQC) == FALSE)
			CreateDirectory(strPro_IQC, NULL);

		if (PathIsDirectory(strPro_Cali) == FALSE)
			CreateDirectory(strPro_Cali, NULL);

		if (PathIsDirectory(strPro_OQC) == FALSE)
			CreateDirectory(strPro_OQC, NULL);


		if (_eeprom_ack == 2) //ȫ�Ԅӻ�������Ҫ�A�����
		{
			//���ȫ��BackUp test�Y��
			for (int t = 0; t < 3; t++){
				if (t == 0)
					strAll = strPro_IQC;
				else if (t == 1)
					strAll = strPro_Cali;
				else if (t == 2)
					strAll = strPro_OQC;

				if (finder.FindFile(strAll))
					m_pApi->m_pInterface->RecursiveDelete(strAll);
			}		
		}	

		if (m_pApi->m_pInterface->Raw_dis_test == 3)
		{
			//���� Cycle_Cali_All һ�_ʼ�O�����ƄӽǶ�
			FastCalibration_CMD_Ack(m_pApi->m_pInterface->Raw_dis_test);
		}		
	}
	else{ 
		//Run Mulit_Get_Raw
		CString  strBarcode = m_pApi->m_pInterface->pST->strBarcode;
		CString strAll = _T(""), strPro_IQC = _T(""), strPro_Cali = _T(""), strPro_OQC = _T("");
		CFileFind finder;
		int file_count = 0;

		if (PathIsDirectory(strBackUp_Dis_Raw) == FALSE)
			CreateDirectory(strBackUp_Dis_Raw, NULL);

		//�����ӗl�a�Y�ϊA
		strBackUp_Dis_Raw += L"\\" + strBarcode;

		if (PathIsDirectory(strBackUp_Dis_Raw) == FALSE)
			CreateDirectory(strBackUp_Dis_Raw, NULL);

		CreateFile_forMulitRawDistance(strBackUp_Dis_Raw, m_pApi->m_pInterface->Raw_dis_test);		
	}

	
#endif

	/*****end****/
	if (!m_pApi->m_pInterface->pST->ManualTest)
	{
		return;
	}
	if (bIsProcess)
	{
		AddLog(L"��Ʒ���ڲ���...", COLOR_RED);
		return;
	}
	if (m_pApi->m_pInterface->GetSensor() == NULL)
	{
		SetDisplayCtrlText(L"оƬ�����ļ�����ʧ��!!!", COLOR_RED);
		return ;
	}
	if (m_bIsPlay)
	{
		KillTimer(1);
		m_pApi->m_pInterface->StopPreview();
		m_pApi->m_pInterface->CloseCamera();
		m_bIsPlay = FALSE;
	}

	if (!m_bIsManualTest)
	{
		if (m_pApi->m_ProjectRun.size() == 0)
		{
			AddLog(L"δ����κβ�����Ŀ,����Ӳ�����Ŀ", COLOR_RED);
		}
		else
		{

			m_wndOutput.SetFocus();//�ƿ�����
			SetTimer(1, 1000, NULL);  //֡�ʼ�ʱ��
			SetDisplayCtrlText(L"");
			m_bIsManualTest = TRUE;
			AddLog(L"��ʼ����");
			//DoTest();

			//����start�ļ�һ������
			if((m_pApi->m_pInterface->GetAppInfo()->AppNum == 1) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath1, L"start");
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath3, L"start");
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath4, L"start");
			}
			if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 0) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath1, 0) != 0)  //��·�����ļ�����ɾ��
				{
					DeleteFile(m_pApi->m_pInterface->pST->OTPCommandPath1);
				}
			}
			else if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 2) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath3, 0) != 0)  //��·�����ļ�����ɾ��
				{
					DeleteFile(m_pApi->m_pInterface->pST->OTPCommandPath3);
				}
			}
			else if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 3) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath4, 0) != 0)  //��·�����ļ�����ɾ��
				{
					DeleteFile(m_pApi->m_pInterface->pST->OTPCommandPath4);
				}
			}

		}
	}
}

void CMainFrame::FastCalibration_CMD_Ack(int cycle)
{
	int time = 0, t = 0;
	char seps[] = ",";
	char *token;
	BYTE *pByteArray;
	CByteArray arrByte2;
	CString sResult_File = _T(""), sFinal = _T("");
	CFileFind finder;

	if (cycle == 3)
		sFinal = m_pApi->m_pInterface->s_Cycle_3_cali_array;
	 

	int len = WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), NULL, 0, NULL, NULL);
	char *p = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), p, len, NULL, NULL);
	p[len] = '\0';

	//token = strtok((char *)(LPCTSTR)sFinal, seps);
	token = strtok(p, seps);
	while (token != NULL)
	{
		token = strtok(NULL, seps);
		time++;
	}
	delete[]p;

	m_pApi->m_pInterface->dis_Raw_Cs = new CString[time];	
	 

	int len2 = WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), NULL, 0, NULL, NULL);
	char *p2 = new char[len2 + 1];
	WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), p2, len2, NULL, NULL);
	p2[len] = '\0';


	token = strtok(p2, seps);
	while (t < time  && token != NULL)
	{
		/*
		use z�S
		Cycle_3 =  60,  30,       3,             90
		��IQC  ��Cali  ��Non-linear   ����ԭ�c
		*/
		
		m_pApi->m_pInterface->dis_Raw_Cs[t] = token;
		token = strtok(NULL, seps);
	
		t++;
	}
	m_pApi->m_pInterface->raw_profile_num = time;
	delete[] p2;
}

void swap(CString *xp, CString *yp)
{
	CString temp = *xp;
	*xp = *yp;
	*yp = temp;
}

CString SelectSort_distance(CString* sSlider_Array, int direct_number, int n_size)
{
	CString sreult = _T("");
	int i, j, min_max_idx;
	
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n_size - 1; i++) {		 
		// Find the "Min" element in unsorted array
		min_max_idx = i;
		for (j = i + 1; j < n_size; j++){			
			if (direct_number == 1){	
				//���x��С����
				if (_wtoi(sSlider_Array[j]) < _wtoi(sSlider_Array[min_max_idx]))
					min_max_idx = j;
			}				
			else if (direct_number == 2){
				//���x�ɴ�С
				if (_wtoi(sSlider_Array[j]) > _wtoi(sSlider_Array[min_max_idx]))
					min_max_idx = j;
			}			
		}
		swap(&sSlider_Array[min_max_idx], &sSlider_Array[i]);
	}

	//�D�Q���µ��ִ�,�����^��
	for (int h = 0; h < n_size; h++){		
		sreult += sSlider_Array[h];
		if (h < n_size - 1)
			sreult +=L",";
	}

	return sreult;
}


void CMainFrame::CreateFile_forMulitRawDistance(CString sBackUp_Dis_Raw,int cycle)
{
	int time = 0, t = 0 , y = 0 , inc = 0 ,dec = 0;
	char seps[] = ",";
	char *token;	 
	BYTE *pByteArray;
	CByteArray arrByte2;
	CString sResult_File = _T(""), sFinal = _T(""), sFinal2 = _T("");
	CFileFind finder;
	CString sPro_Num;
	CString *sProfile, *sCmdSort;

	if (cycle == 1)
		sFinal = m_pApi->m_pInterface->s_Cycle_1_array;
	else if (cycle == 2)
		sFinal = m_pApi->m_pInterface->s_Cycle_2_array;
	  
	int len = WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), NULL, 0, NULL, NULL);
	char *p = new char[len + 1];
	char *p2 = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), p, len, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, sFinal, sFinal.GetLength(), p2, len, NULL, NULL);
	p2[len] = p[len] = '\0';

	 
	//token = strtok((char *)(LPCTSTR)sFinal, seps);
	token = strtok(p, seps);
	while ( token != NULL)
	{		
		token = strtok(NULL, seps);
		time++;
	}
	delete[]p;
	m_pApi->m_pInterface->dis_Raw_Cs = new CString[time];	
	m_pApi->m_pInterface->ALL_Dis_Raw_File = new CString[time];
	m_pApi->m_pInterface->dis_Raw_FN = new CString[time];
	sProfile = new CString[time];
	sCmdSort = new CString[time];


	token = strtok(p2, seps);
	//�����ƶ���Ѕ���
	while (token != NULL && y < time)
	{
		sCmdSort[y] = (CString)token;
		token = strtok(NULL, seps);		
		y++;
	}

	delete[]p2;
			
	//������������������շ����С���Д���h��2021.04.19
	sFinal2 = SelectSort_distance(sCmdSort, _mulit_status, time);

	if (cycle == 1)//�_��1 (40cm ~ 170cm) // 40cm,60cm,80cm,100cm,120cm,140cm,170cm
	{		
		for (int t = 0; t < time; t++)
		{			
			if (_mulit_status == 1) //�ɽ����h
			{	
				if (t < time - 2) 
					sPro_Num.Format(L"%d", 40 + 20 * t);
				else{					
					sPro_Num.Format(L"%d", 140 + 30 * inc);
					inc++;
				}					
			}
			else if (_mulit_status == 2) //���h����
			{			
				if (t < 2)
					sPro_Num.Format(L"%d", 170 - 30 * t);
				else{
					sPro_Num.Format(L"%d", 120 + 20 * dec);
					dec--;
				}
			}
				
			//�����Y�ϊA���Q
			if (_wtoi(sPro_Num) >= 100)
				sProfile[t] = sPro_Num;
			else
				sProfile[t] = L"0" + sPro_Num;
		}
	}
	else if (cycle == 2)
	{
		for (int t = 0; t < time; t++)
		{
			if (_mulit_status == 1)
				sPro_Num.Format(L"%d", 140 + 30 * t);
			else if (_mulit_status == 2)
				sPro_Num.Format(L"%d", 170 - 30 * t);

			if (_wtoi(sPro_Num) >= 100)
				sProfile[t] = sPro_Num;
			else
				sProfile[t] = L"0" + sPro_Num;
		}
	}

	int len3 = WideCharToMultiByte(CP_ACP, 0, sFinal2, sFinal2.GetLength(), NULL, 0, NULL, NULL);
	char *p3 = new char[len3 + 1];
	WideCharToMultiByte(CP_ACP, 0, sFinal2, sFinal2.GetLength(), p3, len3, NULL, NULL);
	p3[len] = '\0';


	token = strtok(p3, seps);
	while (t < time  && token != NULL)
	{
		CString sfull = _T(""), stemp = _T("");		
		stemp = m_pApi->m_pInterface->dis_Raw_Cs[t] = token;
		token = strtok(NULL, seps);
		/*
		Cycle_1 = 40cm ~ 120cm (5��)
		Cycle_2 = 140cm ~ 170cm (2��)
		*/
#if 0
		//���������x�Y�ϊA
		if (stemp == L"17" || stemp == L"15")
			stemp = L"120";
		else if (stemp == L"37" || stemp == L"35")
			stemp = L"100";
		else if (stemp == L"57" || stemp == L"55")
			stemp = L"080";
		else if (stemp == L"77" || stemp == L"75")
			stemp = L"060";
		else if (stemp == L"97" || stemp == L"95")
			stemp = L"040";
		else if (stemp == L"0")
			stemp = L"170";
		else if (stemp == L"30")
			stemp = L"140";
#else
		/*�_ʼ */
		
		if (_wtoi(stemp) >= 0)
			stemp = sProfile[t];
		else{			
			AddLog(L"ݔ��ָ������e�` ,Ո�_�JCycle �ִ�" + stemp, COLOR_RED);
			return;		
		}
		/*�Y�� */
		 
#endif
		sfull = sBackUp_Dis_Raw + L"\\" + stemp;

		if (PathIsDirectory(sfull) == FALSE)
			CreateDirectory(sfull, NULL);

		if (finder.FindFile(sfull)){
			m_pApi->m_pInterface->RecursiveDelete(sfull);
			m_pApi->m_pInterface->ALL_Dis_Raw_File[t] = sfull;
			m_pApi->m_pInterface->dis_Raw_FN[t] = stemp;
		}
			
		/*stemp = stemp.Left(3);		
		m_pApi->m_pInterface->ALL_Dis_Raw_File[t] = stemp;*/
		t++;
	}
	m_pApi->m_pInterface->raw_profile_num = time;
	delete[] p3;
}

void CMainFrame::SetButtonFont(void)
{
	CFont *f;
	f = new CFont;
	f->CreateFont(35, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("lpszFac")); // lpszFac lpszFac

	m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFont(f);
	//ָ��й¶
}
void CMainFrame::DoTest(void)
{

	m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"������...");
	//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(200, 200, 0));
	//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(560);

	if (m_pApi->DoTestItem())
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"�������");
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(200, 200, 0));
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(330);
	}
	else
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"�������");
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(200, 200, 0));
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(330);
	}
	
}

int CMainFrame::MuaualTestThead()
{
	while (bManualTestFlag)
	{
		if (m_bIsManualTest)
		{

			bIsProcess = TRUE;
			m_bIsManualTest = FALSE;
			DoTest();
			bIsProcess = FALSE;
			//������Ϸ���ָ���PLC���Ʒ�����
			if (m_pApi->m_pInterface->pST->bPLCAutoFlag)
			{
				m_pApi->m_pInterface->pST->SendCommandTestPLC();
			}
			if (m_pApi->m_pInterface->pST->bBarcodeMode)
			{
				Sleep(1000);
				OnTimer(4);
			}
		}
		else if ((m_IsFocus == TRUE) && (m_bIsPlay == TRUE))
		{
			if (!m_pApi->m_pInterface->CameraIsPlay())
			{
				m_IsFocus = FALSE;
				//m_pApi->m_pInterface->CloseCamera();
				SetDisplayCtrlText(L"");
				m_bIsPlay = FALSE;
				continue;
			}

			m_pApi->m_pInterface->pST->SelectItem_FocusMTF();

		}
		Sleep(400);
	}

	SetEvent(m_hManualTest);
	return 1;
}

UINT CMainFrame::MuaualTestThead(LPVOID lpPara)
{
	return ((CMainFrame*)(lpPara))->MuaualTestThead();
}

UINT CMainFrame::AutoTestThead(LPVOID lpPara)
{
	return ((CMainFrame*)(lpPara))->AutoTestThead();
}

int CMainFrame::AutoTestThead()
{
	while (bAutoTestFlag)
	{
		//ɨ��һ������
		if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 0) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
		{
			if (m_pApi->m_pInterface->pST->CompareFileString(m_pApi->m_pInterface->pST->OTPCommandPath1, L"start"))
			{
				Sleep(100);
				StartFlowTest();
			}
			
		}
		if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 2) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
		{
			if (m_pApi->m_pInterface->pST->CompareFileString(m_pApi->m_pInterface->pST->OTPCommandPath1, L"start"))
			{
				Sleep(100);
				StartFlowTest();
			}

		}
		if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 3) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
		{
			if (m_pApi->m_pInterface->pST->CompareFileString(m_pApi->m_pInterface->pST->OTPCommandPath1, L"start"))
			{
				Sleep(100);
				StartFlowTest();
			}

		}
		if (m_pApi->m_pInterface->pST->m_SocketPLCCommand==L"START")
		{
			CString str;
			str.Format(L"%d��λ ", m_pApi->m_pInterface->pST->DisplayID);

			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(str + L"��ʼִ�в���", COLOR_BROWN,200);
			m_pApi->m_pInterface->pST->m_SocketPLCCommand = L"";
			Sleep(1000);
			StartFlowTest();
		}
		Sleep(500);
	}
	SetEvent(m_hAutoTestFlag);
	return 1;
}
void CMainFrame::LoadTestItem(void)
{
	CString strTemp;
	for (UINT i = 0; i < m_pApi->m_ProjectRun.size(); i++)
	{
		strTemp.Format(L"%d", i);
		m_wndTestItem.m_TestItemDlg.m_hWndTestItem.InsertItem(i, strTemp);
		m_wndTestItem.m_TestItemDlg.m_hWndTestItem.SetItemText(i, 1,m_pApi->m_ProjectRun.at(i).Instance->m_ProjectName);
	}
}


void CMainFrame::SetTestItemTime(WPARAM wParam)
{
	TextInfo* textInfo = (TextInfo*)wParam;
	m_wndTestItem.m_TestItemDlg.m_hWndTestItem.SetItemText(textInfo->item, 2, textInfo->text);
	m_wndTestItem.m_TestItemDlg.m_hWndTestItem.EnsureVisible(textInfo->item, false);
	m_wndTestItem.m_TestItemDlg.m_hWndTestItem.SetItemState(textInfo->item, LVIS_SELECTED, LVIS_SELECTED);
}


void CMainFrame::DeleteTestItem(void)
{
	m_wndTestItem.m_TestItemDlg.m_hWndTestItem.DeleteAllItems();
}

void CMainFrame::ClickTestBtn(UINT uID)
{
	if (m_bIsPlay)
	{
		AddLog(L"������Ч,ͼ���Ѿ�����,ֹͣ������", COLOR_RED);
		return;
	}

	if (m_bIsTest)
	{
		AddLog(L"������Ч,�ѿ��������߳�,ֹͣ������", COLOR_RED);
		return;
	}

	if (m_pApi->m_ProjectRun.at(uID).Instance->Initialize() == FALSE)
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L"��ʼ��ʧ��!", COLOR_RED);
	}

	if (m_pApi->m_ProjectRun.at(uID).Instance->Testing() == TestResult::TEST_FAIL)
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L" ����ʧ��", COLOR_RED);
	}
	else
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L" ���Գɹ�");
	}
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if ((pMsg->wParam == 0x0d) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//�ƿ�����
		AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, 0, MyMessage::FlowTEST);
		//AfxMessageBox(L"123");
		return TRUE;
	}

	if (m_pApi->m_pUI->PreTranslateMessage(pMsg))
		return TRUE;

	return CFrameWndEx::PreTranslateMessage(pMsg);
}

void CMainFrame::DisplayText()
{
	if (m_pApi->m_pInterface->CameraIsPlay())
	{
		CString str;
		CString strSlaveid;
		strSlaveid.Format(L"_0x%02x", m_pApi->m_pInterface->GetSensor()->SlaveID[0]);
		str = m_pApi->m_pInterface->GetSensor()->SensorName + strSlaveid;
		m_wndStatusBar.SetPaneText(1, str, TRUE);
		str.Format(L"�ɼ�֡��:%4.1f fps", m_pApi->m_pInterface->GetDisplaySensorFps());
		m_wndStatusBar.SetPaneText(2, str, TRUE);
		str.Format(L"��ʾ֡��:%4.1f fps", m_pApi->m_pInterface->GetDisplaySensorFps());
		m_wndStatusBar.SetPaneText(3, str, TRUE);
// 		str.Format(L"����֡:%d fps", m_pApi->m_pInterface->GetErrorFps());
// 		m_wndStatusBar.SetPaneText(4, str, TRUE);
		str.Format(L"�ֱ���:%dx%d", m_pApi->m_pInterface->GetSensor()->width, m_pApi->m_pInterface->GetSensor()->height);
		m_wndStatusBar.SetPaneText(4, str, TRUE);
	}
}

void CMainFrame::CleanText()
{
	for (int i = 2; i < 10; i++)
	{
		m_wndStatusBar.SetPaneText(i, L"", TRUE);
	}
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nIDEvent)
	{
	case  1:
		DisplayText();

		break;
	case  2:
		if (m_pApi->m_pInterface->SocketInit())
		{
			OnClick(IDC_START);
		}
		KillTimer(2);
		SetTimer(3, 3000, NULL);
		break;
	case 3:
		KillTimer(3);
		WriteLog();
		SetTimer(3, 3000, NULL);
		break;
	case 4:
		KillTimer(4);
		
		pDlg.DoModal();
	}

	CFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::OnCalcWindow()
{
	// TODO:  �ڴ���������������
	CRect mainDlg;
	CRect bottomDlg;
	CRect RightDlg;
	GetWindowRect(mainDlg);//�������������Ļ�ϵ�λ��
	m_wndOutput.GetClientRect(bottomDlg);
	m_wndTestItem.GetClientRect(RightDlg);


	CString strDlg;
	strDlg.Format(L"������:X=%d,Y=%d,��=%d,��=%d\n�ײ�����:��=%d,��=%d\n�Ҳ�����:��=%d,��=%d",
		mainDlg.left, mainDlg.top, mainDlg.Width(), mainDlg.Height(),
		bottomDlg.Width(), bottomDlg.Height(),
		RightDlg.Width(), RightDlg.Height());

	MessageBox(strDlg);



}


void CMainFrame::OnSaveWindow()
{
	// TODO:  �ڴ���������������
	CString str;
	CRect rect;

	WritePrivateProfileString(STR_Main, STR_CleanWindowState, L"1", CFG::GetConfigPath());

	GetWindowRect(rect);//�������������Ļ�ϵ�λ��

	str.Format(L"%d", rect.left);
	WritePrivateProfileString(STR_Main, STR_WindowX, str, CFG::GetConfigPath());
	str.Format(L"%d", rect.top);
	WritePrivateProfileString(STR_Main, STR_WindowY, str, CFG::GetConfigPath());
	str.Format(L"%d", rect.Width());
	WritePrivateProfileString(STR_Main, STR_WindowW, str, CFG::GetConfigPath());
	str.Format(L"%d", rect.Height());
	WritePrivateProfileString(STR_Main, STR_WindowH, str, CFG::GetConfigPath());


	m_wndOutput.GetClientRect(rect);
	str.Format(L"%d", rect.Width());
	WritePrivateProfileString(STR_Main, STR_WindowWB, str, CFG::GetConfigPath());
	str.Format(L"%d", rect.Height());
	WritePrivateProfileString(STR_Main, STR_WindowHB, str, CFG::GetConfigPath());

	m_wndTestItem.GetClientRect(rect);
	str.Format(L"%d", rect.Width());
	WritePrivateProfileString(STR_Main, STR_WindowWR, str, CFG::GetConfigPath());
	str.Format(L"%d", rect.Height());
	WritePrivateProfileString(STR_Main, STR_WindowHR, str, CFG::GetConfigPath());


	MessageBox(L"���洰��λ�óɹ�");

}




void CMainFrame::OnWindowLog()
{
	// TODO:  �ڴ���������������
	if (::IsWindowVisible(m_wndOutput.m_hWnd))
	{
		m_bDlgLogShow = FALSE;
		m_wndOutput.ShowPane(FALSE, FALSE, FALSE);
		SendMessage(WM_SIZE, 0, 0);
	}
	else
	{
		m_bDlgLogShow = TRUE;
		m_wndOutput.ShowPane(TRUE, TRUE, FALSE);
		SendMessage(WM_SIZE, 0, 0);
	}
}


void CMainFrame::OnUpdateWindowLog(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_bDlgLogShow);
}


void CMainFrame::OnWindowTestItem()
{
	// TODO:  �ڴ���������������
	if (::IsWindowVisible(m_wndTestItem.m_hWnd))
	{
		m_bDlgTestItemShow = FALSE;
		m_wndTestItem.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_bDlgTestItemShow = TRUE;
		m_wndTestItem.ShowPane(TRUE, TRUE, FALSE);
		SendMessage(WM_SIZE, 0, 0);
	}
}


void CMainFrame::OnUpdateWindowTestItem(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_bDlgTestItemShow);
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFrameWndEx::OnPaint()
	if (::IsWindowVisible(m_wndOutput.m_hWnd))
	{
		m_bDlgLogShow = TRUE;
	}
	else
	{
		m_bDlgLogShow = FALSE;
	}

	if (::IsWindowVisible(m_wndTestItem.m_hWnd))
	{
		m_bDlgTestItemShow = TRUE;
	}
	else
	{
		m_bDlgTestItemShow = FALSE;
	}
}


CString CMainFrame::CreateFileName()
{
	COleDateTime t = COleDateTime::GetCurrentTime();
	CString str;
	CString strTmp;
	str.Format(L"%d_%d_%d", t.GetYear(), t.GetMonth(), t.GetDay());
	CString strPath = m_pApi->m_pInterface->GetConfig()->ReportPath + L"\\";

	if (m_pApi->m_pInterface->GetConfig()->PorjectName == L"")
	{
		CString str2;
		str2 = m_pApi->m_pInterface->GetSensor()->SensorName;
		strPath += str2 + L"\\";
	}
	else
	{
		strPath += m_pApi->m_pInterface->GetConfig()->PorjectName + L"\\Log\\";
	}

	if (PathIsDirectory(strPath) == FALSE)
	{
		int index, start = 0;
		while ((index = strPath.Find('\\', start)) != -1)
		{
			strTmp = strPath.Left(index);
			CreateDirectory(strTmp, NULL);
			start = index + 1;
		}
		if (strPath.GetLength() != strTmp.GetLength() + 1)
			CreateDirectory(strPath, NULL);
		::CreateDirectory(strPath, NULL);
	}
	strTmp.Format(L"_%d.txt", m_pApi->m_pInterface->GetAppInfo()->AppNum + 1);
	strPath += str + strTmp;
	return strPath;
}


void CMainFrame::WriteLog()
{
	setlocale(LC_CTYPE, "chs");
	COleDateTime t = COleDateTime::GetCurrentTime();
	CStdioFile file;
	CString fileName = CreateFileName();
	if (PathFileExists(fileName) == FALSE)
	{
		if (file.Open((LPCTSTR)(fileName), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
		{
			file.Close();
		}
		else
		{
			AddLog(L"�����ļ�ʧ�� " + fileName, COLOR_RED);
			return;
		}

	}

	if (file.Open(fileName, CFile::modeNoTruncate | CFile::modeWrite))
	{
		file.SeekToEnd();
	}
	else
	{
		AddLog(L"���ļ�ʧ�� " + fileName, COLOR_RED);
		AddLog(L"Here Error.. ", COLOR_RED);
		return;
	}


	int nLineLength, nLineIndex, nLineCount = m_wndOutput.m_wndOutputLog.GetLineCount();
	CString strText, strLine;

	
	if (nLineCount <= 1)return;
	if (nLineCount == m_LogLenght)return;
	int j = 0;
	// Dump every line of text of the rich edit control.
	for (int i = m_LogLenght; i < nLineCount -1; i++)
	{
		nLineIndex = m_wndOutput.m_wndOutputLog.LineIndex(i);
		if (nLineIndex < 0)return;
		nLineLength = m_wndOutput.m_wndOutputLog.LineLength(nLineIndex);
		m_wndOutput.m_wndOutputLog.GetLine(i, strText.GetBufferSetLength(nLineLength + 1), nLineLength);
		strText.SetAt(nLineLength, _T('\0')); // null terminate
		strText.ReleaseBuffer(nLineLength + 1);
		file.WriteString(strText);
		file.WriteString(L"\n");
		j++;
		
	}

	m_LogLenght += j;
	file.Close();


	//m_wndOutput.m_wndOutputLog.SetWindowText(L"");

}

void CMainFrame::OnSavePic()
{
	// TODO:  �ڴ���������������
	m_pApi->m_pInterface->SavePic();
}

/*void CMainFrame::OnTestPic()
{
// TODO:  �ڴ���������������

CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp�ļ�(*.bmp)|*bmp||"));

if (fileDlg.DoModal() == IDOK)
{
BITMAPINFO *pBmpInfo;
BYTE * pBmpData;
BITMAPFILEHEADER bmpHeader;
BITMAPINFOHEADER bmpInfo;
CFile bmpFile;
if (!bmpFile.Open(fileDlg.GetPathName(), CFile::modeRead | CFile::typeBinary))
{
AfxMessageBox(L"��ʧ��");
}

if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
AfxMessageBox(L"��ȡbmpHeader");
if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
AfxMessageBox(L"��ȡbmpInfo");

pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
pBmpData = (BYTE*)new char[dataBytes];
bmpFile.Read(pBmpData, dataBytes);
bmpFile.Close();

}


}*/

void CMainFrame::OnPlayCam()
{
	// TODO:  �ڴ���������������
	OnClick(ID_PLAY_CAM);
}
void CMainFrame::OnEngMode()
{
	// TODO:  �ڴ���������������
	CManage pDlg;
	
	if (pDlg.DoModal()==IDOK)
	{
		if (pDlg.strPassword != pDlg.strPasswordCheck)
		{
			m_pApi->m_pInterface->AddLog(L"�������..", COLOR_RED);
			return;
		}
		
	}
	else
	{
		m_pApi->m_pInterface->AddLog(L"��ȡ���Ի���...",COLOR_BROWN);
		return;
	}

	m_bIsEngMode = m_pApi->m_pInterface->ReadConfigInt(L"Main", L"bIsEngMode", 0);
	if (m_bIsEngMode)
	{
		m_bIsEngMode = FALSE;
		m_pApi->m_pInterface->WriteConfigInt(L"Main", L"bIsEngMode", 0);
		m_pApi->m_pInterface->AddLog(L"������Ŀ������", COLOR_BROWN);
	}
	else
	{
		m_bIsEngMode = TRUE;
		m_pApi->m_pInterface->WriteConfigInt(L"Main", L"bIsEngMode", 1);
		m_pApi->m_pInterface->AddLog(L"������Ŀ�ѽ���", COLOR_BROWN);
	}

}
void CMainFrame::OnEnableGenMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
	if (m_bIsEngMode)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	//CleanText();
}
void CMainFrame::OnEnableItemMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
	if (m_bIsEngMode)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	//CleanText();
}
void CMainFrame::OnEnableOTPMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
	if (m_bIsEngMode)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	//CleanText();
}
void CMainFrame::OnEnableSenMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
	if (m_bIsEngMode)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	CleanText();
}
void CMainFrame::OnEnablePOGMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
	if (m_bIsEngMode)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	//CleanText();
}
void CMainFrame::OnEnableTestMenu(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ���������������
// 	if (m_pApi->m_pInterface->pST->ManualTest)
// 	{
// 		pCmdUI->Enable(true);
// 
// 	}

	//CleanText();
	
}
void CMainFrame::OnUpdateEngMode(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	if (m_bIsEngMode)
	{
		pCmdUI->SetText(L"����ģʽ");
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"����ģʽ");
		pCmdUI->SetCheck(TRUE);
	}
	CleanText();
}
void CMainFrame::OnUpdatePlayCam(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������

}


void CMainFrame::OnCheck3000k()
{
	// TODO:  �ڴ���������������
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource3000();
}


void CMainFrame::OnCheck4000k()
{
	// TODO:  �ڴ���������������
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource4000();
}


void CMainFrame::OnCheck5100k()
{
	// TODO:  �ڴ���������������
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource5100();
}


void CMainFrame::OnCheckMtf()
{
	// TODO:  �ڴ���������������
	m_pApi->m_pInterface->pST->CheckMTF();
}


void CMainFrame::OnUpdateBlemish(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	if (m_pApi->m_pInterface->bIsBlemish)
	{
		pCmdUI->SetText(L"�ر�����ģʽ");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"��������ģʽ");
	}
}


void CMainFrame::OnBlemish()
{
	// TODO:  �ڴ���������������
	if (m_pApi->m_pInterface->bIsBlemish)
	{
		m_pApi->m_pInterface->bIsBlemish = FALSE;
	}
	else
	{
		m_pApi->m_pInterface->bIsBlemish = TRUE;
	}
}


void CMainFrame::OnCommondCross()
{
	// TODO:  �ڴ���������������
	if (m_pApi->m_pInterface->m_bCross)
	{
		m_pApi->m_pInterface->m_bCross = FALSE;
	}
	else
	{
		m_pApi->m_pInterface->m_bCross = TRUE;
	}
}


void CMainFrame::OnUpdateCross(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	if (m_pApi->m_pInterface->m_bCross)
	{
		pCmdUI->SetText(L"�ر�����ʮ��");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"��������ʮ��");
	}
}


void CMainFrame::OnAwb()
{
	// TODO:  �ڴ���������������
	if (m_pApi->m_pInterface->m_AWBEN2)
	{
		m_pApi->m_pInterface->m_AWBEN2 = FALSE;
	}
	else
	{
		m_pApi->m_pInterface->m_AWBEN2 = TRUE;
		m_pApi->m_pInterface->m_AWBEN1 = TRUE;
	}
}


void CMainFrame::OnUpdateAwb(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	if (m_pApi->m_pInterface->m_AWBEN2)
	{
		pCmdUI->SetText(L"�رհ�ƽ��");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"������ƽ��");
	}
}


void CMainFrame::OnBnClickedTestInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(L"123");
}
