/////////////////////////////////////////////////////////////////////////////
//
// File: diagram.cpp
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
diagram::diagram()
{
	_visible   = true;
	_enabled   = true;

	_pressed   = false;
	_selected  = false;
}

diagram::~diagram()
{
	get_child()->delete_container();
}

//===========================================================================
std::string diagram::get_registered_name (void)
{
	return "widget.diagram";
}

//===========================================================================
void diagram::set_model (model* model)
{
	widget::set_model(model);

//	_renderer1.set_model(model);
}

std::string diagram::get_class (void)
{
	return get_registered_name();
}

void diagram::set_name (std::string name)
{
	if ( get_name()!=name )
	{
		widget::set_name(name);

		set_property_changed();
	}
}

//===========================================================================
void diagram::initialize (void)
{
	point_t lt(coordinates_t(  0), coordinates_t(  0));
	point_t rt(coordinates_t(100), coordinates_t(  0));
	point_t rb(coordinates_t(100), coordinates_t(100));
	point_t lb(coordinates_t(  0), coordinates_t(100));


	get_point_container().push_back(lt);
	get_point_container().push_back(rt);
	get_point_container().push_back(rb);
	get_point_container().push_back(lb);


	anchor* wa_lt;
	anchor* wa_rt;
	anchor* wa_lb;
	anchor* wa_rb;


	wa_lt = new anchor(ANCHOR_ID_LT, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_lt);
	wa_rt = new anchor(ANCHOR_ID_RT, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_rt);
	wa_lb = new anchor(ANCHOR_ID_LB, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_lb);
	wa_rb = new anchor(ANCHOR_ID_RB, anchor::TYPE_RESIZE); get_child()->get_container().push_back(wa_rb);

	get_child()->set_model(get_model());
	get_child()->initialize();
	get_child()->set_parent(this);

	wa_lt->set_point(lt);
	wa_rt->set_point(rt);
	wa_lb->set_point(lb);
	wa_rb->set_point(rb);


//	widget::initialize();
}

cx::bool_t diagram::is_point_in (point_t p)
{
	return get_bounds().is_point_in(p);
}

void diagram::move (point_t offset)
{
	if (offset.is_zero())
	{
		return;
	}


	point_container_t::iterator i;


	for (i = get_point_container().begin(); i != get_point_container().end(); i++)
	{
		(*i).offset(offset);
	}

	
	get_child()->move(offset);


	set_point_changed();
}

void diagram::set_bounds (rectangle_t bounds)
{
	CX_DEBUG_ASSERT(0);

#if 0
	get_point_container()[0].set(bounds._p0._x, bounds._p0._y);
	get_point_container()[1].set(bounds._p1._x, bounds._p0._y);
	get_point_container()[2].set(bounds._p1._x, bounds._p1._y);
	get_point_container()[3].set(bounds._p0._x, bounds._p1._y);

	widget::set_bounds(bounds);

	set_property_changed();
#endif
}

void diagram::draw (void)
{
	model* m;


	m = get_model();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m);


	if (get_design()->get_diagram_mode() != DIAGRAM_MODE_EDIT)
	{
		if (false==get_visible())
		{
			return;
		}
	}


	if (is_point_container_on_rectangle(get_point_container(), m->get_view()->get_viewport_world_rectangle()))
	{
		draw_diagram();
		draw_diagram_bounds();
	}


	widget::draw(); // child anchor
}

//===========================================================================
design* diagram::get_design (void)
{
	design* m;


	m = cx_gw_dynamic_cast<design*>(get_model());

	return m;
}

//===========================================================================
void diagram::draw_diagram (void)
{
	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();
	r = get_bounds();


	_renderer1.set_model      ( get_model() );
	_renderer1.set_rectangle  ( r );
	_renderer1.set_fill_color ( color_t(0xECu,0xECu,0xECu) );

	_renderer1.render(g);
}

void diagram::draw_diagram_bounds(void)
{
	if (DIAGRAM_MODE_EDIT != get_design()->get_diagram_mode())
	{
		return;
	}
	if (!get_selected())
	{
		return;
	}


	graphic_t   g;
	rectangle_t r;


	g = get_model()->get_graphic();


	point_container_t anchor_point_container;

	widget_pointer_container_t::iterator i;
	widget* w;
	anchor* wa;


	for (i = get_child()->get_container().begin(); i != get_child()->get_container().end(); i++)
	{
		w = (*i);

		wa = get_design()->cast_anchor(w);
		if (wa)
		{
			anchor_point_container.push_back(wa->get_point());
		}
	}

	r = point_container_to_rectangle(anchor_point_container);


	_renderer0.set_model(get_model());
	_renderer0.set_rectangle(r);

	_renderer0.set_fill_color(color_t(0x80, 0x80, 0xff, 0x00));
	_renderer0.set_line_color(color_t(0x00, 0x00, 0x80, 0xFF));
	_renderer0.set_line_width(1.0f);
	_renderer0.set_line_dash_style();

	_renderer0.render(g);
}

