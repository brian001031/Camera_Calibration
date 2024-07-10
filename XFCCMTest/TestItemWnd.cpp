// TestInfoWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "TestItemWnd.h"


// CTestItemWnd

IMPLEMENT_DYNAMIC(CTestItemWnd, CDockablePane)

CTestItemWnd::CTestItemWnd()
{

}

CTestItemWnd::~CTestItemWnd()
{
}


BEGIN_MESSAGE_MAP(CTestItemWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CTestItemWnd 消息处理程序




int CTestItemWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	const DWORD dwStyle = WS_CHILD | WS_VISIBLE;

	m_TestItemDlg.Create(CTestItemDlg::IDD,this);
	//m_TestItemDlg.SetBackgroundColor(RGB(0, 255, 255));
	m_TestItemDlg.ShowWindow(SW_SHOW);


	return 1;
}


void CTestItemWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	// TODO:  在此处添加消息处理程序代码
	CWnd *pWnd = CWnd::FromHandle(m_TestItemDlg.m_hWnd);

	if (m_TestItemDlg.GetSafeHwnd())
	{
		m_TestItemDlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		int h = int(cy *0.6);
    	m_TestItemDlg.m_hWndTestItem.SetWindowPos(pWnd, 0, 0, cx, h, SWP_NOACTIVATE | SWP_NOZORDER);

		//m_TestItemDlg.m_Barcode.SetWindowPos(pWnd, 0, h, cx, int(cy *0.06), SWP_NOACTIVATE | SWP_NOZORDER);

		m_TestItemDlg.m_hWndTestInfo.SetWindowPos(pWnd, 0, h, cx, int((cy) *0.4), SWP_NOACTIVATE | SWP_NOZORDER);
		
	}
	
}
