/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_renderer.cpp
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
rectangle_renderer::rectangle_renderer()
{
	_fill_color.set(0xEC, 0xEC, 0xEC);
	_line_color.set(0x40, 0x40, 0x40);
	_line_width = 1.0f;

	_line_dash_style = DashStyleSolid;
}

rectangle_renderer::~rectangle_renderer()
{
}

//===========================================================================
void rectangle_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);


	if (!_fill_color.get_alpha_zero())
	{
		SolidBrush fill(Color(_fill_color.ARGB()));


		g->FillRectangle(&fill, r);
	}


	if (_line_width>0.0f)
	{
		if (!_line_color.get_alpha_zero())
		{
			Pen line(Color(_line_color.ARGB()), _line_width);

		
			if (_line_dash_style != DashStyleSolid)
			{
				line.SetDashStyle(static_cast<DashStyle>(_line_dash_style));
			}


			g->DrawRectangle(&line, r);
		}
	}
}

//===========================================================================
void rectangle_renderer::set_rectangle (rectangle_t v)
{
	_rectangle = v;
}

void rectangle_renderer::set_fill_color (color_t v)
{
	_fill_color = v;
}

void rectangle_renderer::set_line_width (cx::float_t v)
{
	_line_width = v;
}

void rectangle_renderer::set_line_color (color_t v)
{
	_line_color = v;
}

void rectangle_renderer::set_line_dash_style(cx::uint_t v)
{
	_line_dash_style = v;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
