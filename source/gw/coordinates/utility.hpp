#ifndef INCLUDED__CX__GW__COORDINATES__UTILITY__HPP
#define INCLUDED__CX__GW__COORDINATES__UTILITY__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: utility.hpp
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
//===========================================================================
rectangle_t get_rectangle_ltrb(point_t& p0, point_t& p1);
rectangle_t get_rectangle_wh  (point_t& p, coordinates_t w, coordinates_t h);

//===========================================================================
void point_to_POINT (point_t* s, POINT* d);
void POINT_to_point (POINT* s, point_t* d);

//===========================================================================
void rectangle_to_RECT (rectangle_t* s, RECT* d);
void RECT_to_rectangle (RECT* s, rectangle_t* d);

//===========================================================================
RectF rectangle_to_RectF (rectangle_t& s);

//===========================================================================
rectangle_t point_container_to_rectangle   (point_container_t& point_container);
cx::bool_t is_point_container_on_rectangle (point_container_t& point_container, rectangle_t& on_rectangle);
cx::bool_t is_point_container_in_rectangle (point_container_t& point_container, rectangle_t& in_rectangle);
cx::bool_t is_rectangle_in_rectangle (rectangle_t& r, rectangle_t& in_rectangle);
cx::bool_t is_rectangle_on_rectangle (rectangle_t& r, rectangle_t& on_rectangle);

//===========================================================================
cx::bool_t is_point_on_line (point_t p, point_t p0, point_t p1, coordinates_t t);
point_t get_line_offset_point (point_t p0, point_t p1, coordinates_t d);
point_t get_line_center_point (point_t p0, point_t p1);
point_t rotate_point(point_t p0, point_t p, cx::double_t angle);
cx::double_t get_angle (point_t p0, point_t p1);
cx::bool_t is_point_on_polygon (point_t p, point_container_t& polygon);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


