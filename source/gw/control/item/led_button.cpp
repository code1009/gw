/////////////////////////////////////////////////////////////////////////////
//
// File: led_button.cpp
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
#include "../../header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{
namespace ctrl
{


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
led_button::led_button()
{
}

led_button::~led_button()
{
}

//===========================================================================
std::string led_button::get_registered_name (void)
{
	return "widget.control.led_button";
}

//===========================================================================
void led_button::set_model (model* model)
{
	control::set_model(model);

//	_renderer1.set_model(model);
//	_renderer2.set_model(model);
}

std::string led_button::get_class (void)
{
	return get_registered_name();
}

void led_button::initialize (void)
{
	control::initialize();
}

void led_button::set_bounds (rectangle_t bounds)
{
	control::set_bounds(bounds);
}

//===========================================================================
void led_button::draw_control (void)
{
	graphic_t g;
	rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer1.set_model     ( get_model() );
	_renderer1.set_rectangle ( r );

	_renderer1.set_3d_pressed ( get_pressed() );

	
	_renderer2.set_model     ( get_model() );
	_renderer2.set_rectangle ( r );

	_renderer2.set_text      ( get_text() );
	_renderer2.set_text_font ();
	_renderer2.set_text_format_alignment(StringAlignmentNear, StringAlignmentCenter);


	if (get_pressed())
	{
		r._p0._x += 2.0f;
		r._p0._y += 2.0f;
		_renderer2.set_rectangle ( r );
	}


	if (get_selected())
	{
		_renderer1.set_fill_color ( color_t::Yellow );
		_renderer1.set_3d_color_by_fill_color();
	}
	else
	{
		_renderer1.set_fill_color ( color_t(0xECu,0xECu,0xECu) );
		_renderer1.set_3d_color_by_fill_color();
	}


	_renderer1.render(g);
	_renderer2.render(g);
}

//===========================================================================
std::string led_button::get_text(void)
{
	return _text;
}

void led_button::set_text(std::string v)
{
	if (_text != v)
	{
		_text = v;
		set_redraw();
	}
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: led_button_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void led_button_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
	led_button* wc = cx_gw_dynamic_cast<led_button*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
	wc->set_selected(!wc->get_selected());
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
