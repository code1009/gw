/////////////////////////////////////////////////////////////////////////////
//
// File: line_renderer.cpp
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
line_renderer::line_renderer()
{
	_line_color.set(0x40, 0x40, 0x40);
	_line_width = 1.0f;

	_line_dash_style = DashStyleSolid;
}

line_renderer::~line_renderer()
{
}

//===========================================================================
void line_renderer::render (graphic_t g)
{
	if (_line_width>0.0f)
	{
		if (!_line_color.get_alpha_zero())
		{
			Pen line(Color(_line_color.ARGB()), _line_width);

		
			if (_line_dash_style != DashStyleSolid)
			{
				line.SetDashStyle(static_cast<DashStyle>(_line_dash_style));
			}


			g->DrawLine(&line, _p0._x, _p0._y, _p1._x, _p1._y);
		}
	}
}

//===========================================================================
void line_renderer::set_point (point_t p0, point_t p1)
{
	_p0 = p0;
	_p1 = p1;
}

void line_renderer::set_line_width (cx::float_t v)
{
	_line_width = v;
}

void line_renderer::set_line_color (color_t v)
{
	_line_color = v;
}

void line_renderer::set_line_dash_style(cx::uint_t v)
{
	_line_dash_style = v;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
