#include "StdAfx.h"
#include "ColorStatic.h"

CColorStatic::CColorStatic(void)
{
	//m_font.CreatePointFont(500, _T("Microsoft Sans Serif"), NULL);
	//m_font = new CFont;
}

CColorStatic::~CColorStatic(void)
{
	//delete m_font;
}
BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		DeleteObject(m_hBrush);
		m_hBrush=CreateSolidBrush(m_crBackColor);
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkColor(m_crBackColor);
		if (m_bTran == true)
			pDC->SetBkMode(TRANSPARENT);
	}

	return m_hBrush;
}
void CColorStatic::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	RedrawWindow();
}
void CColorStatic::SetFontSize(int nSize)
{
	m_font.DeleteObject();
	m_font.CreatePointFont(nSize, L"Microsoft Sans Serif");
}
void CColorStatic::SetBackColor(COLORREF crBackColor)
{
	m_crBackColor = crBackColor;
	RedrawWindow();
}
void CColorStatic::SetTransparent(bool bTran)
{
	m_bTran = bTran;
	//RedrawWindow();
}

//void CColorStatic::SetBackImage(CImage crBackImage)
//{
//	if (crBackImage.IsNull())
//	{
//		return;
//	}
//	if (!tempImage.IsNull())
//	{
//		tempImage.Destroy();
//	}	
//	tempImage = crBackImage;
//	ModifyStyle(0,SS_BITMAP);
//	tempHbitmap = tempImage.Detach();
//	SetBitmap(tempHbitmap);
//	DeleteObject(tempImage);
//
//}
