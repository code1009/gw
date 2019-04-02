/////////////////////////////////////////////////////////////////////////////
//
// File: window_event_handler.cpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//
// Headers
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define CX_GW_WINDOW_EVENT_HANDLER_MOUSE_DBCLICK_TIME 700u



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window_event_handler::window_event_handler() :
	_model(CX_NULL_POINTER)
{
	_window_mouse_capture_enabled = true;
	_window_mouse_captured = false;

	_widget_mouse_clicked_time = 0u;

	_mouse_pressed_widget   = CX_NULL_POINTER;
	_mouse_released_widget  = CX_NULL_POINTER;
	_mouse_clicked_widget   = CX_NULL_POINTER;
	_mouse_dbclicked_widget = CX_NULL_POINTER;
	_mouse_hover_widget     = CX_NULL_POINTER;
	_mouse_dragging_widget  = CX_NULL_POINTER;
}

window_event_handler::~window_event_handler()
{
}

//===========================================================================
model* window_event_handler::get_model (void)
{
	return _model;
}

void window_event_handler::set_model (model* model)
{
	_model = model;
}

//===========================================================================
void window_event_handler::on_update_widget(void)
{
	if (false==get_model()->get_widget()->is_in_collection(_mouse_pressed_widget  )){_mouse_pressed_widget  =CX_NULL_POINTER;}
	if (false==get_model()->get_widget()->is_in_collection(_mouse_released_widget )){_mouse_released_widget =CX_NULL_POINTER;}
	if (false==get_model()->get_widget()->is_in_collection(_mouse_clicked_widget  )){_mouse_clicked_widget  =CX_NULL_POINTER;}
	if (false==get_model()->get_widget()->is_in_collection(_mouse_dbclicked_widget)){_mouse_dbclicked_widget=CX_NULL_POINTER;}
	if (false==get_model()->get_widget()->is_in_collection(_mouse_hover_widget    )){_mouse_hover_widget    =CX_NULL_POINTER;}
	if (false==get_model()->get_widget()->is_in_collection(_mouse_dragging_widget )){_mouse_dragging_widget =CX_NULL_POINTER;}
}

//===========================================================================
cx::bool_t window_event_handler::get_window_mouse_capture_enabled (void)
{
	return _window_mouse_capture_enabled;
}

void window_event_handler::set_window_mouse_capture_enabled (cx::bool_t enabled)
{
	_window_mouse_capture_enabled = enabled;

	if (false==enabled)
	{
		release_window_mouse_capture();
	}
}

void window_event_handler::set_window_mouse_capture(HWND hwnd)
{
	if ( get_window_mouse_capture_enabled() )
	{
		_window_mouse_captured = true;
		::SetCapture(hwnd);
	}
}

void window_event_handler::release_window_mouse_capture(void)
{
	if (_window_mouse_captured)
	{
		::ReleaseCapture();
		_window_mouse_captured = false;
	}		
}

void window_event_handler::on_windows_message (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CPoint ptMouse((short)LOWORD(lParam), (short)HIWORD(lParam));
	UINT   uMouseFlag = wParam;
	WORD   fwKeys     = LOWORD(wParam);
	SHORT  zDelta     = HIWORD(wParam);

	mouse_event e;


	e._code  = EC_MOUSE_MOVE;
	e._point = get_model()->get_view()->viewport_window_to_world(ptMouse.x, ptMouse.y);

	e._shift_key_pressed = fwKeys & MK_SHIFT   ? true : false;
	e._ctrl_key_pressed  = fwKeys & MK_CONTROL ? true : false;


	// 메세지 발생순서
	// WM_LBUTTONDOWN, WM_LBUTTONUP, WM_LBUTTONDBLCLK, and WM_LBUTTONUP
	switch (uMsg)
	{
		//-----------------------------------------------------------------------
	case WM_MOUSEMOVE:
//		CX_DEBUG_TRACEF(TW_THISCODE, "WM_MOUSEMOVE: %d %d", ptMouse.x, ptMouse.y);
		break;

	case WM_MOUSELEAVE:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_MOUSELEAVE: %d %d", ptMouse.x, ptMouse.y);
		break;

		//-----------------------------------------------------------------------
	case WM_LBUTTONDBLCLK:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_LBUTTONDBLCLK: %d %d", ptMouse.x, ptMouse.y);
		break;

	case WM_LBUTTONDOWN:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_LBUTTONDOWN: %d %d", ptMouse.x, ptMouse.y);
		set_window_mouse_capture(hWnd);
		e._code = EC_MOUSE_LBUTTON_DOWN;
		break;

	case WM_LBUTTONUP:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_LBUTTONUP: %d %d", ptMouse.x, ptMouse.y);
		release_window_mouse_capture();
		e._code = EC_MOUSE_LBUTTON_UP;
		break;

		//-----------------------------------------------------------------------
	case WM_RBUTTONDBLCLK:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_RBUTTONDBLCLK: %d %d", ptMouse.x, ptMouse.y);
		break;

	case WM_RBUTTONDOWN:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_RBUTTONDOWN: %d %d", ptMouse.x, ptMouse.y);
		break;

	case WM_RBUTTONUP:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_RBUTTONUP: %d %d", ptMouse.x, ptMouse.y);
		break;

		//-----------------------------------------------------------------------
	case WM_MOUSEWHEEL:
		CX_DEBUG_TRACEF(TW_THISCODE, "WM_MOUSEWHEEL: %d %d", ptMouse.x, ptMouse.y);

		//-------------------------------------------------------------------
		switch (fwKeys)
		{
		case MK_LBUTTON:
			break;
		case MK_RBUTTON:
			break;
		case MK_MBUTTON:
			break;
		case MK_SHIFT:
			break;
		case MK_CONTROL:
			break;
		case MK_XBUTTON1:
			break;
		case MK_XBUTTON2:
			break;
		}

		break;

	default:
		e._code = EC_NONE;
		break;
	}

	if (EC_NONE != e._code)
	{
		on_event(&e);
	}
}

