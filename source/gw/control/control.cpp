/////////////////////////////////////////////////////////////////////////////
//
// File: control.cpp
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
namespace ctrl
{


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
control::control()
{
	_visible   = true;
	_enabled   = true;
	_pressed   = false;
	_selected  = false;
	_activated = false;
	_focus     = false;
}

control::~control()
{
}

//===========================================================================
std::string control::get_registered_name (void)
{
	return "widget.control";
}

//===========================================================================
void control::set_model (model* model)
{
	widget::set_model(model);

//	_renderer.set_model(model);
}

std::string control::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void control::initialize (void)
{
	point_t p;


	get_point_container().push_back(p);
	get_point_container().push_back(p);
	get_point_container().push_back(p);
	get_point_container().push_back(p);


	get_point_container()[0].set(coordinates_t(  0), coordinates_t(  0));
	get_point_container()[1].set(coordinates_t(100), coordinates_t(  0));
	get_point_container()[2].set(coordinates_t(100), coordinates_t(100));
	get_point_container()[3].set(coordinates_t(  0), coordinates_t(100));


	widget::initialize();
}

cx::bool_t control::is_point_in (point_t p)
{
	return get_bounds().is_point_in(p);
}

void control::set_bounds (rectangle_t bounds)
{
	get_point_container()[0].set(bounds._p0._x, bounds._p0._y);
	get_point_container()[1].set(bounds._p1._x, bounds._p0._y);
	get_point_container()[2].set(bounds._p1._x, bounds._p1._y);
	get_point_container()[3].set(bounds._p0._x, bounds._p1._y);

	widget::set_bounds(bounds);
}

void control::draw (void)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (false==get_visible())
	{
		return;
	}


	if (is_point_container_on_rectangle(get_point_container(), m->get_view()->get_viewport_world_rectangle()))
	{
		draw_control();
	}


	widget::draw(); // child control
}

//===========================================================================
void control::draw_control (void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer.set_model      ( get_model() );
	_renderer.set_rectangle  ( r );
	_renderer.set_3d_pressed ( get_pressed() );
	_renderer.render(g);
}

//===========================================================================
cx::bool_t control::get_visible(void)
{
	return _visible;
}

void control::set_visible(cx::bool_t v)
{
	if (_visible != v)
	{
		_visible = v;
		set_redraw();
	}
}

//===========================================================================
cx::bool_t control::get_enabled(void)
{
	return _enabled;
}

void control::set_enabled(cx::bool_t v)
{
	if (_enabled != v)
	{
		_enabled = v;
		set_redraw();
	}
}

//===========================================================================
void control::set_pressed(cx::bool_t v)
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

cx::bool_t control::get_pressed(void)
{
	return _pressed;
}

//===========================================================================
cx::bool_t control::get_selected(void)
{
	return _selected;
}

void control::set_selected(cx::bool_t v)
{
	if (_selected != v)
	{
		_selected = v;
		set_redraw();
	}
}

//===========================================================================
cx::bool_t control::get_activated(void)
{
	return _activated;
}

void control::set_activated(cx::bool_t v)
{
	if (_activated != v)
	{
		_activated = v;
		set_redraw();
	}
}

//===========================================================================
cx::bool_t control::get_focus(void)
{
	return _focus;
}

void control::set_focus(cx::bool_t v)
{
	if (_focus != v)
	{
		_focus = v;
		set_redraw();
	}
}




/////////////////////////////////////////////////////////////////////////////
//
// Class: control_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void control_event_handler::on_mouse_pressed (widget_mouse_event* e)
{
	control* wc = cx_gw_dynamic_cast<control*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
	wc->set_pressed(true);
}

void control_event_handler::on_mouse_released (widget_mouse_event* e)
{
	control* wc = cx_gw_dynamic_cast<control*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
	wc->set_pressed(false);
}

void control_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
}

void control_event_handler::on_mouse_dbclicked (widget_mouse_event* e)
{
}

void control_event_handler::on_mouse_hover (widget_mouse_event* e)
{
}

void control_event_handler::on_mouse_leave (widget_mouse_event* e)
{
}

void control_event_handler::on_mouse_dragging (widget_mouse_event* e)
{
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
