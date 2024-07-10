#pragma once

class XFButton : public CMFCButton
{
	DECLARE_DYNAMIC(XFButton)

public:
	XFButton();
	virtual ~XFButton();

	void DrawBorder(CDC* pDC, CRect& rectClient, UINT uiState); 

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual void OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState);
	DECLARE_MESSAGE_MAP()
	
};