//===========================================================================
void window_event_handler::on_event (event* e)
{
	switch (e->_code)
	{
	case EC_MOUSE_MOVE        : on_mouse_move        ( cx_gw_dynamic_cast<mouse_event*>(e) ); break;
	case EC_MOUSE_LBUTTON_DOWN: on_mouse_lbutton_down( cx_gw_dynamic_cast<mouse_event*>(e) ); break;
	case EC_MOUSE_LBUTTON_UP  : on_mouse_lbutton_up  ( cx_gw_dynamic_cast<mouse_event*>(e) ); break;

	default:
		break;
	}
}

//===========================================================================
void window_event_handler::on_mouse_move (mouse_event* e)
{
	notify_mouse_move(e);


	widget* w;


	w = get_model()->get_widget()->find(e->_point);


	if (_mouse_pressed_widget)
	{
		if (_mouse_dragging_widget == _mouse_pressed_widget)
		{
			notify_widget_mouse_dragging(_mouse_dragging_widget, e);
		}
		else
		{
			_mouse_dragging_widget = CX_NULL_POINTER;
		}
	}
	else
	{
		_mouse_dragging_widget = CX_NULL_POINTER;
	}


	if (_mouse_hover_widget != w)
	{
		if (_mouse_hover_widget)
		{
			notify_widget_mouse_leave(_mouse_hover_widget, e);
		}

		_mouse_hover_widget = w;

		if (_mouse_hover_widget)
		{
			notify_widget_mouse_hover(_mouse_hover_widget, e);
		}
	}
}

void window_event_handler::on_mouse_lbutton_down (mouse_event* e)
{
	notify_mouse_lbutton_down(e);


	widget* w;

	
	w = get_model()->get_widget()->find(e->_point);


	_mouse_pressed_widget = w;


	if (_mouse_pressed_widget)
	{
		notify_widget_mouse_pressed(_mouse_pressed_widget, e);
	}


	_mouse_dragging_widget = _mouse_pressed_widget;
}

void window_event_handler::on_mouse_lbutton_up (mouse_event* e)
{
	_mouse_dragging_widget = CX_NULL_POINTER;


	notify_mouse_lbutton_up(e);


	widget* w;

	
	CX_DEBUG_TRACEF (TW_THISCODE, "begin");
	w = get_model()->get_widget()->find(e->_point);
	CX_DEBUG_TRACEF (TW_THISCODE, "end");
	
	_mouse_released_widget = w;

	
	if (_mouse_pressed_widget)
	{
		notify_widget_mouse_released(_mouse_pressed_widget, e);
	}


	if (_mouse_pressed_widget != _mouse_released_widget)
	{
		if (_mouse_released_widget)
		{
			notify_widget_mouse_released(_mouse_released_widget, e);
		}
	}


	if (_mouse_pressed_widget == _mouse_released_widget)
	{
		_mouse_clicked_widget = _mouse_released_widget;
		if (_mouse_clicked_widget)
		{
			notify_widget_mouse_clicked(_mouse_clicked_widget, e);
		}
	}


	if (_mouse_dbclicked_widget==_mouse_clicked_widget)
	{
		if (_mouse_dbclicked_widget)
		{
			if (GetTickCount() < _widget_mouse_clicked_time + CX_GW_WINDOW_EVENT_HANDLER_MOUSE_DBCLICK_TIME)
			{
				notify_widget_mouse_dbclicked(_mouse_dbclicked_widget, e);
			}
		}
	}


	if (CX_NULL_POINTER!=_mouse_clicked_widget)
	{
		_widget_mouse_clicked_time = GetTickCount();
	}


	_mouse_dbclicked_widget = _mouse_clicked_widget;
}

//===========================================================================
void window_event_handler::notify_mouse_move (mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (CX_NULL_POINTER!=m)
	{
		m->on_event(e);
	}
}

void window_event_handler::notify_mouse_lbutton_down (mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (CX_NULL_POINTER!=m)
	{
		m->on_event(e);
	}
}

void window_event_handler::notify_mouse_lbutton_up (mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (CX_NULL_POINTER!=m)
	{
		m->on_event(e);
	}
}

//===========================================================================
void window_event_handler::notify_widget_mouse_pressed (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_PRESSED;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_released (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_RELEASED;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;
	

	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_clicked (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_CLICKED;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_dbclicked (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;

	
	we._code              = EC_WIDGET_MOUSE_DBCLICKED;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_hover (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_HOVER;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_leave (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_LEAVE;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}

void window_event_handler::notify_widget_mouse_dragging (widget* w, mouse_event* e)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	widget_event_handler* weh;


	weh = m->get_widget_event_handler()->find(w);



	widget_mouse_event we;


	we._code              = EC_WIDGET_MOUSE_DRAGGING;
	we._point             = e->_point;
	we._shift_key_pressed = e->_shift_key_pressed;
	we._ctrl_key_pressed  = e->_ctrl_key_pressed ;
	we._widget            = w;


	if (CX_NULL_POINTER!=weh)
	{
		weh->on_event(&we);
	}

	if (CX_NULL_POINTER!=m)
	{
		m->on_event(&we);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}


