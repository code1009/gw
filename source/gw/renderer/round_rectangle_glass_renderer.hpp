#ifndef INCLUDED__CX__GW__RENDERER__ROUND_RECTANGLE_GLASS_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__ROUND_RECTANGLE_GLASS_RENDERER__HPP

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
// Class: round_rectangle_glass_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class round_rectangle_glass_renderer : public renderer
{
private:
	rectangle_t _rectangle;

	color_t    _fill_background_color;
	color_t    _fill_glow_color      ;
	color_t    _fill_shine_color     ;
	cx::bool_t _fill_glow_opacity    ;
	cx::bool_t _fill_opacity         ;

public:
	round_rectangle_glass_renderer();
	virtual ~round_rectangle_glass_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_rectangle (rectangle_t v);

	void set_fill_background_color (color_t v);
	void set_fill_glow_color       (color_t v);
	void set_fill_shine_color      (color_t v);
	void set_fill_glow_opacity     (cx::bool_t v);
	void set_fill_opacity          (cx::bool_t v);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


