/////////////////////////////////////////////////////////////////////////////
//
// File: control_default_widget_entry.cpp
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
#include "../header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{
namespace ctrl
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void add_default_widget_entry(widget_entry_collection* wec)
{
	wec->get_container().push_back( create_widget_entry<control       , control_event_handler       >("control"       ) );
	wec->get_container().push_back( create_widget_entry<led_button    , led_button_event_handler    >("led_button"    ) );
	wec->get_container().push_back( create_widget_entry<button        , button_event_handler        >("button"        ) );
	wec->get_container().push_back( create_widget_entry<blue_highlight, blue_highlight_event_handler>("blue_highlight") );
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
