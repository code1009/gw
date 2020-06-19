/////////////////////////////////////////////////////////////////////////////
//
// File: view.cpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// TODO:
// 1. world_rectangle left와 top이 0이 아닐경우




/////////////////////////////////////////////////////////////////////////////
//
// Headers
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: view
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
view::view()
{
	//-----------------------------------------------------------------------
	_model = CX_NULL_POINTER;


	//-----------------------------------------------------------------------
	_viewscale = 1.0F;

	set_wolrd_rectangle(rectangle_t(1.0f,1.0f));
	set_viewport_window_size(1,1);

	_grid_xsize   = 50;
	_grid_ysize   = 50;
	_grid_visible = false;


	//-----------------------------------------------------------------------
	_background_color = color_t(0xEC,0xEC,0xEC);


/*
	//-----------------------------------------------------------------------
	GdiplusStartupInput gdiplusStartupInput;


    GdiplusStartup(&_gdiplus_token, &gdiplusStartupInput, NULL);
*/
}

view::~view()
{
/*
	//-----------------------------------------------------------------------
    GdiplusShutdown(_gdiplus_token);
*/
}

//===========================================================================
model* view::get_model (void)
{
	return _model;
}

void view::set_model (model* model)
{
	_model = model;
}

//===========================================================================
color_t view::get_background_color (void)
{
	return _background_color;
}

void view::set_background_color (color_t background_color)
{
	_background_color = background_color;

	get_model()->set_redraw();
}

//===========================================================================
#if 0
void view::draw (HDC hdc)
{
	CX_DEBUG_TRACEF (CX_TWA_NORMAL, "begin");


	Graphics g(hdc);


	g.ScaleTransform     (get_viewscale(),get_viewscale());
	g.TranslateTransform (-get_viewport_world_rectangle()._p0._x, -get_viewport_world_rectangle()._p0._y);
	/*
	# or 
	Matrix transformation = new Matrix();
	transformation.Translate(50, 50);
	g.Transform = transformation;
	*/

	g.SetSmoothingMode (SmoothingModeNone);
//	g.SetSmoothingMode (SmoothingModeAntiAlias);
//	g.SetSmoothingMode (SmoothingModeHighSpeed);

	draw_background (&g);

	if (true==get_grid_visible())
	{
		draw_grid (&g);
	}

	draw_model (&g);


	CX_DEBUG_TRACEF (CX_TWA_NORMAL, "end");
}
#else
void view::draw (HDC hdc)
{
//	CX_DEBUG_TRACEF (CX_TWA_NORMAL, "begin");

	Bitmap canvas (get_viewport_window_xsize(), get_viewport_window_ysize(), PixelFormat32bppPARGB );

	Graphics g(&canvas);

	g.SetCompositingMode   (CompositingModeSourceOver);   // Over for tranparency
	g.SetCompositingQuality(CompositingQualityHighSpeed);
	g.SetPixelOffsetMode   (PixelOffsetModeNone);
	g.SetSmoothingMode     (SmoothingModeNone);
	g.SetInterpolationMode (InterpolationModeDefault);
	g.SetTextRenderingHint (TextRenderingHintAntiAliasGridFit);

	g.ScaleTransform     (get_viewscale(),get_viewscale());
	g.TranslateTransform (-get_viewport_world_rectangle()._p0._x, -get_viewport_world_rectangle()._p0._y);
	/*
	# or 
	Matrix transformation = new Matrix();
	transformation.Translate(50, 50);
	g.Transform = transformation;
	*/

//	g.SetSmoothingMode (SmoothingModeNone);
//	g.SetSmoothingMode (SmoothingModeAntiAlias);
//	g.SetSmoothingMode (SmoothingModeHighSpeed);

	draw_background (&g);

	if (true==get_grid_visible())
	{
		draw_grid (&g);
	}

	draw_model (&g);



	Graphics* pGraphics = Graphics::FromHWND(get_model()->get_window(), FALSE);

	pGraphics->SetCompositingMode   (CompositingModeSourceCopy);
	pGraphics->SetCompositingQuality(CompositingQualityHighSpeed);
	pGraphics->SetPixelOffsetMode   (PixelOffsetModeNone);
	pGraphics->SetSmoothingMode     (SmoothingModeNone);
	pGraphics->SetInterpolationMode (InterpolationModeDefault);

	pGraphics->DrawImage(&canvas, 0, 0);

	delete pGraphics;

//	CX_DEBUG_TRACEF (CX_TWA_NORMAL, "end");
}
#endif

