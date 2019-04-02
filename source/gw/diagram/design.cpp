/////////////////////////////////////////////////////////////////////////////
//
// File: design.cpp
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
//
// Class: design
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
design::design()
{
}

design::~design()
{
}

//===========================================================================
cx::bool_t design::create (widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	get_resource()->set_model(this);


	//-----------------------------------------------------------------------
	get_view()->set_model(this);
	get_view()->set_background_color(color_t::White);
	get_view()->set_wolrd_rectangle(rectangle_t(1920, 1080));
	get_view()->set_grid_size(5, 5);
	get_view()->set_grid_visible(false);


	//-----------------------------------------------------------------------
	get_window_event_handler()->set_model(this);
	

	//-----------------------------------------------------------------------
	widget_entry_pointer_container_t::iterator i;

	widget_entry*         we;
	std::string           wc;
	widget_event_handler* weh;

	widget*  w;
	diagram* wd;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);


		w = we->get_widget_factory()->create_instance();

		wd = cast_diagram(w);
		if (wd)
		{
			wd->set_model(this);
			wd->initialize();

			if (false == get_diagram_creator()->register_entry(wd))
			{
				delete wd;

				return false;
			}


			wc  = we->get_widget_class();
			weh = we->get_widget_event_handler_factory()->create_instance();

			if (false == get_widget_event_handler()->add(wc, weh))
			{
				return false;
			}
		}
		else
		{
			delete w;


			wc  = we->get_widget_class();
			weh = we->get_widget_event_handler_factory()->create_instance();

			if (false == get_widget_event_handler()->add(wc, weh))
			{
				return false;
			}
		}
	}


	return true;
}

void design::destroy (void)
{
	//-----------------------------------------------------------------------
	get_widget()->delete_container();


	//-----------------------------------------------------------------------
	get_diagram_creator()->delete_container ();


	//-----------------------------------------------------------------------
	get_widget_event_handler()->delete_container();

	get_resource()->delete_container();
}

//===========================================================================
void design::on_event (event* e)
{
	model::on_event(e);

	switch (e->_code)
	{
	case EC_DIAGRAM_PROPERTY_CHANGED:
		on_diagram_property_changed (cx_gw_dynamic_cast<diagram_event*>(e));
		break;

	default:
		break;
	}
}

void design::on_widget_mouse_clicked (widget_mouse_event* e)
{
	widget* w = e->_widget;


	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", w->get_class().c_str());
}

void design::on_widget_mouse_dbclicked (widget_mouse_event* e)
{
	widget* w = e->_widget;


	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", w->get_class().c_str());
}

//===========================================================================
diagram_mode_t design::get_diagram_mode(void)
{
	return DIAGRAM_MODE_DESIGN;
}

diagram_creator* design::get_diagram_creator (void)
{
	return &_diagram_creator;
}

void design::on_diagram_property_changed (diagram_event* e)
{

}

//===========================================================================
diagram* design::cast_diagram (widget* w)
{
	diagram* wd = CX_NULL_POINTER;;


	if (w->get_class() != anchor::get_registered_name())
	{
		wd = cx_gw_dynamic_cast<diagram*>(w);
	}

	return wd;
}

anchor* design::cast_anchor (widget* w)
{
	anchor* wa = CX_NULL_POINTER;;


	if (w->get_class() == anchor::get_registered_name())
	{
		wa = cx_gw_dynamic_cast<anchor*>(w);
	}
	
	return wa;
}

//===========================================================================
void design::clear (void)
{
	//-----------------------------------------------------------------------
	get_widget()->delete_container();


	//-----------------------------------------------------------------------
	set_redraw();
}

//===========================================================================
cx::bool_t design::read (document_reader* io)
{
	//-----------------------------------------------------------------------
	widget_collection collection;


	if (false==io->read(this, &collection))
	{
		collection.delete_container();


		return false;
	}


	//-----------------------------------------------------------------------
	clear();


	//-----------------------------------------------------------------------
	diagram* wd_clone;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	

	//-----------------------------------------------------------------------
	for (i =collection.get_container().begin();
	     i!=collection.get_container().end();
		 i++)
	{
		w = (*i);

		wd = cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();

			get_widget()->get_container().push_back(wd_clone);
		}
	}


	//-----------------------------------------------------------------------
	collection.delete_container();


	//-----------------------------------------------------------------------
	set_redraw();


	return true;
}

cx::bool_t design::write (document_writer* io)
{
	//-----------------------------------------------------------------------
	return io->write(this, get_widget());
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
