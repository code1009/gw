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

static void GetRoundedRect(GraphicsPath* pPath, RectF baseRect, float radius)
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

static void CreateRoundRectangle(GraphicsPath* path, RectF rect, float radius)
{
    float l = rect.X;
    float t = rect.Y;
    float w = rect.Width;
    float h = rect.Height;
    float d = radius / 2.0f;

    path->AddArc(l, t, d, d, 180, 90); // topleft
    path->AddLine(l + radius, t, l + w - radius, t); // top
    path->AddArc(l + w - d, t, d, d, 270, 90); // topright
    path->AddLine(l + w, t + radius, l + w, t + h - radius); // right
    path->AddArc(l + w - d, t + h - d, d, d, 0, 90); // bottomright
    path->AddLine(l + w - radius, t + h, l + radius, t + h); // bottom
    path->AddArc(l, t + h - d, d, d, 90, 90); // bottomleft
    path->AddLine(l, t + h - radius, l, t + radius); // left
    path->CloseFigure();
}

static void CreateTopRoundRectangle(GraphicsPath* path, RectF rect, float radius)
{
    float l = rect.X;
    float t = rect.Y;
    float w = rect.Width;
    float h = rect.Height;
    float d = radius / 2.0f;

    path->AddArc(l, t, d, d, 180, 90); // topleft
    path->AddLine(l + radius, t, l + w - radius, t); // top
    path->AddArc(l + w - d, t, d, d, 270, 90); // topright
    path->AddLine(l + w, t + radius, l + w, t + h); // right
    path->AddLine(l + w, t + h, l, t + h); // bottom
    path->AddLine(l, t + h, l, t + radius); // left
    path->CloseFigure();
}

static void CreateBottomRadialPath(GraphicsPath* path, RectF rect)
{
    rect.X -= rect.Width * .35f;
    rect.Y -= rect.Height * .15f;
    rect.Width *= 1.7f;
    rect.Height *= 2.3f;
    path->AddEllipse(rect);
    path->CloseFigure();
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
#if 1
void round_rectangle_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);


	GraphicsPath RoundPath;


	GetRoundedRect(&RoundPath, r, _radius);
	

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
#else
void round_rectangle_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);


	GraphicsPath RoundPath;


	GetRoundedRect(&RoundPath, r, _radius);
	

	// https://www.codeproject.com/Articles/17695/Creating-a-Glass-Button-using-GDI
	cx::bool_t is_pressed;


	is_pressed = false;

	cx::float_t glowOpacity = 0.0f; // 0.0f; // or 9.0f
	Color backColor  = Color::Blue;
	Color glowColor  = Color::MakeARGB(0xFF, 0x8D, 0xBD, 0xFF);
	Color shineColor = Color::White;

	cx::int_t  opacity;
	Color      color;
	Color      cr;
	Color      cr0;
	Color      cr1;


	// content
	color   = backColor;
	opacity = 0x7f;
	if (is_pressed)
	{
		opacity = 0xcc;
	}
	cr = Color::MakeARGB(opacity, color.GetR(), color.GetG(), color.GetB());;

	SolidBrush fillContent(cr);
	
	g->FillPath(&fillContent, &RoundPath);


#if 0
	// glow
	color = glowColor;
//	g->SetClip(&RoundPath, CombineModeIntersect);
	
	
	GraphicsPath brad;


	CreateBottomRadialPath(&brad, r);


	PathGradientBrush glowFill(&brad);

	opacity = (int)(0xB2 * glowOpacity + .5f);
	
	
	RectF bounds;
	
	
	brad.GetBounds(&bounds);
	
	
	glowFill.SetCenterPoint( PointF((bounds.X + bounds.Width) / 2.0f, (bounds.Y + bounds.Height) / 2.0f) );
	glowFill.SetCenterColor( Color::MakeARGB(opacity, color.GetR(), color.GetG(), color.GetB()) );

	Color SurroundColors[1]  = { Color::MakeARGB(0, color.GetR(), color.GetG(), color.GetB()) };
	INT   SurroundColorCount = 1;
	glowFill.SetSurroundColors(SurroundColors, &SurroundColorCount);
	
	g->FillPath(&glowFill, &brad);
#endif


	// shine
	color   = shineColor;
	opacity = 0x99;
	if (is_pressed)
	{
		opacity = (cx::int_t)(0.4f * opacity + 0.5f);
	}
	cr0 = Color::MakeARGB(opacity  , color.GetR(), color.GetG(), color.GetB());
	cr1 = Color::MakeARGB(opacity/3, color.GetR(), color.GetG(), color.GetB());

	RectF rh;

	rh = r;
	rh.Height = r.Height/2.0f;
	LinearGradientBrush fillShine(rh, cr0, cr1, LinearGradientModeVertical);
	
	GraphicsPath bh;
	CreateTopRoundRectangle(&bh, rh, _radius);
	g->FillPath(&fillShine, &bh);
	

	// 
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
#endif

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
