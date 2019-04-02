/////////////////////////////////////////////////////////////////////////////
//
// File: wh_layout.cpp
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
//
// Class: wh_layout
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
wh_layout::wh_layout(cx::bool_t vertical):
	_vertical(vertical)
{
	_item_xsize = 100.0f;
	_item_ysize =  20.0f;

	_padding_xsize = 2.0f;
	_padding_ysize = 2.0f;

	_cursor._x = 0.0f;
	_cursor._y = 0.0f;
}

wh_layout::~wh_layout()
{
}

//===========================================================================
void wh_layout::begin (point_t start, coordinates_t padding_xsize, coordinates_t padding_ysize)
{
	set_padding_size(padding_xsize, padding_ysize);

	_start = start;

	_cursor._x = _start._x;
	_cursor._y = _start._y;

	_bounds._p0 = _start;

	_cursor._x += _padding_xsize;
	_cursor._y += _padding_ysize;
}

void wh_layout::end(void)
{
	_bounds._p1 = _end;
}

rectangle wh_layout::get_bounds (void)
{
	return _bounds;
}

coordinates_t wh_layout::get_item_xsize(void) 
{
	return _item_xsize;
}

coordinates_t wh_layout::get_item_ysize(void) 
{
	return _item_ysize;
}

coordinates_t wh_layout::get_padding_xsize(void) 
{
	return _padding_xsize;
}

coordinates_t wh_layout::get_padding_ysize(void) 
{
	return _padding_xsize;
}

void wh_layout::set_padding_size (coordinates_t cx, coordinates_t cy)
{
	_padding_xsize = cx; 
	_padding_ysize = cy;
}

void wh_layout::set_item_size (coordinates_t cx, coordinates_t cy)
{
	_item_xsize = cx; 
	_item_ysize = cy;
}

void wh_layout::add_control (control* wc)
{
	point_t p0;
	point_t p1;


	p0 = _cursor;
	p1._x = p0._x + _item_xsize - 1.0f;
	p1._y = p0._y + _item_ysize - 1.0f;
	
	if (_vertical)
	{
//		_cursor._x += _item_xsize;
		_cursor._y += _item_ysize;

//		_cursor._x += _padding_xsize;
		_cursor._y += _padding_ysize;

//		_cursor._y ++;
	}
	else
	{
		_cursor._x += _item_xsize;
//		_cursor._y += _item_ysize;

		_cursor._x += _padding_xsize;
//		_cursor._y += _padding_ysize;

//		_cursor._x ++;
	}

	_end._x = max( _end._x, (p1._x + _padding_xsize) );
	_end._y = max( _end._y, (p1._y + _padding_ysize) );

	wc->set_bounds( rectangle_t(p0,p1) );
}

void wh_layout::separate (void)
{
	if (_vertical)
	{
		_cursor._x += (_item_xsize  + _padding_xsize);
		_cursor._y  = (_start._y    + _padding_ysize);
	}
	else
	{
		_cursor._x  = (_start._x    + _padding_xsize);
		_cursor._y += (_item_ysize  + _padding_ysize);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