void view::draw_background (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(get_viewport_world_rectangle());

	
	SolidBrush fill(Color(_background_color.ARGB()));


	g->FillRectangle(&fill, r);
}

void view::draw_model (graphic_t g)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	m->set_graphic(g);
	m->draw();
	m->set_graphic(CX_NULL_POINTER);
}

void view::draw_grid (graphic_t g)
{
//	Color       pen_color(255, 224,255,224);
	Color       pen_color(255, 240,255,240);
	cx::float_t pen_width = 1.0f;
	Pen         pen(pen_color, pen_width);

	
//	pen.SetDashStyle(DashStyleDot); // 느림


//	Color       boarder_pen_color(255, 64,128,64);
	Color       boarder_pen_color(255, 128,255,128);
	cx::float_t boarder_pen_width = 1.0f;
	Pen         boarder_pen(boarder_pen_color, boarder_pen_width);


	cx::int_t x1;
	cx::int_t y1;
	cx::int_t x2;
	cx::int_t y2;
	cx::int_t x;
	cx::int_t y;

	point_t p;


	p._x = static_cast<coordinates_t>( max(0, _viewport_wolrd_rectangle.l()-_grid_xsize/2.0f) );
	p._y = static_cast<coordinates_t>( max(0, _viewport_wolrd_rectangle.t()-_grid_ysize/2.0f) );
	p    = to_grid_point(p);

	x1 = static_cast<cx::int_t>( p._x );
	x2 = static_cast<cx::int_t>( _wolrd_rectangle.r() );
	y1 = static_cast<cx::int_t>( p._y );
	y2 = static_cast<cx::int_t>( _wolrd_rectangle.b() );

	
	// grid
	for (x=x1; x<=x2; x+=_grid_xsize)
	{
		g->DrawLine(&pen, x, y1, x, y2);
	}

			
	for (y=y1; y<=y2; y+=_grid_ysize)
	{
		g->DrawLine(&pen, x1, y, x2, y);
	}			


	// border
	g->DrawRectangle(&boarder_pen, _wolrd_rectangle.l(), _wolrd_rectangle.t(), _wolrd_rectangle.w(), _wolrd_rectangle.h());
}

//===========================================================================
rectangle_t view::get_wolrd_rectangle (void)
{
	return _wolrd_rectangle;
}

void view::set_wolrd_rectangle (rectangle_t rectangle)
{
	_wolrd_rectangle = rectangle;


	_viewscale_xsize = static_cast<cx::int_t>(_wolrd_rectangle.w() * _viewscale);
	_viewscale_ysize = static_cast<cx::int_t>(_wolrd_rectangle.h() * _viewscale);
}

//===========================================================================
cx::float_t view::get_viewscale (void)
{
	return _viewscale;
}

void view::set_viewscale (cx::float_t viewscale)
{
	if (viewscale<=0.0)
	{
		return;
	}

	_viewscale = viewscale;

	set_wolrd_rectangle(_wolrd_rectangle);
	set_viewport_window_size(_viewport_window_xsize, _viewport_window_ysize);
}

cx::int_t view::get_viewscale_xsize (void)
{
	return _viewscale_xsize;
}

cx::int_t view::get_viewscale_ysize (void)
{
	return _viewscale_ysize;
}

//===========================================================================
cx::int_t view::get_viewport_window_xsize (void)
{
	return _viewport_window_xsize;
}

cx::int_t view::get_viewport_window_ysize (void)
{
	return _viewport_window_ysize;
}

