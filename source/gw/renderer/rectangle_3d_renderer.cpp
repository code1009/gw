/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_3d_renderer.cpp
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
rectangle_3d_renderer::rectangle_3d_renderer()
{
	_fill_color.set(0xEC, 0xEC, 0xEC);

	_3d_width        = 1.0f;
	_3d_light_color  = color_level(_fill_color, 2.00f);
	_3d_shadow_color = color_level(_fill_color, 0.50f);

	_3d_pressed      = false;
}

rectangle_3d_renderer::~rectangle_3d_renderer()
{
}

//===========================================================================
void rectangle_3d_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);


	if (!_fill_color.get_alpha_zero())
	{
		SolidBrush fill(Color(_fill_color.ARGB()));


		g->FillRectangle(&fill, r);
	}


	if (_3d_width>0.0f)
	{
		Pen _3d_light (Color(_3d_light_color .ARGB()), _3d_width);
		Pen _3d_shadow(Color(_3d_shadow_color.ARGB()), _3d_width);

		/*
		PointF lt(r.X          , r.Y           );
		PointF lb(r.X          , r.Y + r.Height);
		PointF rt(r.X + r.Width, r.Y           );
		PointF rb(r.X + r.Width, r.Y + r.Height);
		*/
		PointF lt(_rectangle.lt()._x, _rectangle.lt()._y);
		PointF lb(_rectangle.lb()._x, _rectangle.lb()._y);
		PointF rt(_rectangle.rt()._x, _rectangle.rt()._y);
		PointF rb(_rectangle.rb()._x, _rectangle.rb()._y);

		PointF p[3];


		if (_3d_pressed)
		{
			/*
			g->DrawLine(&_3d_shadow, lt, rt);
			g->DrawLine(&_3d_shadow, lt, lb);
			g->DrawLine(&_3d_light , rb, lb);
			g->DrawLine(&_3d_light , rb, rt);
			*/

			p[0] = lb;
			p[1] = lt;
			p[2] = rt;
			g->DrawLines(&_3d_shadow, p, 3);

			p[0] = rt;
			p[1] = rb;
			p[2] = lb;
			g->DrawLines(&_3d_light, p, 3);
		}
		else
		{
			/*
			g->DrawLine(&_3d_light , lt, rt);
			g->DrawLine(&_3d_light , lt, lb);
			g->DrawLine(&_3d_shadow, rb, lb);
			g->DrawLine(&_3d_shadow, rb, rt);
			*/

			p[0] = lb;
			p[1] = lt;
			p[2] = rt;
			g->DrawLines(&_3d_light, p, 3);

			p[0] = rt;
			p[1] = rb;
			p[2] = lb;
			g->DrawLines(&_3d_shadow, p, 3);
		}
	}
}


//===========================================================================
void rectangle_3d_renderer::set_rectangle (rectangle_t v)
{
	_rectangle = v;
}

void rectangle_3d_renderer::set_fill_color (color_t v)
{
	_fill_color = v;
}

void rectangle_3d_renderer::set_3d_width (cx::float_t v)
{
	_3d_width = v;
}

void rectangle_3d_renderer::set_3d_light_color (color_t v)
{
	_3d_light_color = v;
}

void rectangle_3d_renderer::set_3d_shadow_color (color_t v)
{
	_3d_shadow_color = v;
}

void rectangle_3d_renderer::set_3d_color_by_fill_color (void)
{
	_3d_light_color  = color_level(_fill_color, 2.00f);
	_3d_shadow_color = color_level(_fill_color, 0.50f);
}

void rectangle_3d_renderer::set_3d_pressed (cx::bool_t v)
{
	_3d_pressed = v;
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
