/////////////////////////////////////////////////////////////////////////////
//
// File: widget_event.cpp
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
widget_mouse_event::widget_mouse_event()
{
	_widget = CX_NULL_POINTER;
}

widget_mouse_event::widget_mouse_event(widget_mouse_event& v)
{
	_code = v._code;

	_point = v._point;
	_shift_key_pressed = v._shift_key_pressed;
	_ctrl_key_pressed  = v._ctrl_key_pressed ;

	_widget = v._widget;
}

widget_mouse_event::~widget_mouse_event()
{
}

widget_mouse_event& widget_mouse_event::operator= (const widget_mouse_event& rhs)
{
	_code = rhs._code;

	_point = rhs._point;
	_shift_key_pressed = rhs._shift_key_pressed;
	_ctrl_key_pressed  = rhs._ctrl_key_pressed ;

	_widget = rhs._widget;

	return *this;
}




////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
