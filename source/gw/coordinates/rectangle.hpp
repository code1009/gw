#ifndef INCLUDED__CX__GW__COORDINATES__RECTANGLE__HPP
#define INCLUDED__CX__GW__COORDINATES__RECTANGLE__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle.hpp
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
// Class: rectangle
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle
{
public:
	point _p0;
	point _p1;

public:
	rectangle();
	rectangle(coordinates_t p0_x, coordinates_t p0_y, coordinates_t p1_x, coordinates_t p1_y);
	rectangle(coordinates_t p1_x, coordinates_t p1_y);
	rectangle(point p0, point p1);
	rectangle(const rectangle& v);
//	virtual ~rectangle();

public:
	rectangle& operator =(const rectangle& rhs);

public:
	void set (const rectangle& v);
	void set (rectangle& v);
	void set (rectangle* v);
	void set (point& p0, point& p1);

	cx::bool_t is_point_in (point& p);

public:
	coordinates_t l (void);
	coordinates_t t (void);
	coordinates_t r (void);
	coordinates_t b (void);
	coordinates_t w (void);
	coordinates_t h (void);

	point lt (void);
	point rt (void);
	point lb (void);
	point rb (void);

public:
	void inflate(coordinates_t v);
	void inflate(coordinates_t w, coordinates_t h);

public:
	cx::bool_t operator== (const rectangle& v) const;
	cx::bool_t operator!= (const rectangle& v) const;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


