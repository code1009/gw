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

//===========================================================================
static void MakeRoundRect (GraphicsPath* path, RectF rect, float radius)
{
    float l = rect.X;
    float t = rect.Y;
    float w = rect.Width;
    float h = rect.Height;
    float d = radius * 2.0f;


    path->AddArc (l, t, d, d, 180, 90); // topleft
    path->AddLine(l + radius, t, l + w - radius, t); // top
    path->AddArc (l + w - d, t, d, d, 270, 90); // topright
    path->AddLine(l + w, t + radius, l + w, t + h - radius); // right
    path->AddArc (l + w - d, t + h - d, d, d, 0, 90); // bottomright
    path->AddLine(l + w - radius, t + h, l + radius, t + h); // bottom
    path->AddArc (l, t + h - d, d, d, 90, 90); // bottomleft
    path->AddLine(l, t + h - radius, l, t + radius); // left
    path->CloseFigure();
}

static void MakeTopRoundRect (GraphicsPath* path, RectF rect, float radius)
{
    float l = rect.X;
    float t = rect.Y;
    float w = rect.Width;
    float h = rect.Height;
    float d = radius * 2.0f;


    path->AddArc (l, t, d, d, 180, 90); // topleft
    path->AddLine(l + radius, t, l + w - radius, t); // top
    path->AddArc (l + w - d, t, d, d, 270, 90); // topright
    path->AddLine(l + w, t + radius, l + w, t + h); // right
    path->AddLine(l + w, t + h, l, t + h); // bottom
    path->AddLine(l, t + h, l, t + radius); // left
    path->CloseFigure();
}

static void MakeBottomRadialPath(GraphicsPath* path, RectF rect)
{
    rect.X      -= rect.Width  * .35f;
    rect.Y      -= rect.Height * .15f;
    rect.Width  *= 1.7f;
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
#if 0
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

	RectF rBB; // black border
	RectF rWB; // white border
	RectF rC;  // contents
	RectF rTS; // top shine
	GraphicsPath RoundPathBB;
	GraphicsPath RoundPathWB;
	GraphicsPath RoundPathC;
	GraphicsPath RoundPathTS;

	
	rWB = r;
	rWB.Width -=1.0f;
	rWB.Height-=1.0f;
	MakeRoundRect (&RoundPathWB, rWB, 4);

	rC = r;
	rC.X+=1;
	rC.Y+=1;
	rC.Width -=3.0f;
	rC.Height-=3.0f;
	MakeRoundRect (&RoundPathC, rC, 2);
	
	rTS = rC;
	rTS.Height = rC.Height/2.0f;
	MakeTopRoundRect (&RoundPathTS, rTS, 2);
	
	rBB = rC;
	MakeRoundRect (&RoundPathBB, rBB, 3);


	// https://www.codeproject.com/Articles/17695/Creating-a-Glass-Button-using-GDI
	cx::bool_t is_pressed;


	is_pressed = false;

#if 1
	Color backColor  = Color::Black                           ;
	Color glowColor  = Color::MakeARGB(0xFF, 0x8D, 0xBD, 0xFF);
	Color shineColor = Color::White                           ;
#endif

#if 0
	Color backColor  = Color::Brown;
	Color glowColor  = Color::Red  ;
	Color shineColor = Color::Gold ;
#endif
	
#if 0
	Color backColor  = Color::Red  ;
	Color glowColor  = Color::White;
	Color shineColor = Color::Gold ;
#endif
	
#if 0
	Color backColor  = Color::MakeARGB(0xFF, 0x80, 0x80, 0xFF);
	Color glowColor  = Color::MakeARGB(0xFF, 0x8D, 0xBD, 0xFF);
	Color shineColor = Color::MakeARGB(0xFF, 0xF0, 0xF0, 0xFF);
#endif

	cx::float_t frameCount  = 10.0f;
	cx::float_t frameIndex  = 9.0f;  // 9.0f=HOver, 0.0=Normal
	cx::float_t glowOpacity = frameIndex/(frameCount-1.0f);

	cx::int_t  opacity;
	Color      color;
	Color      cr;
	Color      cr0;
	Color      cr1;



	//-----------------------------------------------------------------------
	// outter white border
	Pen lineWhite(Color::White, 1.0f);

	g->DrawPath(&lineWhite, &RoundPathWB);


	//-----------------------------------------------------------------------
	// content
	color   = backColor;
	opacity = 0x7f;
	if (is_pressed)
	{
		opacity = 0xcc;
	}
	cr = Color::MakeARGB(opacity, color.GetR(), color.GetG(), color.GetB());;

	SolidBrush fillContent(cr);
	
	g->FillPath(&fillContent, &RoundPathC);


#if 1
	//-----------------------------------------------------------------------
	// glow
	color   = glowColor;
	opacity = (int)(0xB2 * glowOpacity + .5f);
	if (!is_pressed)
	{
		cr0 = Color::MakeARGB(opacity, color.GetR(), color.GetG(), color.GetB());
		cr1 = Color::MakeARGB(0      , color.GetR(), color.GetG(), color.GetB());
	
	
		GraphicsPath brad;
		RectF        bounds;
		PointF       center;


		MakeBottomRadialPath(&brad, rC);
		brad.GetBounds(&bounds);
		center.X = (bounds.X + bounds.Width ) / 2.0f;
		center.Y = (bounds.Y + bounds.Height) / 2.0f;


		PathGradientBrush glowFill(&brad);
		Color surroundColors[1]  = { cr1 };
		INT   surroundColorCount = 1;


		glowFill.SetCenterPoint( center );
		glowFill.SetCenterColor( cr0 );
		glowFill.SetSurroundColors(surroundColors, &surroundColorCount);
	

		g->SetClip   (&RoundPathC, CombineModeIntersect);
		g->FillPath  (&glowFill, &brad);
		g->ResetClip ();
	}
#endif


	//-----------------------------------------------------------------------
	// shine
	color   = shineColor;
	opacity = 0x99;
	if (is_pressed)
	{
		opacity = (cx::int_t)(0.4f * opacity + 0.5f);
	}
	cr0 = Color::MakeARGB(opacity  , color.GetR(), color.GetG(), color.GetB());
	cr1 = Color::MakeARGB(opacity/3, color.GetR(), color.GetG(), color.GetB());


	LinearGradientBrush fillShine(rTS, cr0, cr1, LinearGradientModeVertical);
	
	g->FillPath(&fillShine, &RoundPathTS);
	

	//-----------------------------------------------------------------------
	// innder black border
	Pen lineBlack(Color::Black, 1.0f);

	g->DrawPath(&lineBlack, &RoundPathBB);
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
