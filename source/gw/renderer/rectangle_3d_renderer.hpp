#ifndef INCLUDED__CX__GW__RENDERER__RECTANGLE_3D_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__RECTANGLE_3D_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_3d_renderer.hpp
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
// Class: rectangle_3d_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_3d_renderer : public renderer
{
private:
	rectangle_t _rectangle;

	color_t     _fill_color;
	
	cx::float_t _3d_width;
	color_t     _3d_light_color;
	color_t     _3d_shadow_color;

	cx::bool_t  _3d_pressed;

public:
	rectangle_3d_renderer();
	virtual ~rectangle_3d_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_rectangle (rectangle_t v);

	void set_fill_color (color_t v);

	void set_3d_width               (cx::float_t v);
	void set_3d_light_color         (color_t v);
	void set_3d_shadow_color        (color_t v);
	void set_3d_color_by_fill_color (void);

	void set_3d_pressed (cx::bool_t v);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


