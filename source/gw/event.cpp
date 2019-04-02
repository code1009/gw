/////////////////////////////////////////////////////////////////////////////
//
// File: event.cpp
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
event::event()
{
	_code = EC_NONE;
}

event::event(cx::uint_t code)
{
	_code = code;
}

event::event(event& v)
{
	_code = v._code;
}

event::~event()
{
}

event& event::operator= (const event& rhs)
{
	_code = rhs._code;

	return *this;
}

cx::uint_t event::get_code (void)
{
	return _code;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
mouse_event::mouse_event()
{
	_shift_key_pressed = false;
	_ctrl_key_pressed  = false;
}

mouse_event::mouse_event(mouse_event& v)
{
	_code = v._code;

	_point = v._point;
	_shift_key_pressed = v._shift_key_pressed;
	_ctrl_key_pressed  = v._ctrl_key_pressed ;
}

mouse_event::~mouse_event()
{
}

mouse_event& mouse_event::operator= (const mouse_event& rhs)
{
	_code = rhs._code;

	_point = rhs._point;
	_shift_key_pressed = rhs._shift_key_pressed;
	_ctrl_key_pressed  = rhs._ctrl_key_pressed ;

	return *this;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
mouse_drag_drop_event::mouse_drag_drop_event()
{
	_hglobal = NULL;
}

mouse_drag_drop_event::mouse_drag_drop_event(mouse_drag_drop_event& v)
{
	_code = v._code;

	_point = v._point;
	_shift_key_pressed = v._shift_key_pressed;
	_ctrl_key_pressed  = v._ctrl_key_pressed ;

	_hglobal = v._hglobal;
}

mouse_drag_drop_event::~mouse_drag_drop_event()
{
}

mouse_drag_drop_event& mouse_drag_drop_event::operator= (const mouse_drag_drop_event& rhs)
{
	_code = rhs._code;

	_point = rhs._point;
	_shift_key_pressed = rhs._shift_key_pressed;
	_ctrl_key_pressed  = rhs._ctrl_key_pressed ;

	_hglobal = rhs._hglobal;

	return *this;
}



////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