//===========================================================================
cx::bool_t diagram::get_visible(void)
{
	return _visible;
}

void diagram::set_visible(cx::bool_t v)
{
	if (_visible != v)
	{
		_visible = v;
		set_property_changed();
	}
}

//===========================================================================
cx::bool_t diagram::get_enabled(void)
{
	return _enabled;
}

void diagram::set_enabled(cx::bool_t v)
{
	if (_enabled != v)
	{
		_enabled = v;
		set_property_changed();
	}
}

//===========================================================================
void diagram::set_pressed(cx::bool_t v)
{
	if (false==get_enabled())
	{
		v = false;
	}

	if (_pressed != v)
	{
		_pressed = v;
		set_status_changed();
	}
}

cx::bool_t diagram::get_pressed(void)
{
	return _pressed;
}

//===========================================================================
cx::bool_t diagram::get_selected(void)
{
	return _selected;
}

void diagram::set_selected(cx::bool_t v)
{
	if (_selected != v)
	{
		_selected = v;
		set_status_changed();
	}

	CX_DEBUG_ASSERT(CX_NULL_POINTER != get_design());

	if (get_design()->get_diagram_mode() == DIAGRAM_MODE_EDIT)
	{
		widget_pointer_container_t::iterator i;
		widget*  w;
		anchor*  wa;

		for (i = get_child()->get_container().begin(); i != get_child()->get_container().end(); i++)
		{
			w = (*i);

			wa = get_design()->cast_anchor(w);
			if (wa)
			{
				wa->set_visible(_selected);
			}
		}
	}
}

//===========================================================================
void diagram::on_set_anchor_point(anchor* wa, point_t& p)
{
	anchor* wa_lt;
	anchor* wa_rt;
	anchor* wa_lb;
	anchor* wa_rb;


	wa_lt = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[0]); 
	wa_rt = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[1]); 
	wa_lb = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[2]); 
	wa_rb = cx_gw_dynamic_cast<anchor*>(get_child()->get_container()[3]); 


	point_t lt;
	point_t rt;
	point_t lb;
	point_t rb;


	lt = wa_lt->get_point();
	rt = wa_rt->get_point();
	lb = wa_lb->get_point();
	rb = wa_rb->get_point();


	cx::uint_t anchor_id; 
	
	
	anchor_id = wa->get_id();
	switch (anchor_id)
	{
	case ANCHOR_ID_LT:
		if (p == lb){ return; }
		if (p == rt){ return; }
		if (p == rb){ return; }
		if (rb._x <= p._x){ return; }
		if (rb._y <= p._y){ return; }

		lb._x = p._x;
		rt._y = p._y;
		lt    = p;
		break;

	case ANCHOR_ID_RT:
		if (p == lt){ return; }
		if (p == lb){ return; }
		if (p == rb){ return; }
		if (lb._x >= p._x){ return; }
		if (lb._y <= p._y){ return; }

		rb._x = p._x;
		lt._y = p._y;
		rt    = p;
		break;

	case ANCHOR_ID_RB:
		if (p == lt){ return; }
		if (p == lb){ return; }
		if (p == rt){ return; }
		if (lt._x >= p._x){ return; }
		if (lt._y >= p._y){ return; }

		rt._x = p._x;
		lb._y = p._y;
		rb    = p;
		break;

	case ANCHOR_ID_LB:
		if (p == lt){ return; }
		if (p == rt){ return; }
		if (p == rb){ return; }
		if (rt._x <= p._x){ return; }
		if (rt._y >= p._y){ return; }

		lt._x = p._x;
		rb._y = p._y;
		lb    = p;
		break;

	default:
		return;
		break;
	}


	wa_lt->set_point(lt);
	wa_rt->set_point(rt);
	wa_lb->set_point(lb);
	wa_rb->set_point(rb);


	get_point_container()[0].set(lt);
	get_point_container()[1].set(rt);
	get_point_container()[2].set(rb);
	get_point_container()[3].set(lb);


	set_point_changed();
}

