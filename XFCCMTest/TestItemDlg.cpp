// TestItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "TestItemDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTestItemDlg 对话框

IMPLEMENT_DYNAMIC(CTestItemDlg, CDialogEx)

CTestItemDlg::CTestItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestItemDlg::IDD, pParent)
{

}

CTestItemDlg::~CTestItemDlg()
{

}

void CTestItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEST_INFO, m_hWndTestInfo);
	DDX_Control(pDX, IDC_TEST_ITEM, m_hWndTestItem);
	//DDX_Control(pDX, IDC_EDIT_BARCODE, m_Barcode);
}


BEGIN_MESSAGE_MAP(CTestItemDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_TEST_ITEM, &CTestItemDlg::OnNMDblclkTestItem)
//	ON_STN_CLICKED(IDC_TEST_INFO, &CTestItemDlg::OnStnClickedTestInfo)
	ON_BN_CLICKED(IDC_TEST_INFO, &CTestItemDlg::OnBnClickedTestInfo)
END_MESSAGE_MAP()


// CTestItemDlg 消息处理程序



BOOL CTestItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	m_hWndTestItem.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_hWndTestItem.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 38, 0);
	m_hWndTestItem.InsertColumn(1, _T("测试项目"), LVCFMT_LEFT, 130, 0);
	m_hWndTestItem.InsertColumn(2, _T("耗时"), LVCFMT_LEFT, 70, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTestItemDlg::OnNMDblclkTestItem(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	int item = 0;
	item = m_hWndTestItem.GetNextItem(-1, LVIS_SELECTED); //获取选择行

	if (item == -1)//如果没有选中,默认第一行
	{
		item = 0;
		m_hWndTestItem.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //选中行
		m_hWndTestItem.SetSelectionMark(0);
		return;
	}

	AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, (WPARAM)&item, MyMessage::DBCLICK_TEST);

}


void CTestItemDlg::OnStnClickedTestInfo()
{
	// TODO:  在此添加控件通知处理程序代码
	
	//AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, 0, MyMessage::FlowTEST);
	
}





void CTestItemDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	return;
	CDialogEx::OnOK();
}


void CTestItemDlg::OnBnClickedTestInfo()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, 0, MyMessage::FlowTEST);
}
