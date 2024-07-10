// TestItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XFCCMTest.h"
#include "TestItemDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTestItemDlg �Ի���

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


// CTestItemDlg ��Ϣ�������



BOOL CTestItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	m_hWndTestItem.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_hWndTestItem.InsertColumn(0, _T("���"), LVCFMT_LEFT, 38, 0);
	m_hWndTestItem.InsertColumn(1, _T("������Ŀ"), LVCFMT_LEFT, 130, 0);
	m_hWndTestItem.InsertColumn(2, _T("��ʱ"), LVCFMT_LEFT, 70, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTestItemDlg::OnNMDblclkTestItem(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int item = 0;
	item = m_hWndTestItem.GetNextItem(-1, LVIS_SELECTED); //��ȡѡ����

	if (item == -1)//���û��ѡ��,Ĭ�ϵ�һ��
	{
		item = 0;
		m_hWndTestItem.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //ѡ����
		m_hWndTestItem.SetSelectionMark(0);
		return;
	}

	AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, (WPARAM)&item, MyMessage::DBCLICK_TEST);

}


void CTestItemDlg::OnStnClickedTestInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	//AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, 0, MyMessage::FlowTEST);
	
}





void CTestItemDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	return;
	CDialogEx::OnOK();
}


void CTestItemDlg::OnBnClickedTestInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->SendMessage(WM_MY_MESSAGE, 0, MyMessage::FlowTEST);
}
