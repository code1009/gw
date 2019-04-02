/////////////////////////////////////////////////////////////////////////////
//
// File: point.cpp
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



/////////////////////////////////////////////////////////////////////////////
//
// Class: point
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CX_GW_COORDINATES_API point::point()
{
	reset();
}

CX_GW_COORDINATES_API point::point(coordinates_t x, coordinates_t y)
{
	set(x,y);
}

CX_GW_COORDINATES_API point::point(const point& v)
{
	set(v);
}

/*
CX_GW_COORDINATES_API point::~point()
{
}
*/

//===========================================================================
CX_GW_COORDINATES_API point& point::operator= (const point& rhs)
{
	_x = rhs._x;
	_y = rhs._y;

	return *this;
}

//===========================================================================
CX_GW_COORDINATES_API void point::set (const point& v)
{
	_x = v._x;
	_y = v._y;
}

CX_GW_COORDINATES_API void point::set (point& v)
{
	_x = v._x;
	_y = v._y;
}

CX_GW_COORDINATES_API void point::set (point* v)
{
	CX_DEBUG_ASSERT (CX_NULL_POINTER!=v);


	_x = v->_x;
	_y = v->_y;
}

CX_GW_COORDINATES_API void point::set (coordinates_t x, coordinates_t y)
{
	_x = x;
	_y = y;
}

//===========================================================================
CX_GW_COORDINATES_API void point::offset (const point& v)
{
	_x += v._x;
	_y += v._y;
}

CX_GW_COORDINATES_API void point::offset (coordinates_t x, coordinates_t y)
{
	_x += x;
	_y += y;
}

//===========================================================================
CX_GW_COORDINATES_API cx::bool_t point::is_zero (void)
{
	if ( (static_cast<coordinates_t>(0u)==_x) && 
	     (static_cast<coordinates_t>(0u)==_y) )
	{
		return true;
	}

	return false;
}

CX_GW_COORDINATES_API void point::reset (void)
{
	set(static_cast<coordinates_t>(0u), static_cast<coordinates_t>(0u));
}

//===========================================================================
CX_GW_COORDINATES_API cx::bool_t point::operator== (const point& v) const
{
	return (_x == v._x && _y == v._y);
}

CX_GW_COORDINATES_API cx::bool_t point::operator!= (const point& v) const
{
	return (_x != v._x || _y != v._y);
}

//===========================================================================
CX_GW_COORDINATES_API void point::operator+= (const point& v)
{
	_x += v._x;
	_y += v._y;
}

CX_GW_COORDINATES_API void point::operator-= (const point& v)
{
	_x -= v._x;
	_y -= v._y;
}

CX_GW_COORDINATES_API point point::operator- (void) const
{
	return point(-_x, -_y);
}

CX_GW_COORDINATES_API point point::operator+ (const point& v) const
{
	return point(_x + v._x, _y + v._y);
}

CX_GW_COORDINATES_API point point::operator- (const point& v) const
{
	return point(_x - v._x, _y - v._y);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
