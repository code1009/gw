#ifndef INCLUDED__CX__GW__VIEW__HPP
#define INCLUDED__CX__GW__VIEW__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: view.hpp
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
// Class: view
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class view
{
private:
	model* _model;

private:
	cx::float_t _viewscale;

	rectangle_t _wolrd_rectangle;

	cx::int_t   _viewscale_xsize;
	cx::int_t   _viewscale_ysize;
			
	cx::int_t   _viewport_window_xoffset;
	cx::int_t   _viewport_window_yoffset;
	cx::int_t   _viewport_window_xsize;
	cx::int_t   _viewport_window_ysize;

	rectangle_t _viewport_wolrd_rectangle;

	cx::int_t  _grid_xsize;
	cx::int_t  _grid_ysize;
	cx::bool_t _grid_visible;

private:
	color_t _background_color;

private:
//	ULONG_PTR _gdiplus_token;

public:
	view();
	virtual ~view();

public:
	virtual model* get_model(void);
	virtual void   set_model(model* model);

public:
	virtual color_t get_background_color (void);
	virtual void    set_background_color (color_t background_color);

public:
	virtual void draw (HDC hdc);

public:
	virtual void draw_background (graphic_t g);
	virtual void draw_grid       (graphic_t g);
	virtual void draw_model      (graphic_t g);

public:
	rectangle_t get_wolrd_rectangle (void);
	void        set_wolrd_rectangle (rectangle_t rectangle);

public:
	cx::float_t get_viewscale       (void);
	void        set_viewscale       (cx::float_t viewscale);

	cx::int_t   get_viewscale_xsize (void);
	cx::int_t   get_viewscale_ysize (void);

public:
	cx::int_t   get_viewport_window_xsize    (void);
	cx::int_t   get_viewport_window_ysize    (void);
	void        set_viewport_window_size     (cx::int_t xsize, cx::int_t ysize);

	cx::int_t   get_viewport_window_xoffset  (void);
	cx::int_t   get_viewport_window_yoffset  (void);
	void        set_viewport_window_xoffset  (cx::int_t x);
	void        set_viewport_window_yoffset  (cx::int_t y);
	void        set_viewport_window_offset   (cx::int_t x, cx::int_t y);

	rectangle_t& get_viewport_world_rectangle (void);

public:
	point_t viewport_window_to_world (cx::int_t x, cx::int_t y);
	void	world_to_viewport_window (point_t world, cx::int_t& x, cx::int_t& y);

	point_t to_grid_point (point_t world);

	cx::int_t  get_grid_xsize   (void);
	cx::int_t  get_grid_ysize   (void);
	void       set_grid_size    (cx::int_t x, cx::int_t y);
	cx::bool_t get_grid_visible (void);
	void       set_grid_visible (cx::bool_t visible);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


