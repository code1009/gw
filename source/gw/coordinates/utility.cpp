/////////////////////////////////////////////////////////////////////////////
//
// File: utility.cpp
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
//===========================================================================
CX_GW_COORDINATES_API rectangle_t get_rectangle_ltrb(point_t& p0, point_t& p1)
{
	rectangle_t r;

	point_t lt;
	point_t rb;

	
	if (p0._x < p1._x)
	{
		lt._x = p0._x;
		rb._x = p1._x;
	}
	else
	{
		lt._x = p1._x;
		rb._x = p0._x;
	}

	if (p0._y < p1._y)
	{
		lt._y = p0._y;
		rb._y = p1._y;
	}
	else
	{
		lt._y = p1._y;
		rb._y = p0._y;
	}

	r.set(lt,rb);

	return r;
}

rectangle_t get_rectangle_wh(point_t& p, coordinates_t w, coordinates_t h)
{
	rectangle_t r;


	r._p0.set(p._x - (w / 2.0f), p._y - (h / 2.0f));
	r._p1.set(p._x + (w / 2.0f), p._y + (h / 2.0f));

	return r;
}



//===========================================================================
CX_GW_COORDINATES_API void rectangle_to_RECT (rectangle_t* s, RECT* d)
{
	d->left   = (cx::int_t)(s->_p0._x);
	d->top    = (cx::int_t)(s->_p0._y);
	d->right  = (cx::int_t)(s->_p1._x);
	d->bottom = (cx::int_t)(s->_p1._y);
}

CX_GW_COORDINATES_API void RECT_to_rectangle (RECT* s, rectangle_t* d)
{
	d->_p0._x = (coordinates_t)(s->left  );
	d->_p0._y = (coordinates_t)(s->top   );
	d->_p1._x = (coordinates_t)(s->right );
	d->_p1._y = (coordinates_t)(s->bottom);
}



//===========================================================================
CX_GW_COORDINATES_API void point_to_POINT (point_t* s, POINT* d)
{
	d->x = (cx::int_t)(s->_x);
	d->y = (cx::int_t)(s->_y);
}

CX_GW_COORDINATES_API void POINT_to_point (POINT* s, point_t* d)
{
	d->_x = (coordinates_t)(s->x);
	d->_y = (coordinates_t)(s->y);
}



//===========================================================================
CX_GW_COORDINATES_API RectF rectangle_to_RectF (rectangle_t& s)
{
	RectF d(s.l(),s.t(),s.w(),s.h());


	return d;
}



//===========================================================================
CX_GW_COORDINATES_API rectangle_t point_container_to_rectangle (point_container_t& point_container)
{
	rectangle_t r;

	point min_point;
	point max_point;
	point p;

	if (!point_container.empty())
	{
		min_point = point_container[0];
		max_point = point_container[0];
	}

	
	point_container_t::iterator i;


	for (i=point_container.begin(); i!=point_container.end(); i++)
	{
		p = (*i);

		if (p._x < min_point._x)
		{
			min_point._x = p._x;
		}
		if (p._y < min_point._y)
		{
			min_point._y = p._y;
		}

		if (p._x > max_point._x)
		{
			max_point._x = p._x;
		}
		if (p._y > max_point._y)
		{
			max_point._y = p._y;
		}
	}


	r._p0 = min_point;
	r._p1 = max_point;

	return r;
}



//===========================================================================
static cx::bool_t is_point_in_rectangle_ltrb (point_t& p, rectangle_t& in_rectangle_ltrb)
{
	rectangle_t r;

	
	if
	(
		(in_rectangle_ltrb._p0._y <= p._y && p._y <= in_rectangle_ltrb._p1._y) &&
		(in_rectangle_ltrb._p0._x <= p._x && p._x <= in_rectangle_ltrb._p1._x) 
	)
	{
		return true;
	}

	return false;
}

CX_GW_COORDINATES_API cx::bool_t is_point_container_on_rectangle (point_container_t& point_container, rectangle_t& on_rectangle)
{
#if 0
	point_container_t::iterator i;
	point_t p;


	for (i=point_container.begin(); i!=point_container.end(); i++)
	{
		p = (*i);

		if (true==on_rectangle.is_point_in(p))
		{
			return true;
		}
	}

	return false;
#else
	point_container_t::iterator i;
	point_t p;

	rectangle_t on_rectangle_ltrb;


	on_rectangle_ltrb = get_rectangle_ltrb(on_rectangle._p0, on_rectangle._p1);

	for (i=point_container.begin(); i!=point_container.end(); i++)
	{
		p = (*i);

		if (true==is_point_in_rectangle_ltrb(p, on_rectangle_ltrb))
		{
			return true;
		}
	}

	return false;
#endif
}

