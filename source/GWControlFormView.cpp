/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif

//#define SCROLL_PIXEL



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWControlFormView::CGWControlFormView()
{
	m_Model = CX_NULL_POINTER;
}

CGWControlFormView::~CGWControlFormView()
{
}

//===========================================================================
void CGWControlFormView::PreCreate(CREATESTRUCT& cs)
{
	CWnd::PreCreate(cs);
	
	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

int CGWControlFormView::OnCreate(CREATESTRUCT& cs)
{
	UNREFERENCED_PARAMETER(cs);

	SetTimer (1, 250, NULL) ;

	m_Model = new gw::ctrl::form();
	m_Model->set_window(*this);
	m_Model->create(&GetMyWinApp()->_control_widget_entry_collection);
	m_Model->get_view()->set_background_color(gw::color_t::White);

	SCROLLINFO si;


#if defined(SCROLL_PIXEL)
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = 0;
	si.nPos   = 0;
	si.nPage  = 20;
	::SetScrollInfo(*this, SB_HORZ, &si, TRUE);


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = 0;
	si.nPos   = 0;
	si.nPage  = 20;
	::SetScrollInfo(*this, SB_VERT, &si, TRUE);
#else
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = 0;
	si.nPos   = 0;
	si.nPage  = 1;
	::SetScrollInfo(*this, SB_HORZ, &si, TRUE);


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = 0;
	si.nPos   = 0;
	si.nPage  = 1;
	::SetScrollInfo(*this, SB_VERT, &si, TRUE);
#endif

	return 0;
}

void CGWControlFormView::OnDestroy()
{
	m_Model->destroy();
	delete m_Model;
	m_Model = CX_NULL_POINTER;

	KillTimer(1);
}

LRESULT CGWControlFormView::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

	SetFocus();
	return FinalWindowProc(msg, wparam, lparam);
}

LRESULT CGWControlFormView::OnSize(UINT msg, WPARAM wparam, LPARAM lparam)
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


		m_Model->get_view()->set_viewport_window_size(m_cxClientMax, m_cyClientMax);

#if defined(SCROLL_PIXEL)
		int scroll_max_x;
		int scroll_max_y;


		scroll_max_x = m_Model->get_view()->get_viewscale_xsize() - m_Model->get_view()->get_viewport_window_xsize();
		if (scroll_max_x<0)
		{
			scroll_max_x=0;
		}
		scroll_max_y = m_Model->get_view()->get_viewscale_ysize() - m_Model->get_view()->get_viewport_window_ysize();
		if (scroll_max_y<0)
		{
			scroll_max_y=0;
		}


		SCROLLINFO si;


		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_x;
		si.nPos   = 0;
		si.nPage  = 20;
		::SetScrollInfo(*this, SB_HORZ, &si, TRUE);
//		SetScrollRange(SB_HORZ, 0, scroll_max, TRUE);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_y;
		si.nPos   = 0;
		si.nPage  = 20;
		::SetScrollInfo(*this, SB_VERT, &si, TRUE);
//		SetScrollRange(SB_VERT, 0, scroll_max, TRUE);


		int scroll_pos_x;
		int scroll_pos_y;

		scroll_pos_x = static_cast<cx::int_t>( GetScrollPos(SB_HORZ) );
		scroll_pos_y = static_cast<cx::int_t>( GetScrollPos(SB_VERT) );

		m_Model->get_view()->set_viewport_window_offset (scroll_pos_x,scroll_pos_y);
#else
		int scroll_max_x;
		int scroll_max_y;

		scroll_max_x = m_Model->get_view()->get_viewscale_xsize() - m_Model->get_view()->get_viewport_window_xsize();
		if (scroll_max_x<0)
		{
			scroll_max_x=0;
		}
		scroll_max_y = m_Model->get_view()->get_viewscale_ysize() - m_Model->get_view()->get_viewport_window_ysize();
		if (scroll_max_y<0)
		{
			scroll_max_y=0;
		}


		SCROLLINFO si;

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_x==0 ? 0 : 100;
		si.nPos   = 0;
		si.nPage  = 1;
		::SetScrollInfo(*this, SB_HORZ, &si, TRUE);
//		SetScrollRange(SB_HORZ, 0, scroll_max, TRUE);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_y==0 ? 0 : 100;
		si.nPos   = 0;
		si.nPage  = 1;
		::SetScrollInfo(*this, SB_VERT, &si, TRUE);
//		SetScrollRange(SB_VERT, 0, scroll_max, TRUE);


		int scroll_pos_x;
		int scroll_pos_y;

		scroll_pos_x = static_cast<cx::int_t>( GetScrollPos(SB_HORZ) ) * scroll_max_x / 100;
		scroll_pos_y = static_cast<cx::int_t>( GetScrollPos(SB_VERT) ) * scroll_max_y / 100;

		m_Model->get_view()->set_viewport_window_offset (scroll_pos_x,scroll_pos_y);
