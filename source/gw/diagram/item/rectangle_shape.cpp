/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_shape.cpp
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
namespace dgrm
{


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
rectangle_shape::rectangle_shape()
{
}

rectangle_shape::~rectangle_shape()
{
}

//===========================================================================
std::string rectangle_shape::get_registered_name (void)
{
	return "widget.diagram.rectangle_shape";
}

//===========================================================================
void rectangle_shape::set_model (model* model)
{
	diagram::set_model(model);

//	_renderer1.set_model(model);
//	_renderer2.set_model(model);
}

std::string rectangle_shape::get_class (void)
{
	return get_registered_name();
}

void rectangle_shape::initialize (void)
{
	diagram::initialize();

	_text                       = "";
	_text_color                 = color_t::Black;
	_text_format_alignment      = 1u;
	_text_format_line_alignment = 1u;
	_text_font_familyname       = GW_DEFAULT_TEXT_FONT_FAMILYNAME;
	_text_font_size             = GW_DEFAULT_TEXT_FONT_SIZE;
	_text_font_style            = GW_DEFAULT_TEXT_FONT_STYLE;

	_fill_color = color_t::LightBlue;
	_fill_style = 0u;

	_line_width      = 1.0f;
	_line_color      = color_t::DarkBlue;
	_line_dash_style = 0u;
}

//===========================================================================
void rectangle_shape::draw_diagram (void)
{
	draw_shape();
	draw_text();
}

diagram* rectangle_shape::clone (void)
{
	rectangle_shape* wd;


	wd = new rectangle_shape();

	// widget
	wd->set_model (get_model());
	wd->initialize();

	// diagram
	copy_diagram(wd, this);
	
	// rectangle_shape
	wd->_text                       = _text                      ;
	wd->_text_color                 = _text_color                ;
	wd->_text_format_alignment      = _text_format_alignment     ;
	wd->_text_format_line_alignment = _text_format_line_alignment;
	wd->_text_font_familyname       = _text_font_familyname      ;
	wd->_text_font_size             = _text_font_size            ;
	wd->_text_font_style            = _text_font_style           ;

	wd->_fill_color = _fill_color;
	wd->_fill_style = _fill_style;

	wd->_line_width      = _line_width     ;
	wd->_line_color      = _line_color     ;
	wd->_line_dash_style = _line_dash_style;

	return wd;
}

//===========================================================================
void rectangle_shape::draw_shape (void)
{
	graphic_t g;
	rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer1.set_model     ( get_model() );
	_renderer1.set_rectangle ( r );

	_renderer1.set_fill_color (get_fill_color());

	_renderer1.set_line_width      (get_line_width());
	_renderer1.set_line_color      (get_line_color());
	_renderer1.set_line_dash_style (get_line_dash_style());


	_renderer1.render(g);
}

void rectangle_shape::draw_text (void)
{
	graphic_t g;
	rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer2.set_model     ( get_model() );
	_renderer2.set_rectangle ( r );

	_renderer2.set_text      ( get_text() );
	_renderer2.set_text_color( get_text_color () );
	_renderer2.set_text_font ( get_text_font_familyname(), get_text_font_size(), get_text_font_style() );
	_renderer2.set_text_format_alignment( get_text_format_alignment(), get_text_format_line_alignment() );

	_renderer2.render(g);
}

//===========================================================================
std::string rectangle_shape::get_text                       (void)          { return _text                      ; }
color_t     rectangle_shape::get_text_color                 (void)          { return _text_color                ; }
cx::uint_t  rectangle_shape::get_text_format_alignment      (void)          { return _text_format_alignment     ; }
cx::uint_t  rectangle_shape::get_text_format_line_alignment (void)          { return _text_format_line_alignment; }
std::string rectangle_shape::get_text_font_familyname       (void)          { return _text_font_familyname      ; }
cx::float_t rectangle_shape::get_text_font_size             (void)          { return _text_font_size            ; }
cx::uint_t  rectangle_shape::get_text_font_style            (void)          { return _text_font_style           ; }
void        rectangle_shape::set_text                       (std::string v) { if(_text                       != v){ _text                       = v; set_property_changed(); } }
void        rectangle_shape::set_text_color                 (color_t     v) { if(_text_color                 != v){ _text_color                 = v; set_property_changed(); } }
void        rectangle_shape::set_text_format_alignment      (cx::uint_t  v) { if(_text_format_alignment      != v){ _text_format_alignment      = v; set_property_changed(); } }
void        rectangle_shape::set_text_format_line_alignment (cx::uint_t  v) { if(_text_format_line_alignment != v){ _text_format_line_alignment = v; set_property_changed(); } }
void        rectangle_shape::set_text_font_familyname       (std::string v) { if(_text_font_familyname       != v){ _text_font_familyname       = v; set_property_changed(); } }
void        rectangle_shape::set_text_font_size             (cx::float_t v) { if(_text_font_size             != v){ _text_font_size             = v; set_property_changed(); } }
void        rectangle_shape::set_text_font_style            (cx::uint_t  v) { if(_text_font_style            != v){ _text_font_style            = v; set_property_changed(); } }

color_t     rectangle_shape::get_fill_color (void)         { return _fill_color; }
cx::uint_t  rectangle_shape::get_fill_style (void)         { return _fill_style; }
void        rectangle_shape::set_fill_color (color_t    v) { if(_fill_color != v){ _fill_color = v; set_property_changed(); } }
void        rectangle_shape::set_fill_style (cx::uint_t v) { if(_fill_style != v){ _fill_style = v; set_property_changed(); } }

cx::float_t rectangle_shape::get_line_width      (void)          { return _line_width     ; }
color_t     rectangle_shape::get_line_color      (void)          { return _line_color     ; }
cx::uint_t  rectangle_shape::get_line_dash_style (void)          { return _line_dash_style; }
void        rectangle_shape::set_line_width      (cx::float_t v) { if(_line_width      != v){ _line_width      = v; set_property_changed(); } }
void        rectangle_shape::set_line_color      (color_t     v) { if(_line_color      != v){ _line_color      = v; set_property_changed(); } }
void        rectangle_shape::set_line_dash_style (cx::uint_t  v) { if(_line_dash_style != v){ _line_dash_style = v; set_property_changed(); } }



/////////////////////////////////////////////////////////////////////////////
//
// Class: rectangle_shape_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void rectangle_shape_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
	rectangle_shape* wd = cx_gw_dynamic_cast<rectangle_shape*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}

