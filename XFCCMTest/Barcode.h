#pragma once
#include "afxwin.h"


// CBarcode �Ի���

class CBarcode : public CDialog
{
	DECLARE_DYNAMIC(CBarcode)

public:
	CBarcode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBarcode();

// �Ի�������
	enum { IDD = IDD_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
