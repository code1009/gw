/////////////////////////////////////////////////////////////////////////////
//
// File: round_rectangle_glass_renderer.cpp
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
round_rectangle_glass_renderer::round_rectangle_glass_renderer()
{
#if 0
	_fill_background_color = color_t::Black       ;
	_fill_glow_color       . set(0x8D, 0xBD, 0xFF);
	_fill_shine_color      = color_t::White       ;
#endif

#if 0
	_fill_background_color = color_t::Brown;
	_fill_glow_color       = color_t::Red  ;
	_fill_shine_color      = color_t::Gold ;
#endif
	
#if 0
	_fill_background_color = color_t::Red  ;
	_fill_glow_color       = color_t::White;
	_fill_shine_color      = color_t::Gold ;
#endif
	
#if 0
	_fill_background_color .set (0x80, 0x80, 0xFF);
	_fill_glow_color       .set (0x8D, 0xBD, 0xFF);
	_fill_shine_color      .set (0xF0, 0xF0, 0xFF);
#endif

#if 1
	_fill_background_color .set (0x00, 0x00, 0x40);
	_fill_glow_color       .set (0x8D, 0xBD, 0xFF);
	_fill_shine_color      .set (0xC0, 0xC0, 0xD0);
#endif

	_fill_glow_opacity = false;
	_fill_opacity      = false;
}

round_rectangle_glass_renderer::~round_rectangle_glass_renderer()
{
}

//===========================================================================
void round_rectangle_glass_renderer::render (graphic_t g)
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


	is_pressed = _fill_opacity;

	Color backColor  (_fill_background_color.ARGB());
	Color glowColor  (_fill_glow_color      .ARGB());
	Color shineColor (_fill_shine_color     .ARGB());

#if 0
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
	cx::float_t frameIndex  = _fill_glow_opacity ? 2.0f : 9.0f; // 9.0=HOver, 0.0=Normal
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

//===========================================================================
void round_rectangle_glass_renderer::set_rectangle (rectangle_t v)
{
	_rectangle = v;
}

void round_rectangle_glass_renderer::set_fill_background_color (color_t v)    { _fill_background_color = v; }
void round_rectangle_glass_renderer::set_fill_glow_color       (color_t v)    { _fill_glow_color       = v; }
void round_rectangle_glass_renderer::set_fill_shine_color      (color_t v)    { _fill_shine_color      = v; }
void round_rectangle_glass_renderer::set_fill_glow_opacity     (cx::bool_t v) { _fill_glow_opacity     = v; }
void round_rectangle_glass_renderer::set_fill_opacity          (cx::bool_t v) { _fill_opacity          = v; }


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
