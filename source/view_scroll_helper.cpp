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



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
view_scroll_helper::view_scroll_helper()
{
	_cf_xcenter = true;
	_cf_ycenter = true;
}

view_scroll_helper::~view_scroll_helper()
{
}

//===========================================================================
int view_scroll_helper::get_scroll_x (void)
{
	return x_to_xscroll(_x);
}

int view_scroll_helper::get_scroll_x_min (void)
{
	return x_to_xscroll(_x_min);
}

int view_scroll_helper::get_scroll_x_max (void)
{
	int x_max = x_to_xscroll(_x_max);

	
	if (0!=x_max)
	{
		x_max--;
	}

	return x_max;
}

int view_scroll_helper::get_scroll_x_page (void)
{
	return x_to_xscroll(_x_page);
/*
	int page = x_to_xscroll(_x_page);


	if (page!=0)
	{
		page--;
	}

	return page;
*/
}

int view_scroll_helper::get_scroll_y (void)
{
	return y_to_yscroll(_y);
}

int view_scroll_helper::get_scroll_y_min (void)
{
	return y_to_yscroll(_y_min);
}

int view_scroll_helper::get_scroll_y_max (void)
{
	int y_max = y_to_yscroll(_y_max);


	if (0!=y_max)
	{
		y_max--;
	}

	return y_max;
}

int view_scroll_helper::get_scroll_y_page (void)
{
	return y_to_yscroll(_y_page);

/*
	int page = y_to_yscroll(_y_page);


	if (page!=0)
	{
		page--;
	}

	return page;
*/
}

void view_scroll_helper::update_xscroll (void)
{
	SCROLLINFO si;


	si.cbSize    = sizeof(SCROLLINFO);
	si.fMask     = SIF_RANGE | SIF_POS | SIF_PAGE ; // | SIF_TRACKPOS;
	si.nMin      = get_scroll_x_min  ();
	si.nMax      = get_scroll_x_max  ();
	si.nPos      = get_scroll_x      ();
	si.nPage     = get_scroll_x_page ();
//	si.nTrackPos = get_scroll_x      ();

	::SetScrollInfo(_hwnd, SB_HORZ, &si, TRUE);
}

void view_scroll_helper::update_yscroll (void)
{
	SCROLLINFO si;


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask     = SIF_RANGE | SIF_POS | SIF_PAGE ; // | SIF_TRACKPOS;
	si.nMin      = get_scroll_y_min  ();
	si.nMax      = get_scroll_y_max  ();
	si.nPos      = get_scroll_y      ();
	si.nPage     = get_scroll_y_page ();
//	si.nTrackPos = get_scroll_y      ();

	::SetScrollInfo(_hwnd, SB_VERT, &si, TRUE);
}

//===========================================================================
int view_scroll_helper::x_to_xscroll (float v)
{
	if (_x_max==0.0f)
	{
		return 0;
	}

	if (v<_x_min) {v = _x_min;}
	if (v>_x_max) {v = _x_max;}

	return static_cast<int>(v*10000.0f/_x_max);
}

int view_scroll_helper::y_to_yscroll (float v)
{
	if (_y_max==0.0f)
	{
		return 0;
	}

	if (v<_y_min) {v = _y_min;}
	if (v>_y_max) {v = _y_max;}

	return static_cast<int>(v*10000.0f/_y_max);
}

float view_scroll_helper::xscroll_to_x(int v)
{
	if (v<    0) {v =     0;}
	if (v>10000) {v = 10000;}

	return _x_max * v / 10000.0f;
}

float view_scroll_helper::yscroll_to_y(int v)
{
	if (v<    0) {v =     0;}
	if (v>10000) {v = 10000;}

	return _y_max * v / 10000.0f;
}

//===========================================================================
void view_scroll_helper::recalc_xscroll (void)
{
	if (_contents_cx<_window_cx)
	{
		_x      = 0.0f;
		_x_min  = 0.0f;
		_x_max  = 0.0f;
		_x_page = 0.0f;

		if (_cf_xcenter)
		{
			_view_xoffset = (_window_cx - _contents_cx) / 2;
		}
		else
		{
			_view_xoffset = 0.0f;
		}
	}
	else
	{
		_x_min  = 0.0f;
		_x_max  = _contents_cx;//-_window_cx;
		_x_page = _window_cx;

		if (_x+_x_page>_x_max)
		{
			_x = _x_max-+_x_page;
		}
	}
}

void view_scroll_helper::recalc_yscroll (void)
{
	if (_contents_cy<_window_cy)
	{
		_y      = 0.0f;
		_y_min  = 0.0f;
		_y_max  = 0.0f;
		_y_page = 0.0f;

		if (_cf_ycenter)
		{
			_view_yoffset = (_window_cy - _contents_cy) / 2;
		}
		else
		{
			_view_yoffset = 0.0f;
		}
	}
	else
	{
		_y_min  = 0.0f;
		_y_max  = _contents_cy;//-_window_cy;
		_y_page = _window_cy;

		if (_y+_y_page>_y_max)
		{
			_y = _y_max-_y_page;
		}
	}
}

