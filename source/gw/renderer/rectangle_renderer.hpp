#ifndef INCLUDED__CX__GW__RENDERER__RECTANGLE_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__RECTANGLE_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_renderer.hpp
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
// Class: rectangle_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_renderer : public renderer
{
private:
	rectangle_t _rectangle;

	color_t     _fill_color;

	color_t     _line_color;
	cx::float_t _line_width;
	
	cx::uint_t  _line_dash_style;

public:
	rectangle_renderer();
	virtual ~rectangle_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_rectangle (rectangle_t v);

	void set_fill_color (color_t v);

	void set_line_width (cx::float_t v);
	void set_line_color (color_t     v);

	void set_line_dash_style(cx::uint_t v = DashStyleDot);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


