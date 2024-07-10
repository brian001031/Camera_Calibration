#pragma once
#include "afxwin.h"

class CColorStatic :public CStatic
{
public:
	CColorStatic(void);
	~CColorStatic(void);
protected:
	COLORREF m_crText;
	COLORREF m_crBackColor;
	HBRUSH   m_hBrush;
	LOGFONT  m_lf;
	CFont    m_font;
	bool     m_bTran;
	CRect    m_rc;


	public:
		void SetTextColor(COLORREF crText);
		void SetFontSize(int nSize);
		void SetBackColor(COLORREF crBackColor);
		void SetTransparent(bool bTran);
//		void SetBackImage(CImage crBackImage);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

public:
	//CImage tempImage;
	//HBITMAP tempHbitmap;
};