diagram* diagram::clone (void)
{
	diagram* wd1;
	diagram* wd2;

	anchor* wa1;
	anchor* wa2;

	diagram* wd;


	wd = new diagram();

	wd1 = this;
	wd2 = wd;


	// widget
	wd2->set_model (wd1->get_model());
	wd2->initialize();

	wd2->set_name (wd1->get_name());

	wd2->get_point_container()[0].set(wd1->get_point_container()[0]);
	wd2->get_point_container()[1].set(wd1->get_point_container()[1]);
	wd2->get_point_container()[2].set(wd1->get_point_container()[2]);
	wd2->get_point_container()[3].set(wd1->get_point_container()[3]);

	wa1 = cx_gw_dynamic_cast<anchor*>(wd1->get_child()->get_container()[0]);
	wa2 = cx_gw_dynamic_cast<anchor*>(wd2->get_child()->get_container()[0]); wa2->set_point(wa1->get_point());
	wa1 = cx_gw_dynamic_cast<anchor*>(wd1->get_child()->get_container()[1]);
	wa2 = cx_gw_dynamic_cast<anchor*>(wd2->get_child()->get_container()[1]); wa2->set_point(wa1->get_point());
	wa1 = cx_gw_dynamic_cast<anchor*>(wd1->get_child()->get_container()[2]);
	wa2 = cx_gw_dynamic_cast<anchor*>(wd2->get_child()->get_container()[2]); wa2->set_point(wa1->get_point());
	wa1 = cx_gw_dynamic_cast<anchor*>(wd1->get_child()->get_container()[3]);
	wa2 = cx_gw_dynamic_cast<anchor*>(wd2->get_child()->get_container()[3]); wa2->set_point(wa1->get_point());

	wd2->set_parent(wd1->get_parent());
	

	// diagram
	wd2->set_visible (wd1->get_visible ());
	wd2->set_enabled (wd1->get_enabled ());
	wd2->set_pressed (wd1->get_pressed ());
	wd2->set_selected(wd1->get_selected());


	return wd;
}

//===========================================================================
void diagram::set_status_changed (void)
{
	set_redraw();
}

void diagram::set_property_changed (void)
{
	set_redraw();


	diagram_event e;


	e._code = EC_DIAGRAM_PROPERTY_CHANGED;
	e._diagram = this;

	
	design* m = get_design();


	if (m)
	{
		m->on_event(&e);
	}
}