void view::set_viewport_window_size (cx::int_t xsize, cx::int_t ysize)
{
	_viewport_window_xsize = xsize ;
	_viewport_window_ysize = ysize;

	_viewport_wolrd_rectangle._p1._x = _viewport_wolrd_rectangle._p0._x + ( _viewport_window_xsize / _viewscale );
	_viewport_wolrd_rectangle._p1._y = _viewport_wolrd_rectangle._p0._y + ( _viewport_window_ysize / _viewscale );

	CX_DEBUG_TRACEF(TW_THISCODE, "{%d,%d}",
		_viewport_window_xsize,
		_viewport_window_ysize
		);
}

cx::int_t view::get_viewport_window_xoffset (void)
{
	return _viewport_window_xoffset;
}

cx::int_t view::get_viewport_window_yoffset (void)
{
	return _viewport_window_yoffset;
}

void view::set_viewport_window_offset (cx::int_t x, cx::int_t y)
{
	_viewport_window_xoffset = x;
	_viewport_window_yoffset = y;

	_viewport_wolrd_rectangle._p0._x = _viewport_window_xoffset / _viewscale;
	_viewport_wolrd_rectangle._p0._y = _viewport_window_yoffset / _viewscale;
	_viewport_wolrd_rectangle._p1._x = _viewport_wolrd_rectangle._p0._x + ( _viewport_window_xsize / _viewscale );
	_viewport_wolrd_rectangle._p1._y = _viewport_wolrd_rectangle._p0._y + ( _viewport_window_ysize / _viewscale );

	CX_DEBUG_TRACEF(TW_THISCODE, "{%d,%d}",
		_viewport_window_xoffset,
		_viewport_window_yoffset 
		);
}

void view::set_viewport_window_xoffset (cx::int_t x)
{
	set_viewport_window_offset(x,_viewport_window_yoffset);
}

void view::set_viewport_window_yoffset (cx::int_t y)
{
	set_viewport_window_offset(_viewport_window_xoffset,y);
}

rectangle_t& view::get_viewport_world_rectangle (void)
{
	return _viewport_wolrd_rectangle;
}

//===========================================================================
point_t view::viewport_window_to_world (cx::int_t x, cx::int_t y)
{
	point_t world;


	world._x = _viewport_wolrd_rectangle.l() + ( x / _viewscale );
	world._y = _viewport_wolrd_rectangle.t() + ( y / _viewscale );

	return world;
}

void view::world_to_viewport_window (point_t world, cx::int_t& x, cx::int_t& y)
{
	x = static_cast<cx::int_t>( ( world._x - _viewport_wolrd_rectangle.l() ) * _viewscale );
	y = static_cast<cx::int_t>( ( world._y - _viewport_wolrd_rectangle.t() ) * _viewscale );
}

//===========================================================================
point_t view::to_grid_point (point_t world)
{
	point_t    snap;
	cx::int_t  x;
	cx::int_t  y;
	cx::bool_t x_minus = false;
	cx::bool_t y_minus = false;


	x = static_cast<cx::int_t>( world._x );
	y = static_cast<cx::int_t>( world._y );
	if (x<0)
	{
		x_minus = true;
		x = x * -1;
	}
	if (y<0)
	{
		y_minus = true;
		y = y * -1;
	}

	x = ((x + _grid_xsize/2)/_grid_xsize)*_grid_xsize;
	y = ((y + _grid_ysize/2)/_grid_ysize)*_grid_ysize;

	if (x_minus)
	{
		x = x * -1;
	}
	if (y_minus)
	{
		y = y * -1;
	}
			
	snap._x = static_cast<coordinates_t>( x );
	snap._y = static_cast<coordinates_t>( y );

	return snap;
}

//===========================================================================
cx::int_t view::get_grid_xsize (void)
{
	return _grid_xsize;
}

cx::int_t view::get_grid_ysize (void)
{
	return _grid_ysize;
}

void view::set_grid_size (cx::int_t x, cx::int_t y)
{
	_grid_xsize = x;
	_grid_ysize = y;


	get_model()->set_redraw();
}

cx::bool_t view::get_grid_visible (void)
{
	return _grid_visible;
}

void view::set_grid_visible (cx::bool_t visible)
{
	_grid_visible = visible;


	get_model()->set_redraw();
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
