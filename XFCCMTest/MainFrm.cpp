
// MainFrm.cpp : CMainFrame 类的实现
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
#pragma comment(lib,"Shlwapi.lib") //如果没有这行，会出现link错误

TCHAR section[1024];
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_LOAD, &CMainFrame::OnLoad)
	ON_COMMAND_RANGE(IDC_START, IDC_START + 100, OnClick)  //注册自定义命令
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

// CMainFrame 构造/析构

static UINT indicators[] =
{
	//  	ID_SEPARATOR,           // 状态行指示器
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
	// TODO:  在此添加成员初始化代码
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
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndMenuBar.EnableCustomizeButton(TRUE, -1, _T(""));
	//m_wndMenuBar.EnableHelpCombobox(1, _T(""), 80);
	//m_wndMenuBar.EnableMenuShadows();




	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
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


	// TODO:  如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
	CDockingManager::SetDockingMode(DT_SMART);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
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

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndTestItem.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTestItem);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);


	// 启用快速(按住 Alt 拖动)工具栏自定义
//	CMFCToolBar::EnableQuickCustomization();
	//m_bIsEngMode = TRUE;//设置量产模式
	int offset = 250;
	m_bIsTest = FALSE;
	m_bIsPlay = FALSE;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP;
	CWnd *pWnd = CWnd::FromHandle(m_wndMenuBar.m_hWnd);
	m_btnPlay.Create(_T("调焦"), dwStyle, CRect(offset, 0, offset + 40, 20), pWnd, IDC_START);
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
	
	m_pApi = XFApiCreate(appInfo);//创建设备

	CString strTemp;
	strTemp.Format(L"  程序编号(%d)   ", appInfo.AppNum + 1);
	SetWindowText(m_pApi->m_pInterface->pST->SoftVersion + strTemp);

	LoadTestItem();

	CMenu *pMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (pMenu == NULL) return 0;
	CMenu *pPopMenu = pMenu->GetSubMenu(2);
	pPopMenu->RemoveMenu(0, MF_BYPOSITION);

	CStringArray *pDlgName = m_pApi->m_pUI->GetDlgName();
	for (int i = 0; i < pDlgName->GetSize(); i++)
	{
		pPopMenu->AppendMenu(MF_POPUP, IDC_DLG + i, pDlgName->GetAt(i)); // 添加DLG菜单
	}
	m_bIsEngMode = m_pApi->m_pInterface->ReadConfigInt(L"Main", L"bIsEngMode", 0);
	//初始化线程句柄
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
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"点击测试");
		//由于测试时候界面卡死，创建测试线程
		bIsProcess = FALSE;
		bManualTestFlag = TRUE;
		m_bIsManualTest = FALSE;
		m_hManualTest = CreateEvent(NULL, TRUE, FALSE, NULL);
		AfxBeginThread(MuaualTestThead, this);

		//扫描文档线程
		m_hAutoTestFlag = CreateEvent(NULL, TRUE, FALSE, NULL);
		AfxBeginThread(AutoTestThead, this);
		bAutoTestFlag = TRUE;
		SetTimer(3, 3000, NULL);

	}

	m_pApi->m_pInterface->pST->bIsBlemish = FALSE;//初始化脏污flag
	m_pApi->m_pInterface->m_bCross = FALSE;//初始化中心十字架
	m_pApi->m_pInterface->m_AWBEN1 = FALSE;//初始化中心十字架
	m_pApi->m_pInterface->m_AWBEN1 = FALSE;//初始化中心十字架
	m_LogLenght = 0;

	m_Run_Usc_Count = 1;

	//取得RAW存圖設定
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

	//取得RAW測試距離腳本
	Run_Raw_dis_Script  = m_pApi->m_pInterface->ReadConfigInt(L"Raw_Distance", L"m_Run_distance", 0);
	m_pApi->m_pInterface->Raw_dis_test = Run_Raw_dis_Script;

	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	// 创建输出窗口

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

	if (!m_wndOutput.Create(L"输出", this, CRect(0, 0, w, h), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
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

	if (!m_wndTestItem.Create(L"测试项目", this, CRect(0, 0, w, h), TRUE, 10010, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建测试信息\n");
		return FALSE; // 未能创建
	}
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->Create();
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


BOOL CMainFrame::DestroyWindow()
{
	// TODO:  在此添加专用代码和/或调用基类

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
	// TODO:  在此添加命令处理程序代码

	Stop();
	CFileDialog fileDlg(TRUE, L"xf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"xf文件(*.xf)|*xf|ini文件(*.ini)|*.ini||");

	if (fileDlg.DoModal() == IDOK)
	{
		if (m_pApi->m_pInterface->LoadSensorConfig(fileDlg.GetPathName()) == FALSE)
		{
			AddLog(L"ERROR:加载Sensor配置文件失败", COLOR_RED);
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
			AddLog(fileDlg.GetPathName() + L" 已加载");
		}

	}

}


void CMainFrame::OnShowConfigDlg()
{
	// TODO:  在此添加命令处理程序代码
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
	m_btnPlay.SetWindowText(L"开始");

	for (UINT i = 0; i < m_pApi->m_ProjectRun.size(); i++)
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestItem.SetItemText(i, 2, L"");
	}
	CleanText();

}

void CMainFrame::OnClick(UINT uID)  //按钮命令 5000-5050,菜单命令 5050-5100
{
	CString str;
	if (uID >= IDC_DLG) //菜单栏事件
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

	switch (uID)   //按钮事件
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
			//m_pApi->m_pInterface->SwitchSensorTable(0);//切换第一个摄像头
			if (m_pApi->m_pInterface->OpenCamera())
			{
				m_bIsPlay = TRUE;
				SetDisplayCtrlText(L"");
				m_pApi->m_pInterface->PlayVideo();
				m_pApi->m_pInterface->StartPreview();
				SetTimer(1, 0, NULL);  //帧率计时器
			}
		}



		break;
	case IDC_START:
		if (m_pApi->m_pInterface->GetSensor() == NULL)
		{
			SetDisplayCtrlText(L"芯片配置文件加载失败!!!", COLOR_RED);
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
				AddLog(L"未添加任何测试项目,请添加测试项目", COLOR_RED);
				m_pApi->m_pInterface->CloseCamera();
				break;
			}
			else
			{
				m_pApi->m_pInterface->PlayVideo();

				//setVCM
				m_pApi->m_pInterface->pST->SetVCMStep(0);
				SetTimer(1, 1000, NULL);  //帧率计时器
				SetDisplayCtrlText(L"");
				// 				bool mExp = m_pApi->m_pInterface->ExposureEx(130, 5, 0, NULL, EXP_Y, m_pApi->m_pInterface->GetSensor()->width / 2, m_pApi->m_pInterface->GetSensor()->height / 2, 10, 3);
				// 				if (!mExp)
				// 				{
				// 					AddLog(L"AE曝光NG", COLOR_RED);
				// 					m_btnPlay.SetWindowText(L"调焦");
				// 					m_bIsPlay = TRUE;
				// 					m_IsFocus = FALSE;
				// 					SetDisplayCtrlText(L"");
				// 					break;
				// 				}
				m_btnPlay.SetWindowText(L"停止");
				m_bIsPlay = TRUE;
				m_IsFocus = TRUE;
				AddLog(L"调焦");
			}
		}
		else
		{
			//m_pApi->m_pInterface->StopPreview();
			m_pApi->m_pInterface->CloseCamera();
			AddLog(L"停止图像", COLOR_BROWN);
			m_btnPlay.SetWindowText(L"调焦");
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
		AddLog(L"当前测试项目未支持配置", COLOR_RED);
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
		AfxMessageBox(L"当前测试项目未添加窗口");
	}
}


LRESULT CMainFrame::MyMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class 
	
	switch (lParam)
	{
	case MyMessage::PLAY_VIDEO:                //播放  
		OnClick(ID_PLAY_CAM);	
		break;
	case MyMessage::STOP_VIDEO:                //停止
		OnClick(ID_PLAY_CAM);
		break;
	case MyMessage::ADDLOG:                    //添加LOG输出信息
		AddLog(wParam);
		break;
	case MyMessage::SET_DISPLAYCTRL_TEXT:      //设置CChildView类中显示控件的字符和颜色
		SetDisplayCtrlText(wParam);
		break;
	case MyMessage::LOAD_ITEM:                 //依据测试项目个数加载测试项目
		DeleteTestItem();                      //加载测试项目前,清空已经已加载的测试项目
		m_pApi->InitPlugins();                 //重新初始化测试项目数组
		LoadTestItem();
		break;
	case MyMessage::DBCLICK_TEST:               //响应测试项目控件双击事件
		ClickTestBtn(*(UINT*)wParam);
		break;
	case MyMessage::CREATE_TEST_THREAD:         //创建测试项目线程
		m_pApi->StartTestThread();
		break;
	case MyMessage::SET_TEST_ITEM_TIME:         //测试项目完成时间
		SetTestItemTime(wParam);
		break;
	case MyMessage::SHOW_TEST_ITEM_DLG:         //显示测试项目对话框
		ShowTestItemDlg(*(UINT*)wParam);
		break;
	case MyMessage::FlowTEST:         //显示测试项目对话框
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
				pos_read = file.GetPosition();//记录读到了哪一行;
				
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
		AddLog(L"已更新校正條碼->" + strBarcode, COLOR_RED);
	}else{
		AddLog(L"讀檔 Calib_release TestData inFo.txt", COLOR_RED);
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
	/*****手动扫码20190307*****/
	//一键测试与扫码不能同时测试

	if (m_pApi->m_pInterface->pST->bBarcodeMode == 1)
	{
		m_pApi->m_pInterface->pST->strBarcode = L"";
		pDlg.strBarcode.MakeUpper();
		AddLog(L"二维码扫码完成BarCode: " + pDlg.strBarcode, COLOR_BROWN);
		m_pApi->m_pInterface->pST->strBarcode = pDlg.strBarcode;
		if (pDlg.strBarcode.GetLength() != m_pApi->m_pInterface->pST->m_BCLenght)
		{
			AddLog(L"二维码扫描长度错误,重新扫码... ", COLOR_RED);
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

	

	//紀錄多距離滑軌移動CM
	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_1"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_1_array = section;	
	sCy1 = m_pApi->m_pInterface->s_Cycle_1_array;
	   
	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_2"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_2_array = section;
	sCy2 = m_pApi->m_pInterface->s_Cycle_2_array;

	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_Cali_All"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_3_cali_array = section;
	sCy_Cali = m_pApi->m_pInterface->s_Cycle_3_cali_array;


	//多距離測試方向判定旗標	 
	GetPrivateProfileStringW(L"Mulit_Direction_Status", _T("m_direction_St"), _T(""), section, sizeof(section), str_xini);
	_mulit_status = m_pApi->m_pInterface->Mulit_Ack_Status = _wtoi(section);
	 		 
	//執行EEPROM 收集資料動作次數
	GetPrivateProfileStringW( L"Eeprom_Ack_Mode", _T("m_eeprom_acknum"), _T(""), section, sizeof(section), str_xini);
	_eeprom_ack  = m_pApi->m_pInterface->Eeprom_Ack_Num = _wtoi(section);
		 	 	  

	GetPrivateProfileStringW(STR_RAWMULIT_CMTOANGLE, _T("Cycle_2"), _T(""), section, sizeof(section), str_xini);
	m_pApi->m_pInterface->s_Cycle_2_array = section;
	

	//將條碼內容寫入XFConfig.ini 2021.03.12	
	WritePrivateProfileString(STR_BARCODE_RECORD, STR_BARCODE_PATH, m_pApi->m_pInterface->pST->strBarcode, str_xini);



	//走自動化燒錄
	if (_eeprom_ack == 2){		
		GetPrivateProfileStringW(STR_BARCODE_RECORD, STR_IDENTIFY_BARCODE, _T(""), section, sizeof(section), str_xini);
		m_pApi->m_pInterface->s_Identify_barcode = section;
		
		CString  sIdent = m_pApi->m_pInterface->s_Identify_barcode;
		int idencheck_len = sizeof(sIdent)+1;
		CString  subbarcode = m_pApi->m_pInterface->pST->strBarcode.Left(idencheck_len);   //找尋案名(EX:AT004,BT001)

		//案名比對有誤
		if (sIdent.Compare(subbarcode) == -1 || sIdent.Compare(subbarcode) == 1)
		{			
			AddLog(L"條碼比對NG!,掃錯開頭為:" + subbarcode, COLOR_RED);
			OnTimer(4);
			return;
		}
		else{
			//OK
			AddLog(L"條碼比對OK,開頭案名為:" + subbarcode, COLOR_BLUE);
			ReplaceBarcodeString(m_pApi->m_pInterface->s_Identify_barcode, m_pApi->m_pInterface->pST->strBarcode);
		}				
	}
		
	// 建立條碼資料夾
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

		//建立子條碼資料夾
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


		if (_eeprom_ack == 2) //全自動化流程需要預先清空
		{
			//清空全部BackUp test資料
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
			//儲存 Cycle_Cali_All 一開始設定的移動角度
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

		//建立子條碼資料夾
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
		AddLog(L"产品正在测试...", COLOR_RED);
		return;
	}
	if (m_pApi->m_pInterface->GetSensor() == NULL)
	{
		SetDisplayCtrlText(L"芯片配置文件加载失败!!!", COLOR_RED);
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
			AddLog(L"未添加任何测试项目,请添加测试项目", COLOR_RED);
		}
		else
		{

			m_wndOutput.SetFocus();//移开焦点
			SetTimer(1, 1000, NULL);  //帧率计时器
			SetDisplayCtrlText(L"");
			m_bIsManualTest = TRUE;
			AddLog(L"开始测试");
			//DoTest();

			//生成start文件一键测试
			if((m_pApi->m_pInterface->GetAppInfo()->AppNum == 1) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath1, L"start");
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath3, L"start");
				m_pApi->m_pInterface->pST->WriteCommandIni1(m_pApi->m_pInterface->pST->OTPCommandPath4, L"start");
			}
			if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 0) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath1, 0) != 0)  //该路径有文件则将其删掉
				{
					DeleteFile(m_pApi->m_pInterface->pST->OTPCommandPath1);
				}
			}
			else if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 2) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath3, 0) != 0)  //该路径有文件则将其删掉
				{
					DeleteFile(m_pApi->m_pInterface->pST->OTPCommandPath3);
				}
			}
			else if ((m_pApi->m_pInterface->GetAppInfo()->AppNum == 3) && (m_pApi->m_pInterface->pST->bOneKeyTest == true))
			{
				CFileFind   ff;
				if (ff.FindFile(m_pApi->m_pInterface->pST->OTPCommandPath4, 0) != 0)  //该路径有文件则将其删掉
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
		use z軸
		Cycle_3 =  60,  30,       3,             90
		↑IQC  ↑Cali  ↑Non-linear   ↑回原點
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
				//距離由小到大
				if (_wtoi(sSlider_Array[j]) < _wtoi(sSlider_Array[min_max_idx]))
					min_max_idx = j;
			}				
			else if (direct_number == 2){
				//距離由大到小
				if (_wtoi(sSlider_Array[j]) > _wtoi(sSlider_Array[min_max_idx]))
					min_max_idx = j;
			}			
		}
		swap(&sSlider_Array[min_max_idx], &sSlider_Array[i]);
	}

	//轉換成新的字串,排序過的
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
	//重新制定陣列參數
	while (token != NULL && y < time)
	{
		sCmdSort[y] = (CString)token;
		token = strtok(NULL, seps);		
		y++;
	}

	delete[]p2;
			
	//新增排序將陣列重整依照方向大小，判斷近遠，2021.04.19
	sFinal2 = SelectSort_distance(sCmdSort, _mulit_status, time);

	if (cycle == 1)//腳本1 (40cm ~ 170cm) // 40cm,60cm,80cm,100cm,120cm,140cm,170cm
	{		
		for (int t = 0; t < time; t++)
		{			
			if (_mulit_status == 1) //由近到遠
			{	
				if (t < time - 2) 
					sPro_Num.Format(L"%d", 40 + 20 * t);
				else{					
					sPro_Num.Format(L"%d", 140 + 30 * inc);
					inc++;
				}					
			}
			else if (_mulit_status == 2) //由遠到近
			{			
				if (t < 2)
					sPro_Num.Format(L"%d", 170 - 30 * t);
				else{
					sPro_Num.Format(L"%d", 120 + 20 * dec);
					dec--;
				}
			}
				
			//命名資料夾名稱
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
		Cycle_1 = 40cm ~ 120cm (5段)
		Cycle_2 = 140cm ~ 170cm (2段)
		*/
#if 0
		//建立各距離資料夾
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
		/*開始 */
		
		if (_wtoi(stemp) >= 0)
			stemp = sProfile[t];
		else{			
			AddLog(L"輸入指令數字有錯誤 ,請確認Cycle 字串" + stemp, COLOR_RED);
			return;		
		}
		/*結束 */
		 
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
	//指针泄露
}
void CMainFrame::DoTest(void)
{

	m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"测试中...");
	//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(200, 200, 0));
	//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(560);

	if (m_pApi->DoTestItem())
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"点击测试");
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetBackColor(RGB(200, 200, 0));
		//m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetFontSize(330);
	}
	else
	{
		m_wndTestItem.m_TestItemDlg.m_hWndTestInfo.SetWindowTextW(L"点击测试");
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
			//测试完毕发送指令给PLC控制服务器
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
		//扫描一键测试
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
			str.Format(L"%d号位 ", m_pApi->m_pInterface->pST->DisplayID);

			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(L"*********", COLOR_BROWN, 200);
			AddLog(str + L"开始执行测试", COLOR_BROWN,200);
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
		AddLog(L"操作无效,图像已经播放,停止后重试", COLOR_RED);
		return;
	}

	if (m_bIsTest)
	{
		AddLog(L"操作无效,已开启测试线程,停止后重试", COLOR_RED);
		return;
	}

	if (m_pApi->m_ProjectRun.at(uID).Instance->Initialize() == FALSE)
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L"初始化失败!", COLOR_RED);
	}

	if (m_pApi->m_ProjectRun.at(uID).Instance->Testing() == TestResult::TEST_FAIL)
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L" 测试失败", COLOR_RED);
	}
	else
	{
		AddLog(m_pApi->m_ProjectRun.at(uID).Instance->m_ProjectName + L" 测试成功");
	}
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if ((pMsg->wParam == 0x0d) && (pMsg->message == WM_KEYDOWN))//Enter key
	{//VK_RETURN

		//m_wndOutput.SetFocus();//移开焦点
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
		str.Format(L"采集帧率:%4.1f fps", m_pApi->m_pInterface->GetDisplaySensorFps());
		m_wndStatusBar.SetPaneText(2, str, TRUE);
		str.Format(L"显示帧率:%4.1f fps", m_pApi->m_pInterface->GetDisplaySensorFps());
		m_wndStatusBar.SetPaneText(3, str, TRUE);
// 		str.Format(L"错误帧:%d fps", m_pApi->m_pInterface->GetErrorFps());
// 		m_wndStatusBar.SetPaneText(4, str, TRUE);
		str.Format(L"分辨率:%dx%d", m_pApi->m_pInterface->GetSensor()->width, m_pApi->m_pInterface->GetSensor()->height);
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
	// TODO:  在此添加命令处理程序代码
	CRect mainDlg;
	CRect bottomDlg;
	CRect RightDlg;
	GetWindowRect(mainDlg);//获得主窗体在屏幕上的位置
	m_wndOutput.GetClientRect(bottomDlg);
	m_wndTestItem.GetClientRect(RightDlg);


	CString strDlg;
	strDlg.Format(L"主窗体:X=%d,Y=%d,宽=%d,高=%d\n底部窗体:宽=%d,高=%d\n右部窗体:宽=%d,高=%d",
		mainDlg.left, mainDlg.top, mainDlg.Width(), mainDlg.Height(),
		bottomDlg.Width(), bottomDlg.Height(),
		RightDlg.Width(), RightDlg.Height());

	MessageBox(strDlg);



}


