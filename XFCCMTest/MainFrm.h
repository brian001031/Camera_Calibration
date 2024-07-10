
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"
#include "OutputWnd.h"
#include "TestItemWnd.h"
#include "../Include/XFApi.h"
#include "XFButton.h"
#include "Barcode.h"
#include "Manage.h"
#define   IDC_START       5000
#define   IDC_DLG         5050


class CMainFrame : public CFrameWndEx
{

public:
	CMainFrame();
protected:
	DECLARE_DYNAMIC(CMainFrame)

	// 特性
public:

	// 操作
public:
	XFButton  m_btnPlay;

	XFApi  *m_pApi;



	// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCStatusBar     m_wndStatusBar;
	COutputWnd        m_wndOutput;
	CTestItemWnd      m_wndTestItem;
	CChildView		  m_wndView;
	BOOL              m_bDlgLogShow;
	BOOL              m_bDlgTestItemShow;
	BOOL              m_bIsTest;
	BOOL              m_bIsPlay;
	BOOL			  m_bIsManualTest;
	BOOL			  m_IsFocus;

	void              AddLog(WPARAM wParam);
	void			  AddLog(CString text = L"这是一个测试输出", COLORREF color = RGB(0, 0, 255), int yHeight = 170);
	void			  SetDisplayCtrlText(CString text = L"Test String", COLORREF BackColor = RGB(125, 125, 125), COLORREF textColor = RGB(0, 0, 255), int FontSize = 200);
	void              SetDisplayCtrlText(WPARAM wParam);
	void     		  StartTest();
	void              StopTest();
	void			  Stop();
	void			  CleanText();
	void			  DisplayText();
	void			  ClickTestBtn(UINT uID);
	void			  ShowTestItemDlg(UINT item);
	void			  LoadTestItem(void);
	void			  DoTest(void);
	void			  SetButtonFont(void);
	void			  StartFlowTest(void);
	void			  SetTestItemTime(WPARAM wParam);
	void              DeleteTestItem(void);
	void			  WriteLog();
	//2021.03.12 New Add
	void			  ReplaceBarcodeString(CString strIdentify, CString iniFile);

	BOOL			  MakeMulitBarcodeDirPath(LPWSTR szPath);

	void			  CreateFile_forMulitRawDistance(CString sBackUp_Dis_Raw, int cycle);

	//2021.04.08 New Add
	void			  FastCalibration_CMD_Ack(int cycle);

	// 生成的消息映射函数
protected:
	LRESULT		 MyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClick(UINT uID);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL    CreateDockingWindows();
	void    SetDockingWindowIcons(BOOL bHiColorIcons);
	CString CreateFileName();
	CString GetConfigPath(void);
public:
	virtual BOOL DestroyWindow();
	afx_msg void OnLoad();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowConfigDlg();
	afx_msg void OnCalcWindow();
	afx_msg void OnSaveWindow();
	afx_msg void OnWindowLog();
	afx_msg void OnUpdateWindowLog(CCmdUI *pCmdUI);
	afx_msg void OnWindowTestItem();
	afx_msg void OnUpdateWindowTestItem(CCmdUI *pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnSavePic();
	afx_msg void OnPlayCam();
	afx_msg void OnUpdatePlayCam(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEngMode(CCmdUI *pCmdUI);
	afx_msg void OnEngMode();
	afx_msg void OnEnableOTPMenu(CCmdUI *pCmdUI);
	afx_msg void OnEnableSenMenu(CCmdUI *pCmdUI);
	afx_msg void OnEnablePOGMenu(CCmdUI *pCmdUI);
	afx_msg void OnEnableItemMenu(CCmdUI *pCmdUI);
	afx_msg void OnEnableTestMenu(CCmdUI *pCmdUI); 
	afx_msg void OnEnableGenMenu(CCmdUI *pCmdUI);

	//2021.03.04 New Add	 

	ULONG   m_LogLenght;
	BOOL    m_bIsEngMode;
	afx_msg void OnCheck3000k();
	afx_msg void OnCheck4000k();
	afx_msg void OnCheck5100k();
	afx_msg void OnCheckMtf();

	//
private:
	HANDLE m_hManualTest;
	static UINT MuaualTestThead(LPVOID lpPara);
	int  MuaualTestThead(void);
	BOOL bManualTestFlag;
	BOOL bIsProcess;
	HANDLE m_hAutoTestFlag;
	static UINT AutoTestThead(LPVOID lpPara);
	int  AutoTestThead(void);
	BOOL bAutoTestFlag;
	CBarcode pDlg;
/*	CManage pDlgManage;*/
	BOOL    m_save_Raw_Multi;
	int     save_Raw_Num;
	int		m_Run_Usc_Count;

	int     Run_Raw_dis_Script;
	CString sCy1;
	CString sCy2;
	CString sCy_Cali;

	int _eeprom_ack;
	int _mulit_status;
public:
	afx_msg void OnUpdateBlemish(CCmdUI *pCmdUI);
	afx_msg void OnBlemish();
	afx_msg void OnCommondCross();
	afx_msg void OnUpdateCross(CCmdUI *pCmdUI);
	afx_msg void OnAwb();
	afx_msg void OnUpdateAwb(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedTestInfo();
};


