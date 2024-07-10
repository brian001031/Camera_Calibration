
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建输出窗格: 
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL;

	if (!m_wndOutputLog.Create(dwStyle, rectDummy, this,1))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}

	UpdateFonts();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndOutputLog.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

}


void COutputWnd::UpdateFonts()
{
 	m_wndOutputLog.SetFont(&afxGlobalData.fontRegular);

}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CRichEditCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
// 	CMenu menu;
// 	menu.LoadMenu(IDR_POPUP_EDIT);
// 
// 	CMenu* pSumMenu = menu.GetSubMenu(0);
// 
// 	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
// 	{
// 		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
// 
// 		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
// 			return;
// 
// 		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
// 		UpdateDialogControls(this, FALSE);
// 	}
	CPoint pt = point;
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);
	CMenu* PopupMenu = NULL;
	ScreenToClient(&pt);
	//加载菜单  
	//子菜单项  
	//右键点击 弹出此子菜单项  
	PopupMenu = menu.GetSubMenu(0);
	PopupMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

	SetFocus();

	
}

void COutputList::OnEditCopy()
{
	this->Copy();
}

void COutputList::OnEditClear()
{
	SetWindowText(L"");
}

void COutputList::AddLog(CString text,COLORREF color,LONG yHeight)
{
	//SetSel(-1, -1);
	/*在有空格的时候会出现界面卡死20181130*/
	text.TrimRight();
	text.TrimLeft();
	/*end*/
	SYSTEMTIME st;
	CString strDate, strTime;
	GetLocalTime(&st);
	strDate.Format(L"%4d/%2d/%2d %.2d:%.2d:%.2d:%.3d  ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,st.wMilliseconds);
	CString str = strDate + text;
//	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format("%Y/%m/%d %H:%M:%S  ") + text;

	CHARFORMAT defaultFont;
	defaultFont.cbSize = sizeof(CHARFORMAT);
	defaultFont.yHeight = yHeight;
	defaultFont.dwMask = CFM_FACE | CFM_SIZE | CFM_BOLD | CFM_COLOR;
	defaultFont.dwEffects = CFE_BOLD;
	defaultFont.crTextColor = color;
	lstrcpy(defaultFont.szFaceName, L"微软雅黑");
	SetWordCharFormat(defaultFont);
	str+= L"\n";
	ReplaceSel(str);
	SendMessage(WM_VSCROLL, SB_BOTTOM , 0);
	SetSel(-1, -1);
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
