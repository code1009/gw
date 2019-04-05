/////////////////////////////////////////////////////////////////////////////
//
// File: anchor.cpp
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
namespace dgrm
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static coordinates_t ANCHOR_WIDTH  = 10.0f;
static coordinates_t ANCHOR_HEIGHT = 10.0f;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
anchor::anchor()
{
	_visible  = false;
	_enabled  = true;
	_pressed  = false;
	_selected = false;

	_id   = ANCHOR_ID_NONE;
	_type = TYPE_NONE;
}

anchor::anchor(cx::uint_t id, anchor::type_t type) : anchor()
{
	_id   = id;
	_type = type;
}

anchor::~anchor()
{
}

//===========================================================================
std::string anchor::get_registered_name (void)
{
	return "widget.anchor";
}

//===========================================================================
void anchor::set_model (model* model)
{
	widget::set_model(model);
}

std::string anchor::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void anchor::initialize (void)
{
	point_t p;


	get_point_container().push_back(p);

	widget::initialize();
}

cx::bool_t anchor::is_point_in (point_t p)
{
	return get_bounds().is_point_in(p);
}

rectangle_t anchor::get_bounds(void)
{
	return get_rectangle_wh(get_point(), ANCHOR_WIDTH, ANCHOR_HEIGHT);
}

void anchor::set_bounds (rectangle_t bounds)
{
	CX_DEBUG_ASSERT(0);

	widget::set_bounds(bounds);
}

void anchor::draw (void)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (false==get_visible())
	{
		return;
	}


	if (is_rectangle_on_rectangle(get_bounds(), m->get_view()->get_viewport_world_rectangle()))
	{
		draw_anchor();
	}
}

//===========================================================================
design* anchor::get_design(void)
{
	design* m;


	m = cx_gw_dynamic_cast<design*>(get_model());

	return m;
}

//===========================================================================
cx::uint_t anchor::get_id(void)
{
	return _id;
}

anchor::type_t anchor::get_type(void)
{
	return _type;
}

//===========================================================================
void anchor::draw_anchor (void)
{
	switch (_type)
	{
	case TYPE_RESIZE:    draw_anchor_type_resize   (); break;
	case TYPE_MOVE:      draw_anchor_type_move     (); break;
	case TYPE_CONTROL:   draw_anchor_type_control  (); break;
	case TYPE_INVISIBLE: draw_anchor_type_invisible(); break;
	default:
		break;
	}
}

void anchor::draw_anchor_type_resize(void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer1.set_model(get_model());
	_renderer1.set_rectangle(r);

	_renderer1.set_fill_color(color_t(0x80, 0x80, 0xff, 0xA0));
	_renderer1.set_line_color(color_t(0x00, 0x00, 0x80, 0xA0));
	_renderer1.set_line_width(1.0f);

	_renderer1.render(g);
}

void anchor::draw_anchor_type_move(void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer2.set_model(get_model());
	_renderer2.set_rectangle(r);

	_renderer2.set_fill_color(color_t(0xff, 0xff, 0x00, 0xFF));
	_renderer2.set_line_color(color_t(0x00, 0x00, 0x80, 0xFF));
	_renderer2.set_line_width(1.0f);

	_renderer2.render(g);
}

void anchor::draw_anchor_type_control(void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer3.set_model(get_model());
	_renderer3.set_rectangle(r);

	_renderer3.set_fill_color(color_t(0xff, 0xff, 0x00, 0xA0));
	_renderer3.set_line_color(color_t(0x00, 0x00, 0x80, 0xA0));
	_renderer3.set_line_width(1.0f);

	_renderer3.render(g);
}

void anchor::draw_anchor_type_invisible(void)
{
}

//===========================================================================
cx::bool_t anchor::get_visible(void)
{
	return _visible;
}

void anchor::set_visible(cx::bool_t v)
{
	if (_visible != v)
	{
		_visible = v;
		set_redraw();
	}
}

//===========================================================================
cx::bool_t anchor::get_enabled(void)
{
	return _enabled;
}

void anchor::set_enabled(cx::bool_t v)
{
	if (_enabled != v)
	{
		_enabled = v;
		set_redraw();
	}
}

//===========================================================================
void anchor::set_pressed(cx::bool_t v)
{
	if (false==get_enabled())
	{
		v = false;
	}

	if (_pressed != v)
	{
		_pressed = v;
		set_redraw();
	}
}

cx::bool_t anchor::get_pressed(void)
{
	return _pressed;
}

//===========================================================================
cx::bool_t anchor::get_selected(void)
{
	return _selected;
}

void anchor::set_selected(cx::bool_t v)
{
	if (_selected != v)
	{
		_selected = v;
		set_redraw();
	}
}

//===========================================================================
diagram* anchor::get_diagram(void)
{
	return get_design()->cast_diagram( get_parent() );
}

void anchor::on_set_point(point_t& p)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER != get_diagram());

	get_diagram()->on_set_anchor_point(this, p);
}

point_t anchor::get_point(void)
{
//	return widget::get_point(0);

	return get_point_container()[0];
}

void anchor::set_point(point_t& p)
{
//	widget::set_point(0, p);

	get_point_container()[0].set(p);
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: anchor_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void anchor_event_handler::on_mouse_pressed (widget_mouse_event* e)
{
	anchor* wa = cx_gw_dynamic_cast<anchor*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wa);
	wa->set_pressed(true);
}

void anchor_event_handler::on_mouse_released (widget_mouse_event* e)
{
	anchor* wa = cx_gw_dynamic_cast<anchor*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wa);
	wa->set_pressed(false);
}

void anchor_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
}

void anchor_event_handler::on_mouse_dbclicked (widget_mouse_event* e)
{
}

void anchor_event_handler::on_mouse_hover (widget_mouse_event* e)
{
}

void anchor_event_handler::on_mouse_leave (widget_mouse_event* e)
{
}

void anchor_event_handler::on_mouse_dragging (widget_mouse_event* e)
{
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