//===========================================================================
void view_scroll_helper::initialize (HWND hwnd, cx::bool_t cf_xcenter, cx::bool_t cf_ycenter)
{
	_hwnd = hwnd;

	_cf_xcenter = cf_xcenter;
	_cf_ycenter = cf_ycenter;

	_contents_cx = 1.0f;
	_contents_cy = 1.0f;
	_window_cx = 1.0f;
	_window_cy = 1.0f;
	_view_xoffset = 0.0f;
	_view_yoffset = 0.0f;

	_x      = 0.0f;
	_x_min  = 0.0f;
	_x_max  = 0.0f;
	_x_page = 0.0f;

	_y      = 0.0f;
	_y_min  = 0.0f;
	_y_max  = 0.0f;
	_y_page = 0.0f;

	update_xscroll();
	update_yscroll();
}

void view_scroll_helper::set_contents (float cx, float cy, cx::bool_t update_scroll)
{
	if (_contents_cx != cx)
	{
		_contents_cx = cx;

		recalc_xscroll();

		if (update_scroll)
		{
			update_xscroll();
		}
	}

	if (_contents_cy != cy)
	{
		_contents_cy = cy;

		recalc_yscroll();

		if (update_scroll)
		{
			update_yscroll();
		}
	}
}

void view_scroll_helper::set_window (int cx, int cy, cx::bool_t update_scroll)
{
	float wcx = static_cast<float>(cx);
	float wcy = static_cast<float>(cy);


	if (_window_cx != wcx)
	{
		_window_cx = wcx;

		recalc_xscroll();

		if (update_scroll)
		{
			update_xscroll();
		}
	}

	if (_window_cy != wcy)
	{
		_window_cy = wcy;

		recalc_yscroll();
		if (update_scroll)
		{
			update_yscroll();
		}
	}
}

void view_scroll_helper::on_xscroll(UINT code, int nPos)
{
	SCROLLINFO si;


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;
	if (FALSE==::GetScrollInfo(_hwnd, SB_HORZ, &si))
	{
		return;
	}


	float position;


	switch(code)
	{
	case SB_LEFT         : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LEFT          %d %d", si.nPos, nPos); position = _x_min            ; break;
	case SB_RIGHT        : CX_DEBUG_TRACEF(TW_THISCODE, "SB_RIGHT         %d %d", si.nPos, nPos); position = _x_max            ; break;
	case SB_LINELEFT     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINELEFT      %d %d", si.nPos, nPos); position = _x-(_x_page/10.0f); break;
	case SB_LINERIGHT    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINERIGHT     %d %d", si.nPos, nPos); position = _x+(_x_page/10.0f); break;
	case SB_PAGELEFT     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGELEFT      %d %d", si.nPos, nPos); position = _x-_x_page        ; break;
	case SB_PAGERIGHT    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGERIGHT     %d %d", si.nPos, nPos); position = _x+_x_page        ; break;
	case SB_THUMBTRACK   : CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBTRACK    %d %d", si.nPos, nPos); position = xscroll_to_x(nPos); break;
	case SB_THUMBPOSITION: CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBPOSITION %d %d", si.nPos, nPos); position = xscroll_to_x(nPos); break; 
	case SB_ENDSCROLL    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_ENDSCROLL     %d %d", si.nPos, nPos); position = xscroll_to_x(nPos); return; break;
	}


	if (_x_min>position)
	{
		position = _x_min;
	}
	if (_x_max-_x_page<position)
	{
		position = _x_max-_x_page;
	}

		
	_x = position;


	update_xscroll();
}

void view_scroll_helper::on_yscroll(UINT code, int nPos)
{
	SCROLLINFO si;


	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;
	if (FALSE==::GetScrollInfo(_hwnd, SB_VERT, &si))
	{
		return;
	}


	float position;


	switch(code)
	{
	case SB_TOP          : CX_DEBUG_TRACEF(TW_THISCODE, "SB_TOP           %d %d", si.nPos, nPos); position = _y_min            ; break;
	case SB_BOTTOM       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_BOTTOM        %d %d", si.nPos, nPos); position = _y_max            ; break;
	case SB_LINEUP       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINEUP        %d %d", si.nPos, nPos); position = _y-(_y_page/10.0f); break;
	case SB_LINEDOWN     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_LINEDOWN      %d %d", si.nPos, nPos); position = _y+(_y_page/10.0f); break;
	case SB_PAGEUP       : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGEUP        %d %d", si.nPos, nPos); position = _y-_y_page        ; break;
	case SB_PAGEDOWN     : CX_DEBUG_TRACEF(TW_THISCODE, "SB_PAGEDOWN      %d %d", si.nPos, nPos); position = _y+_y_page        ; break;
	case SB_THUMBTRACK   : CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBTRACK    %d %d", si.nPos, nPos); position = yscroll_to_y(nPos); break;
	case SB_THUMBPOSITION: CX_DEBUG_TRACEF(TW_THISCODE, "SB_THUMBPOSITION %d %d", si.nPos, nPos); position = yscroll_to_y(nPos); break; 
	case SB_ENDSCROLL    : CX_DEBUG_TRACEF(TW_THISCODE, "SB_ENDSCROLL     %d %d", si.nPos, nPos); position = yscroll_to_y(nPos); return; break;
	}
		

	if (_y_min>position)
	{
		position = _y_min;
	}
	if (_y_max-_y_page<position)
	{
		position = _y_max-_y_page;
	}

		
	_y = position;


	update_yscroll();
}

int view_scroll_helper::get_view_xoffset (void)
{
	if (_contents_cx<_window_cx)
	{
		return static_cast<int>(-_view_xoffset);
	}

	return static_cast<int>(_x);
}

int view_scroll_helper::get_view_yoffset (void)
{
	if (_contents_cy<_window_cy)
	{
		return static_cast<int>(-_view_yoffset);
	}

	return static_cast<int>(_y);
}


