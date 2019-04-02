#ifndef INCLUDED__CX__GW__RENDERER__ROUND_RECTANGLE_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__ROUND_RECTANGLE_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: round_round_rectangle_renderer.hpp
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
// Class: round_rectangle_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class round_rectangle_renderer : public renderer
{
private:
	rectangle_t _rectangle;
	cx::float_t _radius;

	color_t     _fill_color;

	color_t     _line_color;
	cx::float_t _line_width;
	
	cx::uint_t  _line_dash_style;

public:
	round_rectangle_renderer();
	virtual ~round_rectangle_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_rectangle (rectangle_t v);
	void set_radius (cx::float_t radius);

	void set_fill_color (color_t v);

	void set_line_color (color_t     v);
	void set_line_width (cx::float_t v);

	void set_line_dash_style(cx::uint_t v = DashStyleDot);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


