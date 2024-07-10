#pragma once


// CTestItemDlg 对话框

#include "../Include/XFApi.h"
#include "ColorStatic.h"
#include "afxwin.h"

class CTestItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestItemDlg)

public:
	CTestItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestItemDlg();

// 对话框数据
	enum { IDD = IDD_DLG_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CColorStatic  m_hWndTestInfo;
	virtual BOOL OnInitDialog();
	CListCtrl m_hWndTestItem;
	afx_msg void OnNMDblclkTestItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedTestInfo();

	virtual void OnOK();
	afx_msg void OnBnClickedTestInfo();
};
