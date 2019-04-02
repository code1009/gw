/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CInplaceWindow::CInplaceWindow()
{
}

CInplaceWindow::~CInplaceWindow()
{
}


//===========================================================================
void CInplaceWindow::PreCreate(CREATESTRUCT& cs)
{
	CWnd::PreCreate(cs);
	
	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

int CInplaceWindow::OnCreate(CREATESTRUCT& cs)
{
	UNREFERENCED_PARAMETER(cs);

	//SetTimer (1, 250, NULL) ;

	return 0;
}

void CInplaceWindow::OnDestroy()
{
}

LRESULT CInplaceWindow::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

	SetFocus();
	return FinalWindowProc(msg, wparam, lparam);
}

LRESULT CInplaceWindow::OnSize(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);

	// If not minimized, save the window size
	if (wparam != SIZE_MINIMIZED)
	{
		m_cxClientMax = LOWORD (lparam) ;
		if (m_cxClientMax < 1)
			m_cxClientMax = 1;

		m_cyClientMax = HIWORD (lparam) ;
		if (m_cyClientMax < 1)
			m_cyClientMax = 1;

		Invalidate();
	}

	return 0;
}

LRESULT CInplaceWindow::OnHScroll (UINT msg, WPARAM wparam, LPARAM lparam)
{
	int  code     ;
	HWND scrollbar;

	int  position ;


	code       = (int )LOWORD(wparam);
	scrollbar  = (HWND)lparam;

	if (SB_THUMBTRACK   == code || 
		SB_THUMBPOSITION== code  )
	{
		position = (SHORT)HIWORD(wparam);
	}
	else
	{
		position = GetScrollPos(SB_HORZ);
	}

	Invalidate();

	return 0;
}

LRESULT CInplaceWindow::OnVScroll (UINT msg, WPARAM wparam, LPARAM lparam)
{
	int  code     ;
	HWND scrollbar;

	int  position ;


	code       = (int )LOWORD(wparam);
	scrollbar  = (HWND)lparam;

	if (SB_THUMBTRACK   == code || 
		SB_THUMBPOSITION== code  )
	{
		position = (SHORT)HIWORD(wparam);
	}
	else
	{
		position = GetScrollPos(SB_VERT);
	}

	Invalidate();

	return 0;
}

LRESULT CInplaceWindow::OnMouseWheel (UINT msg, WPARAM wparam, LPARAM lparam)
{
	CPoint ptMouse((short)LOWORD(lparam), (short)HIWORD(lparam));
	UINT   uMouseFlag = wparam;

	WORD  fwKeys = LOWORD(wparam);
	SHORT zDelta = HIWORD(wparam);


	cx::bool_t scale = false;

	switch (fwKeys)
	{
	case MK_CONTROL  :
		scale = true;
		break;
	case MK_LBUTTON  :
	case MK_RBUTTON  :
		break;
	case MK_MBUTTON  :
		break;
	case MK_SHIFT    :
		break;
	case MK_XBUTTON1 :
	case MK_XBUTTON2 :
		break;
	}

//	scale = false;
	if ( scale )
	{
		Invalidate();
	}
	else
	{
		if ( zDelta > 0 )
		{
			OnVScroll(0,MAKEWORD(SB_LINEUP,0),0);
		}
		else
		{
			OnVScroll(0,MAKEWORD(SB_LINEDOWN,0),0);
		}
	}

	return 0;
}

LRESULT CInplaceWindow::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	return 0;
}

/*
LRESULT CInplaceWindow::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	CPaintDC dc(GetHwnd());


	Draw(dc);


	return 0;
}
*/

void CInplaceWindow::OnDraw(CDC& dc)
{
	// OnDraw is called automatically whenever a part of the window needs to be redrawn.
	Draw(dc);
}

void CInplaceWindow::Draw (CDC& dc)
{
	CRect rect;
	
	
	rect = GetClientRect();


#if 1
	CDC     memoryDC;
	CBitmap bitmap;
	HBITMAP hOldBitmap;

	memoryDC.CreateCompatibleDC    (dc);
	bitmap  .CreateCompatibleBitmap(dc, rect.right, rect.bottom);

	hOldBitmap = memoryDC.SelectObject(bitmap);

	memoryDC.SolidFill(RGB(0xFFu, 0xFFu, 0xFFu), rect);



	dc.BitBlt(0, 0, rect.right, rect.bottom, memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(hOldBitmap);
	memoryDC.Destroy();

	bitmap.DeleteObject();
#else
	dc.SolidFill(RGB(0xFFu, 0xFFu, 0xFFu), rect);

	m_Model->get_view()->draw(dc);
#endif

	return;
}

BOOL CInplaceWindow::OnEraseBkgnd(CDC& dc)
{
	UNREFERENCED_PARAMETER(dc);

	return TRUE;
}

LRESULT CInplaceWindow::OnLButtonUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONUP");
	return 0;
}

