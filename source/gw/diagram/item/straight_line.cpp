/////////////////////////////////////////////////////////////////////////////
//
// File: straight_line.cpp
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
straight_line::straight_line()
{
}

straight_line::~straight_line()
{
}

//===========================================================================
std::string straight_line::get_registered_name (void)
{
	return "widget.diagram.straight_line";
}

//===========================================================================
void straight_line::set_model (model* model)
{
	diagram::set_model(model);
}

std::string straight_line::get_class (void)
{
	return get_registered_name();
}

void straight_line::initialize (void)
{
	point_t lt(coordinates_t(  0), coordinates_t(  0));
	point_t rb(coordinates_t(100), coordinates_t(100));


	get_point_container().push_back(lt);
	get_point_container().push_back(rb);


	anchor* wa_lt;
	anchor* wa_rb;


	wa_lt = new anchor(ANCHOR_ID_LT, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_lt);
	wa_rb = new anchor(ANCHOR_ID_RB, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_rb);

	get_child()->set_model(get_model());
	get_child()->initialize();
	get_child()->set_parent(this);

	wa_lt->set_point(lt);
	wa_rb->set_point(rb);


	_line_width      = 1.0f;
	_line_color      = color_t::DarkBlue;
	_line_dash_style = 0u;
}

cx::bool_t straight_line::is_point_in (point_t p)
{
///	return get_bounds().is_point_in(p);

	if (is_point_on_line(p, get_point_container()[0], get_point_container()[1], _line_width+5.0f))
	{
		return true;
	}

	return false;
}

//===========================================================================
void straight_line::draw_diagram (void)
{
	draw_line();
}

diagram* straight_line::clone (void)
{
	straight_line* wd;


	wd = new straight_line();

	// widget
	wd->set_model (get_model());
	wd->initialize();

	// diagram
	copy_diagram(wd, this);
	
	// straight_line
	wd->_line_width      = _line_width     ;
	wd->_line_color      = _line_color     ;
	wd->_line_dash_style = _line_dash_style;

	return wd;
}

void straight_line::on_set_anchor_point(anchor* wa, point_t& p)
{
	anchor* wa_lt;
	anchor* wa_rb;


	wa_lt = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[0]); 
	wa_rb = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[1]); 


	point_t lt;
	point_t rb;


	lt = wa_lt->get_point();
	rb = wa_rb->get_point();


	cx::uint_t anchor_id; 
	
	
	anchor_id = wa->get_id();
	switch (anchor_id)
	{
	case ANCHOR_ID_LT:
		lt = p;
		break;
	case ANCHOR_ID_RB:
		rb = p;
		break;

	default:
		return;
		break;
	}


	wa_lt->set_point(lt);
	wa_rb->set_point(rb);


	get_point_container()[0].set(lt);
	get_point_container()[1].set(rb);


	set_point_changed();
}

//===========================================================================
void straight_line::draw_line (void)
{
	graphic_t g;


	g = get_model()->get_graphic();


	_renderer1.set_model ( get_model() );
	_renderer1.set_point ( get_point_container()[0], get_point_container()[1] );

	_renderer1.set_line_width      (get_line_width());
	_renderer1.set_line_color      (get_line_color());
	_renderer1.set_line_dash_style (get_line_dash_style());


	_renderer1.render(g);
}

//===========================================================================
cx::float_t straight_line::get_line_width      (void)          { return _line_width     ; }
color_t     straight_line::get_line_color      (void)          { return _line_color     ; }
cx::uint_t  straight_line::get_line_dash_style (void)          { return _line_dash_style; }
void        straight_line::set_line_width      (cx::float_t v) { if(_line_width      != v){ _line_width      = v; set_property_changed(); } }
void        straight_line::set_line_color      (color_t     v) { if(_line_color      != v){ _line_color      = v; set_property_changed(); } }
void        straight_line::set_line_dash_style (cx::uint_t  v) { if(_line_dash_style != v){ _line_dash_style = v; set_property_changed(); } }



/////////////////////////////////////////////////////////////////////////////
//
// Class: straight_line_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void straight_line_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
	straight_line* wd = cx_gw_dynamic_cast<straight_line*>(e->_widget);

	
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}

void straight_line_event_handler::on_mouse_hover(widget_mouse_event* e)
{
	straight_line* wd = cx_gw_dynamic_cast<straight_line*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}

void straight_line_event_handler::on_mouse_leave(widget_mouse_event* e)
{
	straight_line* wd = cx_gw_dynamic_cast<straight_line*>(e->_widget);


	CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd);
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: straight_line_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _json_document_diagram_line_width      = "선크기";
static cx::char_t* _json_document_diagram_line_color      = "선색상";
static cx::char_t* _json_document_diagram_line_dash_style = "선모양";

//===========================================================================
cx::bool_t straight_line_json_iostream::read(document_reader* io, widget* w, model* m)
{
	//-----------------------------------------------------------------------
	if (false==diagram_json_iostream::read(io, w, m))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	json_document_reader* json_io = cx_gw_dynamic_cast<json_document_reader*>(io);
	straight_line* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<straight_line*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


	//-----------------------------------------------------------------------
	anchor* wa;


	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[0]); wa->set_point(wd->get_point_container()[0]);
	wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[1]); wa->set_point(wd->get_point_container()[1]);


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
	node = object->find (get_json_value_string(_json_document_diagram_line_width));
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
	node = object->find (get_json_value_string(_json_document_diagram_line_color));
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
	node = object->find (get_json_value_string(_json_document_diagram_line_dash_style));
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

cx::bool_t straight_line_json_iostream::write(document_writer* io, widget* w, model* m)
{
	if (false==diagram_json_iostream::write(io, w, m))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	json_document_writer* json_io = cx_gw_dynamic_cast<json_document_writer*>(io);
	straight_line* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<straight_line*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


	//-----------------------------------------------------------------------
	json_io->get_json_writer()->value( _json_document_diagram_line_width     , get_json_string_float( wd->get_line_width     () ) );
	json_io->get_json_writer()->value( _json_document_diagram_line_color     , get_json_string_color( wd->get_line_color     () ) );
	json_io->get_json_writer()->value( _json_document_diagram_line_dash_style, get_json_string_uint ( wd->get_line_dash_style() ) );

	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
