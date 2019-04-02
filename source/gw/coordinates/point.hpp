#ifndef INCLUDED__CX__GW__COORDINATES__POINT__HPP
#define INCLUDED__CX__GW__COORDINATES__POINT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: point.hpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





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
class point
{
public:
	coordinates_t _x;
	coordinates_t _y;

public:
	point();
	point(coordinates_t x, coordinates_t y);
	point(const point& v);
//	virtual ~point();

public:
	point& operator= (const point& rhs);

public:
	void set (const point& v);
	void set (point& v);
	void set (point* v);
	void set (coordinates_t x, coordinates_t y);

public:
	void offset(const point& v);
	void offset(coordinates_t x, coordinates_t y);

public:
	cx::bool_t is_zero (void);
	void       reset   (void);

public:
	cx::bool_t operator== (const point& v) const;
	cx::bool_t operator!= (const point& v) const;

public:
	void   operator+= (const point& v);
	void   operator-= (const point& v);
	point  operator-  (void) const;
	point  operator+  (const point& v) const;
	point  operator-  (const point& v) const;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


