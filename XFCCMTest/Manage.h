#pragma once


// CManage �Ի���

class CManage : public CDialogEx
{
	DECLARE_DYNAMIC(CManage)

public:
	CManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManage();

// �Ի�������
	enum { IDD = IDD_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	void LoadConfig();
public:
	CString strPassword;
	CString strPasswordCheck;
	afx_msg void OnBnClickedOk();
};
