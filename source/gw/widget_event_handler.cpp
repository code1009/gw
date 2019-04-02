/////////////////////////////////////////////////////////////////////////////
//
// File: widget_event_handler.cpp
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
//===========================================================================
widget_event_handler::widget_event_handler()
{
}

widget_event_handler::~widget_event_handler()
{
}

//===========================================================================
void widget_event_handler::on_event (event* e)
{
	switch (e->_code)
	{
	case EC_WIDGET_MOUSE_PRESSED  : on_mouse_pressed  (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_RELEASED : on_mouse_released (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_CLICKED  : on_mouse_clicked  (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_DBCLICKED: on_mouse_dbclicked(cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_HOVER    : on_mouse_hover    (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_LEAVE    : on_mouse_leave    (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;
	case EC_WIDGET_MOUSE_DRAGGING : on_mouse_dragging (cx_gw_dynamic_cast<widget_mouse_event*>(e)); break;

	default:
		break;
	}
}

//===========================================================================
void widget_event_handler::on_mouse_pressed  (widget_mouse_event* e) {}
void widget_event_handler::on_mouse_released (widget_mouse_event* e) {}
void widget_event_handler::on_mouse_clicked  (widget_mouse_event* e) {}
void widget_event_handler::on_mouse_dbclicked(widget_mouse_event* e) {}
void widget_event_handler::on_mouse_hover    (widget_mouse_event* e) {}
void widget_event_handler::on_mouse_leave    (widget_mouse_event* e) {}
void widget_event_handler::on_mouse_dragging (widget_mouse_event* e) {}



/////////////////////////////////////////////////////////////////////////////
//
// Class: named_widget_event_handler_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
named_widget_event_handler_collection::named_widget_event_handler_collection()
{
}

named_widget_event_handler_collection::~named_widget_event_handler_collection()
{
}

//===========================================================================
named_widget_event_handler_pointer_container_t& named_widget_event_handler_collection::get_container(void)
{
	return _container;
}

void named_widget_event_handler_collection::delete_container (void)
{
	named_widget_event_handler_pointer_container_t::iterator i;
	widget_event_handler* weh;
	

	for (i =get_container().begin(); 
	     i!=get_container().end(); 
	     i++)
	{
		weh = (*i).second;

		delete weh;
	}

	get_container().clear();
}

//===========================================================================
widget_event_handler* named_widget_event_handler_collection::find (widget* w)
{
	std::string name = w->get_class();


	named_widget_event_handler_pointer_container_t::iterator i;
	widget_event_handler* weh;


	weh = CX_NULL_POINTER;


	i = get_container().find(name);
	if (i!=get_container().end())
	{
		weh = (*i).second;
	}

	return weh;
}

cx::bool_t named_widget_event_handler_collection::add (std::string name, widget_event_handler* weh)
{
	named_widget_event_handler_pointer_container_t::iterator i;


	i = get_container().find(name);
	if (i != get_container().end())
	{
		return false;
	}


	get_container()[name] = weh;

	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================

}
