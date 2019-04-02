/////////////////////////////////////////////////////////////////////////////
//
// File: blue_highlight.cpp
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
blue_highlight::blue_highlight()
{
}

blue_highlight::~blue_highlight()
{
}

//===========================================================================
std::string blue_highlight::get_registered_name (void)
{
	return "widget.control.blue_highlight";
}

//===========================================================================
std::string blue_highlight::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void blue_highlight::draw_control (void)
{
	graphic_t g;
	rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	rectangle r1;
	rectangle r2;


	r1 = r;
	r2 = r;
	r2.inflate(-8.0f,0.0f);


	_renderer1.set_model     (get_model());
	_renderer1.set_rectangle ( r1 );

	_renderer1.set_fill_color (color_t(0xA0, 0xA0, 0xff, 0xA0));
	_renderer1.set_line_color (color_t(0x00, 0x00, 0x80, 0xA0));
	_renderer1.set_line_width (1.0f);


	_renderer2.set_model     ( get_model() );
	_renderer2.set_rectangle ( r2 );

	_renderer2.set_text      ( get_text() );
	_renderer2.set_text_font ();
	_renderer2.set_text_format_alignment (StringAlignmentNear);


	if (get_pressed() || get_selected())
	{
		if (get_pressed())
		{
			r2._p0._x += 2.0f;
			r2._p0._y += 2.0f;

			_renderer2.set_rectangle(r2);
		}
		
		_renderer1.render(g);
	}


	_renderer2.render(g);
}

//===========================================================================
std::string blue_highlight::get_text(void)
{
	return _text;
}

void blue_highlight::set_text(std::string v)
{
	if (_text != v)
	{
		_text = v;
		set_redraw();
	}
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: blue_highlight_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void blue_highlight_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
	blue_highlight* wc = cx_gw_dynamic_cast<blue_highlight*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
}

void blue_highlight_event_handler::on_mouse_hover(widget_mouse_event* e)
{
	blue_highlight* wc = cx_gw_dynamic_cast<blue_highlight*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
	wc->set_selected(true);
}

void blue_highlight_event_handler::on_mouse_leave(widget_mouse_event* e)
{
	blue_highlight* wc = cx_gw_dynamic_cast<blue_highlight*>(e->_widget);

	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wc);
	wc->set_selected(false);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