void diagram::set_point_changed (void)
{
	set_property_changed ();
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void diagram_event_handler::on_mouse_pressed (widget_mouse_event* e)
{
	diagram* wd = cx_gw_dynamic_cast<diagram*>(e->_widget);

	
	wd->set_pressed(true);
}

void diagram_event_handler::on_mouse_released (widget_mouse_event* e)
{
	diagram* wd = cx_gw_dynamic_cast<diagram*>(e->_widget);

	
	wd->set_pressed(false);
}

void diagram_event_handler::on_mouse_clicked (widget_mouse_event* e)
{
}

void diagram_event_handler::on_mouse_dbclicked (widget_mouse_event* e)
{
}

void diagram_event_handler::on_mouse_hover (widget_mouse_event* e)
{
}

void diagram_event_handler::on_mouse_leave (widget_mouse_event* e)
{
}

void diagram_event_handler::on_mouse_dragging (widget_mouse_event* e)
{
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _json_document_diagram_class   = "형식";
static cx::char_t* _json_document_diagram_name    = "이름";
static cx::char_t* _json_document_diagram_point   = "좌표";
static cx::char_t* _json_document_diagram_anchor  = "기준점";
static cx::char_t* _json_document_diagram_visible = "보이기"; 
static cx::char_t* _json_document_diagram_enabled = "동작가능";

//===========================================================================
diagram_json_iostream::diagram_json_iostream()
{
}

diagram_json_iostream::~diagram_json_iostream()
{
}

//===========================================================================
cx::bool_t diagram_json_iostream::read(document_reader* io, widget* w, model* m)
{
	//-----------------------------------------------------------------------
	json_document_reader* json_io = cx_gw_dynamic_cast<json_document_reader*>(io);
	diagram* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<diagram*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


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


	// widget
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string(_json_document_diagram_name));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_name ( get_json_value_string(data->to_string()) );
	}
	

	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string(_json_document_diagram_point));
	if (node)
	{
		if (node->_type != JSON_ARRAY_BEGIN)
		{
			return false;
		}


		cx::json_dom_node_array* array = cx_gw_dynamic_cast<cx::json_dom_node_array*>(node); 


		//-------------------------------------------------------------------
		std::vector<cx::json_dom_node*>::iterator i;
		point_container_t::iterator j;
		point_t p;


		for (i=array->_collection.begin(), j=wd->get_point_container().begin(); i!=array->_collection.end() && j!=wd->get_point_container().end(); i++, j++)
		{
			node = (*i);

			if (JSON_OBJECT_BEGIN==node->_type)
			{
				cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(node);


				//-----------------------------------------------------------
				node = object->find("x");
				if (node)
				{
					if (node->_type==JSON_STRING)
					{
						cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node);

						
						p._x = get_json_value_float(data->to_string());
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

				//-----------------------------------------------------------
				node = object->find("y");
				if (node)
				{
					if (node->_type==JSON_STRING)
					{
						cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node);

						
						p._y = get_json_value_float(data->to_string());
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

				//-----------------------------------------------------------
				(*j).set(&p);
			}
			else
			{
				return false;
			}
		}


		//-------------------------------------------------------------------
		//set_json_current(current);
	}


	//-----------------------------------------------------------------------
	anchor* wa;


	if (wd->get_class()==diagram::get_registered_name())
	{
		wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[0]); wa->set_point(wd->get_point_container()[0]);
		wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[1]); wa->set_point(wd->get_point_container()[1]);
		wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[2]); wa->set_point(wd->get_point_container()[3]);
		wa = cx_gw_dynamic_cast<anchor*>(wd->get_child()->get_container()[3]); wa->set_point(wd->get_point_container()[2]);
	}


	// diagram
	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string(_json_document_diagram_visible));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_visible ( get_json_value_bool(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string(_json_document_diagram_enabled));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		wd->set_visible ( get_json_value_bool(data->to_string()) );
	}


	return true;
}

cx::bool_t diagram_json_iostream::write(document_writer* io, widget* w, model* m)
{
	//-----------------------------------------------------------------------
	json_document_writer* json_io = cx_gw_dynamic_cast<json_document_writer*>(io);
	diagram* wd;
	design*  md;


	wd = cx_gw_dynamic_cast<diagram*>(w);
	md = cx_gw_dynamic_cast<design*>(m);


	// widget
	//-----------------------------------------------------------------------
	json_io->get_json_writer()->value(_json_document_diagram_class, wd->get_class());


	//-----------------------------------------------------------------------
	json_io->get_json_writer()->value(_json_document_diagram_name, wd->get_name());


	//-----------------------------------------------------------------------
	json_io->get_json_writer()->key(_json_document_diagram_point);
	json_io->get_json_writer()->array_begin();

	{	
		point_container_t::iterator i;

		point_t p;

		for (i=wd->get_point_container().begin(); i!=wd->get_point_container().end(); i++)
		{
			p = (*i);
			json_io->get_json_writer()->object_begin();
			json_io->get_json_writer()->value("x", get_json_string_float(p._x));
			json_io->get_json_writer()->value("y", get_json_string_float(p._y));
			json_io->get_json_writer()->object_end();
		}
	}

	json_io->get_json_writer()->array_end();
	

	//-----------------------------------------------------------------------
/*
	json_io->get_json_writer()->key(_json_document_diagram_anchor);
	json_io->get_json_writer()->array_begin();

	{
		widget_pointer_container_t::iterator i;

		widget*  w;
		anchor*  wa;

		point_t p;


		for (i=wd->get_child()->get_container().begin(); i!=wd->get_child()->get_container().end(); i++)
		{
			w = (*i);

			wa = md->cast_anchor(w);
			if (wa)
			{
				p = wa->get_point();

				json_io->get_json_writer()->object_begin();
				json_io->get_json_writer()->value("x", get_json_string_float(p._x));
				json_io->get_json_writer()->value("y", get_json_string_float(p._y));
				json_io->get_json_writer()->object_end();
			}
		}	
	}

	json_io->get_json_writer()->array_end();
*/

	// diagram
	//-----------------------------------------------------------------------
	json_io->get_json_writer()->value(_json_document_diagram_visible, get_json_string_bool(wd->get_visible()) );
	json_io->get_json_writer()->value(_json_document_diagram_enabled, get_json_string_bool(wd->get_enabled()) );


	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
