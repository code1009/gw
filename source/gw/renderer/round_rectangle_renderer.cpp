/////////////////////////////////////////////////////////////////////////////
//
// File: round_rectangle_renderer.cpp
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
static void GetCapsule(GraphicsPath* pPath, RectF baseRect)
{ 
    float diameter; 
    
    try
	{ 
        if( baseRect.Width > baseRect.Height)
		{ 
            diameter = baseRect.Height;            

			RectF arc( baseRect.X, baseRect.Y, diameter, diameter); 
            pPath->AddArc( arc, 90, 180); 
            
			arc.X = baseRect.GetRight() - diameter; 
            pPath->AddArc( arc, 270, 180); 
        }
		else if( baseRect.Width < baseRect.Height )
		{ 
            diameter = baseRect.Width;
             
            RectF arc( baseRect.X, baseRect.Y, diameter, diameter ); 
            pPath->AddArc( arc, 180, 180 ); 
            
			arc.Y = baseRect.GetBottom() - diameter; 
            pPath->AddArc( arc, 0, 180 ); 
        }
		else
		{ 
            pPath->AddEllipse( baseRect ); 
        }
    }
	catch(...)
	{
		pPath->AddEllipse( baseRect ); 
	}
	
    pPath->CloseFigure(); 
}

static void GetRoundRect(GraphicsPath* pPath, RectF baseRect, float radius)
{
    if( radius<=0.0F )
	{ 
        pPath->AddRectangle(baseRect); 
        pPath->CloseFigure(); 
        return;
    }

    if( radius>=(min(baseRect.Width, baseRect.Height))/2.0F)
	{
        GetCapsule(pPath, baseRect); 
        return;
    }


    float diameter = radius * 2.0F; 

	RectF arc   ( baseRect.X, baseRect.Y, diameter, diameter); 
    pPath->AddArc( arc, 180, 90 ); 

	arc.X = baseRect.GetRight() -diameter; 
	pPath->AddArc( arc, 270, 90 ); 
    
	arc.Y = baseRect.GetBottom() -diameter; 
	pPath->AddArc( arc, 0, 90 ); 

	arc.X = baseRect.GetLeft();
    pPath->AddArc( arc, 90, 90 );     

	pPath->CloseFigure(); 
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
round_rectangle_renderer::round_rectangle_renderer()
{
	_fill_color.set(0xEC, 0xEC, 0xEC);
	_line_color.set(0x40, 0x40, 0x40);
	_line_width = 1.0f;

	_line_dash_style = DashStyleSolid;
}

round_rectangle_renderer::~round_rectangle_renderer()
{
}

//===========================================================================
void round_rectangle_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);


	GraphicsPath RoundPath;


	GetRoundRect(&RoundPath, r, _radius);
	

	if (!_fill_color.get_alpha_zero())
	{
		SolidBrush fill(Color(_fill_color.ARGB()));


		g->FillPath(&fill, &RoundPath);
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


			g->DrawPath(&line, &RoundPath);
		}
	}
}

//===========================================================================
void round_rectangle_renderer::set_rectangle (rectangle_t v)
{
	_rectangle = v;

	cx::float_t f;
	
	
	f = _rectangle.w() < _rectangle.h() ? _rectangle.w() : _rectangle.h();
	f = f * 0.1f;

	set_radius(f);
}

void round_rectangle_renderer::set_radius (cx::float_t radius)
{
	_radius = radius;
}

void round_rectangle_renderer::set_fill_color (color_t v)
{
	_fill_color = v;
}

void round_rectangle_renderer::set_line_color (color_t v)
{
	_line_color = v;
}

void round_rectangle_renderer::set_line_width (cx::float_t v)
{
	_line_width = v;
}

void round_rectangle_renderer::set_line_dash_style(cx::uint_t v)
{
	_line_dash_style = v;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