void rectangle_shape_event_handler::on_mouse_hover(widget_mouse_event* e)
{
	rectangle_shape* wd = cx_gw_dynamic_cast<rectangle_shape*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}

void rectangle_shape_event_handler::on_mouse_leave(widget_mouse_event* e)
{
	rectangle_shape* wd = cx_gw_dynamic_cast<rectangle_shape*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: rectangle_shape_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::bool_t rectangle_shape_json_iostream::read(document_reader* io, widget* w, model* m)
{
	//-----------------------------------------------------------------------
	if (false==diagram_json_iostream::read(io, w, m))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	json_document_reader* json_io = cx_gw_dynamic_cast<json_document_reader*>(io);
	rectangle_shape* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<rectangle_shape*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


	//-----------------------------------------------------------------------
	anchor* wa;


	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[0]); wa->set_point(wd->get_point_container()[0]);
	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[1]); wa->set_point(wd->get_point_container()[1]);
	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[2]); wa->set_point(wd->get_point_container()[3]);
	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[3]); wa->set_point(wd->get_point_container()[2]);


	//-----------------------------------------------------------------------
	cx::json_dom_node* current = json_io->get_json_current();


	if (current->_type != JSON_OBJECT_BEGIN)
	{
		return false;
	}

		
	//-----------------------------------------------------------------------
	cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(current);


	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text ( get_json_value_string(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글색상"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_color ( get_json_value_color(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글정렬"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_format_alignment ( get_json_value_uint(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글세로정렬"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_format_line_alignment ( get_json_value_uint(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글꼴"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_font_familyname ( get_json_value_string(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글꼴크기"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_font_size ( get_json_value_float(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("글꼴모양"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_text_font_style ( get_json_value_uint(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("채움색상"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_fill_color ( get_json_value_color(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("채움모양"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_fill_style ( get_json_value_uint(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("선크기"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_line_width ( get_json_value_float(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("선색상"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_line_color ( get_json_value_color(data->to_string()) );
	}

	
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("선모양"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_line_dash_style ( get_json_value_uint(data->to_string()) );
	}

	
	return true;
}

cx::bool_t rectangle_shape_json_iostream::write(document_writer* io, widget* w, model* m)
{
	if (false==diagram_json_iostream::write(io, w, m))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	json_document_writer* json_io = cx_gw_dynamic_cast<json_document_writer*>(io);
	rectangle_shape* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<rectangle_shape*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


	//-----------------------------------------------------------------------
	json_io->get_json_writer()->value( "글"        , get_json_string      ( wd->get_text                      () ) );
	json_io->get_json_writer()->value( "글색상"    , get_json_string_color( wd->get_text_color                () ) );
	json_io->get_json_writer()->value( "글정렬"    , get_json_string_uint ( wd->get_text_format_alignment     () ) );
	json_io->get_json_writer()->value( "글세로정렬", get_json_string_uint ( wd->get_text_format_line_alignment() ) );
	json_io->get_json_writer()->value( "글꼴"      , get_json_string      ( wd->get_text_font_familyname      () ) );
	json_io->get_json_writer()->value( "글꼴크기"  , get_json_string_float( wd->get_text_font_size            () ) );
	json_io->get_json_writer()->value( "글꼴모양"  , get_json_string_uint ( wd->get_text_font_style           () ) );

	json_io->get_json_writer()->value( "채움색상", get_json_string_color( wd->get_fill_color() ) );
	json_io->get_json_writer()->value( "채움모양", get_json_string_uint ( wd->get_fill_style() ) );

	json_io->get_json_writer()->value( "선크기", get_json_string_float( wd->get_line_width     () ) );
	json_io->get_json_writer()->value( "선색상", get_json_string_color( wd->get_line_color     () ) );
	json_io->get_json_writer()->value( "선모양", get_json_string_uint ( wd->get_line_dash_style() ) );

	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
