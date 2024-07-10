#pragma once
#include "afxwin.h"


// CBarcode 对话框

class CBarcode : public CDialog
{
	DECLARE_DYNAMIC(CBarcode)

public:
	CBarcode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBarcode();

// 对话框数据
	enum { IDD = IDD_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Barcode;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditBarcode();
	void LoadConfig();
	int   mBarcodeLength;
	bool  bBarcodeMode;
	CString strBarcode;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
