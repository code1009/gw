/////////////////////////////////////////////////////////////////////////////
//
// File: button.cpp
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
button::button()
{
}

button::~button()
{
}

//===========================================================================
std::string button::get_registered_name (void)
{
	return "widget.control.button";
}

//===========================================================================
std::string button::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void button::draw_control (void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer1.set_model     ( get_model() );
	_renderer1.set_rectangle ( r );

	_renderer1.set_3d_pressed ( get_pressed() );

	
	_renderer2.set_model     ( get_model() );
	_renderer2.set_rectangle ( r );

	_renderer2.set_text      ( get_text()  );
	_renderer2.set_text_font ();
	_renderer2.set_text_format_alignment();


	if (get_pressed())
	{
		r._p0._x += 2.0f;
		r._p0._y += 2.0f;

		_renderer2.set_rectangle ( r );
	}


	_renderer1.render(g);


/*
	cx::bool_t is_pressed;
	RectF      rc;

	cx::int_t  opacity;
	Color      shineColor;
	Color      cr0;
	Color      cr1;


	is_pressed = get_pressed();
	rc = rectangle_to_RectF(r);


	shineColor = Color::Red;
	opacity    = 0x99;
	opacity    = (cx::int_t)(0.4f * opacity + 0.5f);
	cr0        = Color::MakeARGB(opacity  , shineColor.GetR(), shineColor.GetG(), shineColor.GetB());
	cr1        = Color::MakeARGB(opacity/3, shineColor.GetR(), shineColor.GetG(), shineColor.GetB());


	LinearGradientBrush fill(rc, cr0, cr1, LinearGradientModeVertical);
	
	g->FillRectangle(&fill, rc);
*/


	_renderer2.render(g);
}

//===========================================================================
std::string button::get_text(void)
{
	return _text;
}

void button::set_text(std::string v)
{
	if (_text != v)
	{
		_text = v;
		set_redraw();
	}
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: button_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void button_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
	button* wc = cx_gw_dynamic_cast<button*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
