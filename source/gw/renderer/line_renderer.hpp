#ifndef INCLUDED__CX__GW__RENDERER__LINE_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__LINE_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: line_renderer.hpp
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
// Class: line_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class line_renderer : public renderer
{
private:
	point_t _p0;
	point_t _p1;

	color_t     _line_color;
	cx::float_t _line_width;
	
	cx::uint_t  _line_dash_style;

public:
	line_renderer();
	virtual ~line_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_point (point_t p0, point_t p1);

	void set_fill_color (color_t v);

	void set_line_width (cx::float_t v);
	void set_line_color (color_t     v);

	void set_line_dash_style(cx::uint_t v = DashStyleDot);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