void CMainFrame::OnSaveWindow()
{
	// TODO:  在此添加命令处理程序代码
	CString str;
	CRect rect;

	WritePrivateProfileString(STR_Main, STR_CleanWindowState, L"1", CFG::GetConfigPath());

	GetWindowRect(rect);//获得主窗体在屏幕上的位置

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


	MessageBox(L"保存窗口位置成功");

}




void CMainFrame::OnWindowLog()
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bDlgLogShow);
}


void CMainFrame::OnWindowTestItem()
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bDlgTestItemShow);
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CFrameWndEx::OnPaint()
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
			AddLog(L"创建文件失败 " + fileName, COLOR_RED);
			return;
		}

	}

	if (file.Open(fileName, CFile::modeNoTruncate | CFile::modeWrite))
	{
		file.SeekToEnd();
	}
	else
	{
		AddLog(L"打开文件失败 " + fileName, COLOR_RED);
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
	// TODO:  在此添加命令处理程序代码
	m_pApi->m_pInterface->SavePic();
}

/*void CMainFrame::OnTestPic()
{
// TODO:  在此添加命令处理程序代码

CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp文件(*.bmp)|*bmp||"));

if (fileDlg.DoModal() == IDOK)
{
BITMAPINFO *pBmpInfo;
BYTE * pBmpData;
BITMAPFILEHEADER bmpHeader;
BITMAPINFOHEADER bmpInfo;
CFile bmpFile;
if (!bmpFile.Open(fileDlg.GetPathName(), CFile::modeRead | CFile::typeBinary))
{
AfxMessageBox(L"打开失败");
}

if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
AfxMessageBox(L"读取bmpHeader");
if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
AfxMessageBox(L"读取bmpInfo");

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
	// TODO:  在此添加命令处理程序代码
	OnClick(ID_PLAY_CAM);
}
void CMainFrame::OnEngMode()
{
	// TODO:  在此添加命令处理程序代码
	CManage pDlg;
	
	if (pDlg.DoModal()==IDOK)
	{
		if (pDlg.strPassword != pDlg.strPasswordCheck)
		{
			m_pApi->m_pInterface->AddLog(L"密码错误..", COLOR_RED);
			return;
		}
		
	}
	else
	{
		m_pApi->m_pInterface->AddLog(L"已取消对话框...",COLOR_BROWN);
		return;
	}

	m_bIsEngMode = m_pApi->m_pInterface->ReadConfigInt(L"Main", L"bIsEngMode", 0);
	if (m_bIsEngMode)
	{
		m_bIsEngMode = FALSE;
		m_pApi->m_pInterface->WriteConfigInt(L"Main", L"bIsEngMode", 0);
		m_pApi->m_pInterface->AddLog(L"测试项目已锁定", COLOR_BROWN);
	}
	else
	{
		m_bIsEngMode = TRUE;
		m_pApi->m_pInterface->WriteConfigInt(L"Main", L"bIsEngMode", 1);
		m_pApi->m_pInterface->AddLog(L"测试项目已解锁", COLOR_BROWN);
	}

}
void CMainFrame::OnEnableGenMenu(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
// 	if (m_pApi->m_pInterface->pST->ManualTest)
// 	{
// 		pCmdUI->Enable(true);
// 
// 	}

	//CleanText();
	
}
void CMainFrame::OnUpdateEngMode(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_bIsEngMode)
	{
		pCmdUI->SetText(L"调试模式");
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"量产模式");
		pCmdUI->SetCheck(TRUE);
	}
	CleanText();
}
void CMainFrame::OnUpdatePlayCam(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码

}


void CMainFrame::OnCheck3000k()
{
	// TODO:  在此添加命令处理程序代码
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource3000();
}


void CMainFrame::OnCheck4000k()
{
	// TODO:  在此添加命令处理程序代码
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource4000();
}


void CMainFrame::OnCheck5100k()
{
	// TODO:  在此添加命令处理程序代码
	StopTest();
	m_pApi->m_pInterface->pST->CheckLightSource5100();
}


void CMainFrame::OnCheckMtf()
{
	// TODO:  在此添加命令处理程序代码
	m_pApi->m_pInterface->pST->CheckMTF();
}


void CMainFrame::OnUpdateBlemish(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pApi->m_pInterface->bIsBlemish)
	{
		pCmdUI->SetText(L"关闭脏污模式");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"开启脏污模式");
	}
}


void CMainFrame::OnBlemish()
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pApi->m_pInterface->m_bCross)
	{
		pCmdUI->SetText(L"关闭中心十字");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"开启中心十字");
	}
}


void CMainFrame::OnAwb()
{
	// TODO:  在此添加命令处理程序代码
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
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pApi->m_pInterface->m_AWBEN2)
	{
		pCmdUI->SetText(L"关闭白平衡");
		//pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetText(L"开启白平衡");
	}
}


void CMainFrame::OnBnClickedTestInfo()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxMessageBox(L"123");
}
