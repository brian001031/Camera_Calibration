#pragma once
#include "TestItemDlg.h"

class CTestItemWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CTestItemWnd)

public:
	CTestItemWnd();
	virtual ~CTestItemWnd();

	CTestItemDlg m_TestItemDlg;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


