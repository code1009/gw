/////////////////////////////////////////////////////////////////////////////
//
// File: model.cpp
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
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: model
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
model::model()
{
	_window  = CX_NULL_POINTER;
	_graphic = CX_NULL_POINTER;
}

model::~model()
{
}

//===========================================================================
window_t model::get_window (void)
{
	return _window;
}

void model::set_window (window_t window)
{
	_window = window;
}

//===========================================================================
graphic_t model::get_graphic (void)
{
	return _graphic;
}

void model::set_graphic (graphic_t graphic)
{
	_graphic = graphic;
}

resource* model::get_resource (void)
{
	return &_resource;
}

view* model::get_view (void)	
{
	return &_view;
}

window_event_handler* model::get_window_event_handler (void)
{
	return &_window_event_handler;
}

//===========================================================================
named_widget_event_handler_collection* model::get_widget_event_handler (void)
{
	return &_widget_event_handler ;
}

widget_collection* model::get_widget (void)
{
	return &_widget;
}

//===========================================================================
cx::bool_t model::create (widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	get_resource()->set_model(this);
	get_view()->set_model(this);
	get_window_event_handler()->set_model(this);


	//-----------------------------------------------------------------------
	widget_entry_pointer_container_t::iterator i;
	
	widget_entry*         we;
	std::string           wc;
	widget_event_handler* weh;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);

		wc  = we->get_widget_class();
		weh = we->get_widget_event_handler_factory()->create_instance();

		if (false == get_widget_event_handler()->add(wc, weh))
		{
			delete weh;

			return false;
		}
	}


	//-----------------------------------------------------------------------
	get_widget()->set_model(this);
	get_widget()->initialize();

	return true;
}

void model::destroy (void)
{
	get_widget_event_handler()->delete_container();

	get_resource()->delete_container();
}

//===========================================================================
void model::set_redraw (void)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_window());

//	:: InvalidateRect (get_window(), NULL, FALSE);
	RedrawWindow(get_window(), NULL, NULL, RDW_INVALIDATE);
}

void model::set_redraw (widget* widget)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_window());

///	:: InvalidateRect (get_window(), NULL, FALSE);
//	:: UpdateWindow(get_window());
	RedrawWindow(get_window(), NULL, NULL, RDW_INVALIDATE);
}

//===========================================================================
void model::draw (void)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_graphic());

	get_widget()->draw();
}

//===========================================================================
void model::on_event (event* e)
{
	switch (e->_code)
	{
	case EC_MOUSE_MOVE             : on_mouse_move            (cx_gw_dynamic_cast<mouse_event*>(e));           break;
	case EC_MOUSE_LBUTTON_DOWN     : on_mouse_lbutton_down    (cx_gw_dynamic_cast<mouse_event*>(e));           break;
	case EC_MOUSE_LBUTTON_UP       : on_mouse_lbutton_up      (cx_gw_dynamic_cast<mouse_event*>(e));           break;

	case EC_MOUSE_DRAG_ENTER       : on_mouse_drag_enter      (cx_gw_dynamic_cast<mouse_drag_drop_event*>(e)); break;
	case EC_MOUSE_DRAG_LEAVE       : on_mouse_drag_leave      (cx_gw_dynamic_cast<mouse_drag_drop_event*>(e)); break;
	case EC_MOUSE_DRAG_OVER        : on_mouse_drag_over       (cx_gw_dynamic_cast<mouse_drag_drop_event*>(e)); break;
	case EC_MOUSE_DROP             : on_mouse_drop            (cx_gw_dynamic_cast<mouse_drag_drop_event*>(e)); break;

	case EC_WIDGET_MOUSE_PRESSED   : on_widget_mouse_pressed  (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_RELEASED  : on_widget_mouse_released (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_CLICKED   : on_widget_mouse_clicked  (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_DBCLICKED : on_widget_mouse_dbclicked(cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_HOVER     : on_widget_mouse_hover    (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_LEAVE     : on_widget_mouse_leave    (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;
	case EC_WIDGET_MOUSE_DRAGGING  : on_widget_mouse_dragging (cx_gw_dynamic_cast<widget_mouse_event*>(e));    break;

	default:
		break;
	}
}

void model::on_mouse_move         (mouse_event* e) {}
void model::on_mouse_lbutton_down (mouse_event* e) {}
void model::on_mouse_lbutton_up   (mouse_event* e) {}

void model::on_mouse_drag_enter (mouse_drag_drop_event* e) {}
void model::on_mouse_drag_over  (mouse_drag_drop_event* e) {}
void model::on_mouse_drag_leave (mouse_drag_drop_event* e) {}
void model::on_mouse_drop       (mouse_drag_drop_event* e) {}

void model::on_widget_mouse_pressed  (widget_mouse_event* e) {}
void model::on_widget_mouse_released (widget_mouse_event* e) {}
void model::on_widget_mouse_clicked  (widget_mouse_event* e) {}
void model::on_widget_mouse_dbclicked(widget_mouse_event* e) {}
void model::on_widget_mouse_hover    (widget_mouse_event* e) {}
void model::on_widget_mouse_leave    (widget_mouse_event* e) {}
void model::on_widget_mouse_dragging (widget_mouse_event* e) {}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
