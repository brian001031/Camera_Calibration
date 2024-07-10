#pragma once


// CManage 对话框

class CManage : public CDialogEx
{
	DECLARE_DYNAMIC(CManage)

public:
	CManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManage();

// 对话框数据
	enum { IDD = IDD_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	void LoadConfig();
public:
	CString strPassword;
	CString strPasswordCheck;
	afx_msg void OnBnClickedOk();
};
