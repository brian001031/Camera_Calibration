// XFButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XFButton.h"


// XFButton

IMPLEMENT_DYNAMIC(XFButton, CMFCButton)

XFButton::XFButton()
{
}

XFButton::~XFButton()
{
}

BEGIN_MESSAGE_MAP(XFButton, CMFCButton)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// XFButton 消息处理程序
void XFButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ENSURE(lpDIS != NULL);
	ENSURE(lpDIS->CtlType == ODT_BUTTON);

	CDC* pDCPaint = CDC::FromHandle(lpDIS->hDC);
	ASSERT_VALID(pDCPaint);

	CMemDC memDC(*pDCPaint, this);
	CDC* pDC = &memDC.GetDC();

	CRect rectClient = lpDIS->rcItem;

	OnFillBackground(pDC, rectClient);
	
	OnDrawBorder(pDC, rectClient, lpDIS->itemState);
	

	COLORREF clrBtnText = afxGlobalData.clrBtnText;
	afxGlobalData.clrBtnText = RGB(0,0,0);			
	OnDraw(pDC, rectClient, lpDIS->itemState);
	afxGlobalData.clrBtnText = clrBtnText;


}

void XFButton::OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState)
{
	// TODO: 在此添加专用代码和/或调用基类
	DrawBorder(pDC, rectClient, uiState);
}

void XFButton::DrawBorder(CDC* pDC, CRect& rectClient, UINT uiState) 
{
	COLORREF bkColor;
	CPen pen(PS_SOLID, 1, RGB(46, 130, 255));

	if (uiState & ODS_DISABLED)
		bkColor = RGB(255, 204, 237);
	else
		bkColor = RGB(150, 190, 230);

	if (m_bHighlighted)
		bkColor = RGB(214, 241, 18);
		//bkColor = RGB(15, 141, 239);
		//bkColor = RGB(204, 230, 255);
	
// 	if (m_bClickiedInside)
// 		bkColor = RGB(255, 0, 0);

	CBrush brush(bkColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(pen);
	pDC->SelectObject(brush);
	pDC->Rectangle(rectClient);

// 	if (m_bClickiedInside)
// 	{
// 		pDC->Draw3dRect(rectClient, afxGlobalData.clrBtnLight, afxGlobalData.clrBtnHilite);
// 	}
		
}