LRESULT CInplaceWindow::OnLButtonDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONDOWN");

	return 0;
}

LRESULT CInplaceWindow::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


	switch (msg)
	{
	case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
	case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
	case WM_HSCROLL:        lResult = OnHScroll       (msg, wparam, lparam); break;
	case WM_VSCROLL:        lResult = OnVScroll       (msg, wparam, lparam); break;
	case WM_MOUSEWHEEL:     lResult = OnMouseWheel    (msg, wparam, lparam); break;
//	case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;
//	case WM_PAINT:          lResult = OnPaint         (msg, wparam, lparam); break;
//	case WM_LBUTTONDOWN:    lResult = OnLButtonDown   (msg, wparam, lparam); break;
//	case WM_LBUTTONUP:      lResult = OnLButtonUp     (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
	}


	return lResult;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CInplaceEditWindow::CInplaceEditWindow()
{
}

CInplaceEditWindow::~CInplaceEditWindow()
{
}

//===========================================================================
void CInplaceEditWindow::PreCreate(CREATESTRUCT& cs)
{
    CEdit::PreCreate(cs);
	
//	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
//	cs.dwExStyle |=  WS_EX_CLIENTEDGE;

	cs.style = WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOHSCROLL;
}

//===========================================================================
int CInplaceEditWindow::OnCreate(CREATESTRUCT& cs)
{
	int nResult;


	nResult = CEdit::OnCreate(cs);

	SetFont( GetParent().GetFont() );

	SetMargins(2+8, 8);


	return nResult;
}

void CInplaceEditWindow::OnDestroy()
{
	CEdit::OnDestroy();
}

//===========================================================================
LRESULT CInplaceEditWindow::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


	switch (msg)
	{
	case WM_KEYDOWN   : lResult = OnKeyDown    (msg, wparam, lparam); break;
	case WM_CHAR      : lResult = OnChar       (msg, wparam, lparam); break;
	case WM_SETFOCUS  : lResult = OnSetFocus   (msg, wparam, lparam); break;
	case WM_KILLFOCUS : lResult = OnKillFocus  (msg, wparam, lparam); break;
	case WM_GETDLGCODE: lResult = OnGetDlgCode (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
	}


	return lResult;
}

LRESULT CInplaceEditWindow::OnKeyDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	int lLow, lHigh;


	switch (wparam) 
	{
	case VK_ESCAPE:
		m_Cancel = true;
		// FALL THROUGH...

	case VK_RETURN:
		// Force focus to parent to update value (see OnKillFocus()...)
		::SetFocus(GetParent());
		// FIX: Allowing a multiline EDIT to VK_ESCAPE will send a WM_CLOSE
		//      to the list control if it's embedded in a dialog!?
		return 0;

	case VK_TAB:
	case VK_UP:
	case VK_DOWN:
//		return ::PostMessage(GetParent(), WM_USER_PROP_NAVIGATE, LOWORD(wParam), 0);
		break;;

	case VK_LEFT:
		GetSel(lLow, lHigh);
		if (lLow != lHigh || lLow != 0) break;
//		return ::PostMessage(GetParent(), WM_USER_PROP_NAVIGATE, LOWORD(wParam), 0);
		break;;

	case VK_RIGHT:
		GetSel(lLow, lHigh);
		if (lLow != lHigh || lLow != GetWindowTextLength())
		{
			break;
		}
//		return ::PostMessage(GetParent(), WM_USER_PROP_NAVIGATE, LOWORD(wParam), 0);
		break;

	default:
		break;;
	}


	return WndProcDefault(msg, wparam, lparam);
}

LRESULT CInplaceEditWindow::OnChar(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch( LOWORD(wparam) ) 
	{
	case VK_RETURN:
	case VK_ESCAPE:
		// Do not BEEP!!!!
		return 0;
		break;

	default:
		break;
	}


	return WndProcDefault(msg, wparam, lparam);
}

LRESULT CInplaceEditWindow::OnSetFocus(UINT msg, WPARAM wparam, LPARAM lparam)
{
	m_Cancel = false;


	return WndProcDefault(msg, wparam, lparam);
}

LRESULT CInplaceEditWindow::OnKillFocus(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;
	
	
	lResult = WndProcDefault(msg, wparam, lparam);

	m_Cancel |= (GetModify() == FALSE);


//	::SendMessage(GetParent(), m_Cancel ? WM_USER_PROP_CANCELPROPERTY : WM_USER_PROP_UPDATEPROPERTY, 0, (LPARAM)*this);
	
	return lResult;
}

LRESULT CInplaceEditWindow::OnGetDlgCode(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return WndProcDefault(msg, wparam, lparam) | DLGC_WANTALLKEYS | DLGC_WANTARROWS;
}