#endif

		Invalidate();
	}

	return 0;
}

LRESULT CGWControlFormView::OnHScroll (UINT msg, WPARAM wparam, LPARAM lparam)
{
	int   code     ;
	int   position ;
	HWND  scrollbar;


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


	SCROLLINFO si;


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;
	if (FALSE==::GetScrollInfo(*this, SB_HORZ, &si))
	{
		return 0;
	}


	switch(code)
	{
	case SB_LEFT         : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LEFT         "); position = si.nMin          ; break;
	case SB_RIGHT        : CX_DEBUG_TRACEF(TW_THISCODE, "SB_RIGHT        "); position = si.nMax          ; break;
	case SB_LINELEFT     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINELEFT     "); position = position-1       ; break;
	case SB_LINERIGHT    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINERIGHT    "); position = position+1       ; break;
	case SB_PAGELEFT     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGELEFT     "); position = position-si.nPage; break;
	case SB_PAGERIGHT    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGERIGHT    "); position = position+si.nPage; break;
	case SB_THUMBTRACK   : CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBTRACK   "); position = position         ; break;
	case SB_THUMBPOSITION: CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBPOSITION"); position = position         ; break; 
	case SB_ENDSCROLL    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_ENDSCROLL    "); position = position         ; return 0; break;
	}

	if (position>si.nMax)
	{
		position = si.nMax;
	}
	if (position<si.nMin)
	{
		position = si.nMin;
	}

	SetScrollPos(SB_HORZ, position, TRUE);


#if defined(SCROLL_PIXEL)
	int scroll_pos_x;
	
	scroll_pos_x = position;
#else
	int scroll_max_x;
	int scroll_max_y;

	scroll_max_x = m_Model->get_view()->get_viewscale_xsize() - m_Model->get_view()->get_viewport_window_xsize();
	if (scroll_max_x<0)
	{
		scroll_max_x=0;
	}
	scroll_max_y = m_Model->get_view()->get_viewscale_ysize() - m_Model->get_view()->get_viewport_window_ysize();
	if (scroll_max_y<0)
	{
		scroll_max_y=0;
	}


	int scroll_pos_x;
	
	scroll_pos_x = scroll_max_x==0 ? 0 : position * scroll_max_x / 100;
#endif


	m_Model->get_view()->set_viewport_window_xoffset (scroll_pos_x);


	Invalidate();

	return 0;
}

LRESULT CGWControlFormView::OnVScroll (UINT msg, WPARAM wparam, LPARAM lparam)
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


	SCROLLINFO si;


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;
	if (FALSE==::GetScrollInfo(*this, SB_VERT, &si))
	{
		return 0;
	}


	switch(code)
	{
	case SB_TOP          : CX_DEBUG_TRACEF(TW_THISCODE, "SB_TOP          "); position = si.nMin          ; break;
	case SB_BOTTOM       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_BOTTOM       "); position = si.nMax          ; break;
	case SB_LINEUP       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINEUP       "); position = position-1       ; break;
	case SB_LINEDOWN     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINEDOWN     "); position = position+1       ; break;
	case SB_PAGEUP       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGEUP       "); position = position-si.nPage; break;
	case SB_PAGEDOWN     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGEDOWN     "); position = position+si.nPage; break;
	case SB_THUMBTRACK   : CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBTRACK   "); position = position         ; break;
	case SB_THUMBPOSITION: CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBPOSITION"); position = position         ; break; 
	case SB_ENDSCROLL    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_ENDSCROLL    "); position = position         ; return 0; break;
	}

	if (position>si.nMax)
	{
		position = si.nMax;
	}
	if (position<si.nMin)
	{
		position = si.nMin;
	}

	SetScrollPos(SB_VERT, position, TRUE);


#if defined(SCROLL_PIXEL)
	int scroll_pos_y;
	
	scroll_pos_y = position;
#else
	int scroll_max_x;
	int scroll_max_y;

	scroll_max_x = m_Model->get_view()->get_viewscale_xsize() - m_Model->get_view()->get_viewport_window_xsize();
	if (scroll_max_x<0)
	{
		scroll_max_x=0;
	}
	scroll_max_y = m_Model->get_view()->get_viewscale_ysize() - m_Model->get_view()->get_viewport_window_ysize();
	if (scroll_max_y<0)
	{
		scroll_max_y=0;
	}


	int scroll_pos_y;
	
	scroll_pos_y = scroll_max_y==0 ? 0 : position * scroll_max_y / 100;
#endif

	m_Model->get_view()->set_viewport_window_yoffset (scroll_pos_y);


	Invalidate();

	return 0;
}

