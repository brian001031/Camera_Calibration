
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ����

class COutputList : public CRichEditCtrl
{
// ����
public:
	COutputList();

	void AddLog(CString text = L"����һ���������", COLORREF color = RGB(0, 0, 255), LONG yHeight = 170);

// ʵ��
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();


	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// ����
public:
	COutputWnd();

	void UpdateFonts();

	COutputList m_wndOutputLog;

// ����
protected:
	//CMFCTabCtrl	m_wndTabs;
	


protected:


// ʵ��
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

