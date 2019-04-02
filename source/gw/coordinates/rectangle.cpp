/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle.cpp
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
// Class: rectangle
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CX_GW_COORDINATES_API rectangle::rectangle()
{
	_p0.reset();
	_p1.reset();
}

CX_GW_COORDINATES_API rectangle::rectangle(coordinates_t p0_x, coordinates_t p0_y, coordinates_t p1_x, coordinates_t p1_y)
{
	_p0.set(p0_x, p0_y);
	_p1.set(p1_x, p1_y);
}

CX_GW_COORDINATES_API rectangle::rectangle(coordinates_t p1_x, coordinates_t p1_y)
{
	_p0.reset();
	_p1.set(p1_x, p1_y);
}

CX_GW_COORDINATES_API rectangle::rectangle(point p0, point p1)
{
	set (p0, p1);
}

CX_GW_COORDINATES_API rectangle::rectangle(const rectangle& v)
{
	set(v);
}

/*
CX_GW_COORDINATES_API rectangle::~rectangle()
{
}
*/

//===========================================================================
CX_GW_COORDINATES_API rectangle& rectangle::operator= (const rectangle& rhs)
{
	_p0 = rhs._p0;
	_p1 = rhs._p1;

	return *this;
}

//===========================================================================
CX_GW_COORDINATES_API void rectangle::set (const rectangle& v)
{
	_p0 = v._p0;
	_p1 = v._p1;
}

CX_GW_COORDINATES_API void rectangle::set (rectangle& v)
{
	_p0 = v._p0;
	_p1 = v._p1;
}

CX_GW_COORDINATES_API void rectangle::set (rectangle* v)
{
	CX_DEBUG_ASSERT (CX_NULL_POINTER != v);

	_p0 = v->_p0;
	_p1 = v->_p1;
}

CX_GW_COORDINATES_API void rectangle::set (point& p0, point& p1)
{
	_p0 = p0;
	_p1 = p1;
}


//===========================================================================
CX_GW_COORDINATES_API cx::bool_t rectangle::is_point_in (point& p)
{
	rectangle r;

	
	r = get_rectangle_ltrb(_p0, _p1);

	if
	(
		(r._p0._y <= p._y && p._y <= r._p1._y) &&
		(r._p0._x <= p._x && p._x <= r._p1._x) 
	)
	{
		return true;
	}

	return false;
}

CX_GW_COORDINATES_API coordinates_t rectangle::l (void)
{
	rectangle r;

	
	r = get_rectangle_ltrb(_p0, _p1);

	return r._p0._x;
}

CX_GW_COORDINATES_API coordinates_t rectangle::t (void)
{
	rectangle r;

	
	r = get_rectangle_ltrb(_p0, _p1);

	return r._p0._y;
}

CX_GW_COORDINATES_API coordinates_t rectangle::r (void)
{
	rectangle r;

	
	r = get_rectangle_ltrb(_p0, _p1);

	return r._p1._x;
}

CX_GW_COORDINATES_API coordinates_t rectangle::b (void)
{
	rectangle r;

	
	r = get_rectangle_ltrb(_p0, _p1);

	return r._p1._y;
}

CX_GW_COORDINATES_API coordinates_t rectangle::w (void)
{
	return r() - l();
}

CX_GW_COORDINATES_API coordinates_t rectangle::h (void)
{
	return b() - t();
}

CX_GW_COORDINATES_API point rectangle::lt (void)
{
	point p;


	p._x = l();
	p._y = t();

	return p;
}

CX_GW_COORDINATES_API point rectangle::rt (void)
{
	point p;


	p._x = r();
	p._y = t();

	return p;
}

CX_GW_COORDINATES_API point rectangle::lb (void)
{
	point p;


	p._x = l();
	p._y = b();

	return p;
}

CX_GW_COORDINATES_API point rectangle::rb (void)
{
	point p;


	p._x = r();
	p._y = b();

	return p;
}

CX_GW_COORDINATES_API void rectangle::inflate (coordinates_t v)
{
	_p0._x -= v;
	_p0._y -= v;

	_p1._x += v;
	_p1._y += v;
}

CX_GW_COORDINATES_API void rectangle::inflate(coordinates_t w, coordinates_t h)
{
	_p0._x -= w;
	_p0._y -= h;

	_p1._x += w;
	_p1._y += h;
}

//===========================================================================
CX_GW_COORDINATES_API cx::bool_t rectangle::operator== (const rectangle& v) const
{
	return (_p0 == v._p0 && _p1 == v._p1);
}

CX_GW_COORDINATES_API cx::bool_t rectangle::operator!= (const rectangle& v) const
{
	return (_p0 != v._p0 || _p1 != v._p1);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