LRESULT CGWControlFormView::OnMouseWheel (UINT msg, WPARAM wparam, LPARAM lparam)
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

	if ( scale )
	{
		cx::float_t viewscale_delta;
		cx::float_t viewscale_max  ;
		cx::float_t viewscale_min  ;

		cx::float_t viewscale;
		cx::float_t previous_viewscale;


		viewscale       = m_Model->get_view()->get_viewscale();
		viewscale_max   =  5.0f;
		viewscale_min   =  0.1f;
		viewscale_delta =  0.1f;

		previous_viewscale = viewscale;



		if ( zDelta>0 ) 
		{
			viewscale = viewscale + viewscale_delta;
		}
		else
		{
			viewscale = viewscale - viewscale_delta;
		}

		if (viewscale>viewscale_max)
		{
			viewscale = viewscale_max;
		}
		if (viewscale<viewscale_min)
		{
			viewscale = viewscale_min;
		}

		m_Model->get_view()->set_viewscale(viewscale);



		int scroll_max_x;
		int scroll_max_y;

		scroll_max_x = m_Model->get_view()->get_viewscale_xsize() - m_Model->get_view()->get_viewport_window_xsize();
		if (scroll_max_x<0)
		{
			scroll_max_x=0;
		}
		scroll_max_y = m_Model->get_view()->get_viewscale_ysize() - m_Model->get_view()->get_viewport_window_ysize();
		if (scroll_max_y<0)
		{
			scroll_max_y=0;
		}

#if defined(SCROLL_PIXEL)
		int scroll_pos_x;
		int scroll_pos_y;

		scroll_pos_x = static_cast<cx::int_t>( GetScrollPos(SB_VERT) / previous_viewscale );
		scroll_pos_y = static_cast<cx::int_t>( GetScrollPos(SB_HORZ) / previous_viewscale );

		scroll_pos_x = static_cast<cx::int_t>(scroll_pos_x*viewscale);
		scroll_pos_y = static_cast<cx::int_t>(scroll_pos_y*viewscale);


		SCROLLINFO si;


		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_x;
		si.nPos   = scroll_pos_x;
		si.nPage  = 20;
		::SetScrollInfo(*this, SB_HORZ, &si, TRUE);


		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_y;
		si.nPos   = scroll_pos_y;
		si.nPage  = 20;
		::SetScrollInfo(*this, SB_VERT, &si, TRUE);


		m_Model->get_view()->set_viewport_window_offset (scroll_pos_x,scroll_pos_y);
#else
		int scroll_pos_x;
		int scroll_pos_y;

		scroll_pos_x = static_cast<cx::int_t>( GetScrollPos(SB_VERT) );
		scroll_pos_y = static_cast<cx::int_t>( GetScrollPos(SB_HORZ) );


		SCROLLINFO si;


		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_x==0 ? 0 : 100;
		si.nPos   = scroll_pos_x;
		si.nPage  = 1;
		::SetScrollInfo(*this, SB_HORZ, &si, TRUE);


		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_RANGE | SIF_POS | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = scroll_max_y==0 ? 0 : 100;
		si.nPos   = scroll_pos_y;
		si.nPage  = 1;
		::SetScrollInfo(*this, SB_VERT, &si, TRUE);


		m_Model->get_view()->set_viewport_window_offset (scroll_pos_x,scroll_pos_y);
#endif

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

LRESULT CGWControlFormView::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	return 0;
}

/*
LRESULT CGWControlFormView::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	CPaintDC dc(GetHwnd());


	Draw(dc);


	return 0;
}
*/

void CGWControlFormView::OnDraw(CDC& dc)
{
	// OnDraw is called automatically whenever a part of the window needs to be redrawn.
	Draw(dc);
}

void CGWControlFormView::Draw (CDC& dc)
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

	if (m_Model)
	{
		m_Model->get_view()->draw(memoryDC);
	}


	dc.BitBlt(0, 0, rect.right, rect.bottom, memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(hOldBitmap);
	memoryDC.Destroy();

	bitmap.DeleteObject();
#else
	dc.SolidFill(RGB(0xFFu, 0xFFu, 0xFFu), rect);

	m_Model->get_view()->draw(dc);
#endif

	return;


	CRect rc = GetClientRect();


	TCHAR text[256];
	
	
	sprintf_s(text, "%d %d - %d %d %d %d ",
		m_cxClientMax, m_cyClientMax,
		rc.left,
		rc.right,
		rc.top,
		rc.bottom
		);

	dc.DrawText(text, -1, rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

BOOL CGWControlFormView::OnEraseBkgnd(CDC& dc)
{
	UNREFERENCED_PARAMETER(dc);

	return TRUE;
}

LRESULT CGWControlFormView::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


	switch (msg)
	{
	case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
	case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
	case WM_HSCROLL:        lResult = OnHScroll       (msg, wparam, lparam); break;
	case WM_VSCROLL:        lResult = OnVScroll       (msg, wparam, lparam); break;
	case WM_MOUSEWHEEL:     lResult = OnMouseWheel    (msg, wparam, lparam); break;
	case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;
//	case WM_PAINT:          lResult = OnPaint         (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
	}

	if (m_Model)
	{
		m_Model->get_window_event_handler()->on_windows_message(*this, msg, wparam, lparam);
	}

	return lResult;
}