CX_GW_COORDINATES_API cx::bool_t is_point_container_in_rectangle (point_container_t& point_container, rectangle_t& in_rectangle)
{
#if 0
	point_container_t::iterator i;
	point_t p;


	for (i=point_container.begin(); i!=point_container.end(); i++)
	{
		p = (*i);

		if (false==in_rectangle.is_point_in(p))
		{
			return false;
		}
	}

	return true;
#else
	point_container_t::iterator i;
	point_t p;

	rectangle_t in_rectangle_ltrb;


	in_rectangle_ltrb = get_rectangle_ltrb(in_rectangle._p0, in_rectangle._p1);

	for (i=point_container.begin(); i!=point_container.end(); i++)
	{
		p = (*i);

		if (false==is_point_in_rectangle_ltrb(p, in_rectangle_ltrb))
		{
			return false;
		}
	}

	return true;
#endif
}

CX_GW_COORDINATES_API cx::bool_t is_rectangle_in_rectangle (rectangle_t& r, rectangle_t& in_rectangle)
{
#if 0
	if (false==in_rectangle.is_point_in(r.lt()))
	{
		return false;
	}

	if (false==in_rectangle.is_point_in(r.rt()))
	{
		return false;
	}

	if (false==in_rectangle.is_point_in(r.lb()))
	{
		return false;
	}

	if (false==in_rectangle.is_point_in(r.rb()))
	{
		return false;
	}

	return true;
#else
	rectangle_t r_ltrb;
	rectangle_t in_rectangle_ltrb;

	point_t r_lt;
	point_t r_rt;
	point_t r_lb;
	point_t r_rb;


	r_ltrb            = get_rectangle_ltrb(r._p0, r._p1);
	in_rectangle_ltrb = get_rectangle_ltrb(in_rectangle._p0, in_rectangle._p1);

	r_lt._x = r_ltrb._p0._x; r_lt._y = r_ltrb._p0._y;
	r_rt._x = r_ltrb._p1._x; r_rt._y = r_ltrb._p0._y;
	r_lb._x = r_ltrb._p0._x; r_lb._y = r_ltrb._p1._y;
	r_rb._x = r_ltrb._p1._x; r_rb._y = r_ltrb._p1._y;

	if (false==is_point_in_rectangle_ltrb(r_lt, in_rectangle_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(r_rt, in_rectangle_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(r_lb, in_rectangle_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(r_rb, in_rectangle_ltrb))
	{
		return false;
	}

	return true;
#endif
}

CX_GW_COORDINATES_API cx::bool_t is_rectangle_on_rectangle (rectangle_t& r, rectangle_t& on_rectangle)
{
#if 0
	if (true==on_rectangle.is_point_in(r.lt()))
	{
		return true;
	}

	if (true==on_rectangle.is_point_in(r.rt()))
	{
		return true;
	}

	if (true==on_rectangle.is_point_in(r.lb()))
	{
		return true;
	}

	if (true==on_rectangle.is_point_in(r.rb()))
	{
		return true;
	}


	if (true==r.is_point_in(on_rectangle.lt()))
	{
		return true;
	}

	if (true==r.is_point_in(on_rectangle.rt()))
	{
		return true;
	}

	if (true==r.is_point_in(on_rectangle.lb()))
	{
		return true;
	}

	if (true==r.is_point_in(on_rectangle.rb()))
	{
		return true;
	}


	return false;
#else
	rectangle_t r_ltrb;
	rectangle_t on_rectangle_ltrb;

	point_t r_lt;
	point_t r_rt;
	point_t r_lb;
	point_t r_rb;

	point_t on_rectangle_lt;
	point_t on_rectangle_rt;
	point_t on_rectangle_lb;
	point_t on_rectangle_rb;


	r_ltrb            = get_rectangle_ltrb(r._p0, r._p1);
	on_rectangle_ltrb = get_rectangle_ltrb(on_rectangle._p0, on_rectangle._p1);

	r_lt._x = r_ltrb._p0._x; r_lt._y = r_ltrb._p0._y;
	r_rt._x = r_ltrb._p1._x; r_rt._y = r_ltrb._p0._y;
	r_lb._x = r_ltrb._p0._x; r_lb._y = r_ltrb._p1._y;
	r_rb._x = r_ltrb._p1._x; r_rb._y = r_ltrb._p1._y;

	on_rectangle_lt._x = on_rectangle_ltrb._p0._x; on_rectangle_lt._y = on_rectangle_ltrb._p0._y;
	on_rectangle_rt._x = on_rectangle_ltrb._p1._x; on_rectangle_rt._y = on_rectangle_ltrb._p0._y;
	on_rectangle_lb._x = on_rectangle_ltrb._p0._x; on_rectangle_lb._y = on_rectangle_ltrb._p1._y;
	on_rectangle_rb._x = on_rectangle_ltrb._p1._x; on_rectangle_rb._y = on_rectangle_ltrb._p1._y;


	if (true==is_point_in_rectangle_ltrb(r_lt, on_rectangle_ltrb))
	{
		return true;
	}

	if (true==is_point_in_rectangle_ltrb(r_rt, on_rectangle_ltrb))
	{
		return true;
	}

	if (true==is_point_in_rectangle_ltrb(r_lb, on_rectangle_ltrb))
	{
		return true;
	}

	if (true==is_point_in_rectangle_ltrb(r_rb, on_rectangle_ltrb))
	{
		return true;
	}


	if (false==is_point_in_rectangle_ltrb(on_rectangle_lt, r_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(on_rectangle_rt, r_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(on_rectangle_lb, r_ltrb))
	{
		return false;
	}

	if (false==is_point_in_rectangle_ltrb(on_rectangle_rb, r_ltrb))
	{
		return false;
	}


	return false;
#endif
}

//===========================================================================
cx::bool_t is_point_on_line (point_t p, point_t p0, point_t p1, coordinates_t t)
{
	cx::float_t slope;
	coordinates_t x;
	coordinates_t y;


	slope = ( p1._y - p0._y ) / ( p1._x - p0._x );

	y = ( slope * p._x ) + ( p1._y - slope * p1._x );

	if ( ( (y-t) <= p._y ) && ( p._y <= (y+t) ) )
	{
		if ( ( p0._x <= p._x ) && ( p._x <= p1._x ) )
		{
			return true;
		}
		if ( ( p1._x <= p._x ) && ( p._x <= p0._x ) )
		{
			return true;
		}
	}


	slope = ( p1._x - p0._x ) / ( p1._y - p0._y );

	x = ( slope * p._y ) + ( p1._x - slope * p1._y );

	if ( ( (x-t) <= p._x ) && ( p._x <= (x+t) ) )
	{
		if ( ( p0._y <= p._y ) && ( p._y <= p1._y ) )
		{
			return true;
		}
		if ( ( p1._y <= p._y ) && ( p._y <= p0._y ) )
		{
			return true;
		}
	}


	return false;
}

//===========================================================================
static cx::float_t PI = 3.14159265358979323846f;

inline static cx::float_t degree_to_radian(cx::float_t angle)
{
	// 1 radian = 180 / pi

	// 2*pi radian = 360  degree
	// radian = pi / 180 * degree
	// degree = 180 / pi * radian

	return PI * angle / 180.0f;
}

inline static cx::float_t radian_to_degree(cx::float_t angle)
{
	return angle * (180.0f / PI);
}

inline static cx::bool_t is_negative_infinity (cx::double_t v)
{
	int f;


	f = _fpclass(v);
	if (f&_FPCLASS_NINF)
	{
		return true;
	}

	return false;
}

inline static cx::bool_t is_positive_infinity (cx::double_t v)
{
	int f;


	f = _fpclass(v);
	if (f&_FPCLASS_PINF)
	{
		return true;
	}

	return false;
}

inline static cx::bool_t is_infinity (cx::double_t v)
{
	int f;


	f = _fpclass(v);
	if (f&_FPCLASS_NINF)
	{
		return true;
	}
	if (f&_FPCLASS_PINF)
	{
		return true;
	}

	return false;
}

inline static cx::bool_t is_nan (cx::double_t v)
{
	int f;


	f = _fpclass(v);
	if (f&_FPCLASS_SNAN)
	{
		return true;
	}
	if (f&_FPCLASS_QNAN)
	{
		return true;
	}

	return false;
}

//===========================================================================
point_t get_line_offset_point (point_t p0, point_t p1, coordinates_t d)
{
	point_t p;

	coordinates_t xLength;
	coordinates_t yLength;
	cx::float_t  slope;
	cx::double_t angle;

	coordinates_t x = 0;
	coordinates_t y = 0;

			
	xLength = p1._x - p0._x;
	yLength = p1._y - p0._y; 
	slope   = yLength/xLength;

	if      (is_negative_infinity(slope))
	{
		x = 0.0F;
		y = -d;
	}
	else if (is_positive_infinity(slope))
	{
		x = 0.0F;
		y = d;
	}
	else if (is_nan(slope))
	{
		x = p0._x;
		y = p0._y;
	}
	else
	{
		angle = std::atan (slope);

		x = (coordinates_t)(std::cos(angle)*d);
		y = (coordinates_t)(std::sin(angle)*d);

		if (p0._x > p1._x)
		{
			x= x*-1.0F; 
			y= y*-1.0F; 
		}
	}

	p._x = p0._x + x;
	p._y = p0._y + y;

	return p;
}

point_t get_line_center_point (point_t p0, point_t p1)
{
	point_t p;

	cx::float_t slope;

	coordinates_t x = 0;
	coordinates_t y = 0;

			
	slope = ( p1._y - p0._y ) / ( p1._x - p0._x );
			

	x = p0._x + (p1._x - p0._x)/2.0F;

	p._x = x;

	
	if ( is_infinity(slope) )
	{
		y = p0._y + (p1._y - p0._y)/2.0F;
	}
	else if ( is_nan(slope) )
	{
		y = p0._y;
	}
	else
	{
		y = ( slope * p._x ) + ( p1._y - slope * p1._x );
	}


	p._y = y;

	return p;
}

point_t rotate_point(point_t p0, point_t p, cx::double_t angle)
{
	// u = 기준점 X
	// v = 기준점 Y
	// x' = (x-u)*  cos(a) + (y-v)*sin(a) + u;
	// y' = (x-u)* -sin(a) + (y-v)*cos(a) + v;
			
	/*
		* OpenGl 좌표계
	point_t r;


	r._x = (coordinates_t)(  (p._x-p0._x)*(  std::cos(angle) ) + (p._y-p0._y)*(std::sin(angle)) + p0._x  );
	r._y = (coordinates_t)(  (p._x-p0._x)*( -std::sin(angle) ) + (p._y-p0._y)*(std::cos(angle)) + p0._y  );
	*/

	point_t r;


	r._x = (coordinates_t)(  (p._x-p0._x)*(  std::cos(angle) ) - (p._y-p0._y)*(std::sin(angle)) + p0._x  );
	r._y = (coordinates_t)(  (p._x-p0._x)*(  std::sin(angle) ) + (p._y-p0._y)*(std::cos(angle)) + p0._y  );

	return r;
}

cx::double_t get_angle (point_t p0, point_t p1)
{
	cx::double_t dx = p1._x - p0._x;
	cx::double_t dy = p1._y - p0._y;


	return (cx::double_t) std::atan2(dy, dx);
}

cx::bool_t is_point_on_polygon (point_t p, point_container_t& polygon)
{
	// http://stackoverflow.com/questions/217578/point-in-polygon-aka-hit-test
	// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
	// http://msdn.microsoft.com/en-us/library/ms969920.aspx
			
	cx::size_t polygon_point_size;


	polygon_point_size = polygon.size();
	if ( polygon.empty() )
	{
		return false;
	}

	coordinates_t min_x = polygon[ 0 ]._x;
	coordinates_t max_x = polygon[ 0 ]._x;
	coordinates_t min_y = polygon[ 0 ]._y;
	coordinates_t max_y = polygon[ 0 ]._y;

	point_t q;
	cx::size_t i;
	cx::size_t j;


	for (i=1; i<polygon_point_size; i++)
	{
		q     = polygon[ i ];
		/*
		min_x = std::min( q._x, min_x );
		max_x = std::max( q._x, max_x );
		min_y = std::min( q._y, min_y );
		max_y = std::max( q._y, max_y );
		*/
		min_x = min( q._x, min_x );
		max_x = max( q._x, max_x );
		min_y = min( q._y, min_y );
		max_y = max( q._y, max_y );
	}

	if ( p._x < min_x || p._x > max_x || p._y < min_y || p._y > max_y )
	{
		return false;
	}


	cx::bool_t inside = false;


	for (i = 0, j = polygon_point_size - 1 ; i <polygon_point_size ; j = i++ )
	{
		if (
			
				( polygon[ i ]._y > p._y ) != ( polygon[ j ]._y > p._y )
			&&
				p._x 
				<
					( polygon[ j ]._x - polygon[ i ]._x )
					* 
					( p._y - polygon[ i ]._y ) 
					/ 
					( polygon[ j ]._y - polygon[ i ]._y ) 
					+ 
					polygon[ i ]._x 
				
			)
		{
			inside = !inside;
		}
	}

	return inside;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
