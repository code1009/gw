#ifndef INCLUDED__CX__GW__RENDERER__ELLIPSE_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__ELLIPSE_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: ellipse_renderer.hpp
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
// Class: ellipse_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class ellipse_renderer : public renderer
{
private:
	rectangle_t _rectangle;

	color_t     _fill_color;

	color_t     _line_color;
	cx::float_t _line_width;
	
	cx::uint_t  _line_dash_style;

public:
	ellipse_renderer();
	virtual ~ellipse_renderer();

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


