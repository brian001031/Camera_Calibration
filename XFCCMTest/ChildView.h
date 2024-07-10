
// ChildView.h : CChildView 类的接口
//


#pragma once

// CChildView 窗口

#include "../include/XFApi.h"
#include "ColorStatic.h"


class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	CColorStatic m_DisplayCtrl;

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

