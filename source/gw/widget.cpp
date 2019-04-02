/////////////////////////////////////////////////////////////////////////////
//
// File: widget.cpp
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
#include "header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template <typename TYPE>
static void delete_pointer(TYPE p)
{
	delete p;
}

template <typename TYPE>
static void delete_array_pointer(TYPE p)
{
	delete[]p;
}

template <typename PAIR>
static void delete_pair_second_pointer(PAIR p)
{
	delete p.second;
}

template <typename TYPE, typename CONTAINER>
static void delete_pointer_in_container(CONTAINER c)
{
	std::for_each(c.begin(), c.end(), delete_pointer < typename TYPE >);
}

template <typename TYPE, typename CONTAINER>
static void delete_pair_second_pointer_in_container(CONTAINER c)
{
	std::for_each(c.begin(), c.end(), delete_pair_second_pointer < typename TYPE >);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_collection::widget_collection()
{
}

widget_collection::~widget_collection()
{
}

//===========================================================================
widget_pointer_container_t& widget_collection::get_container (void)
{
	return _container;
}

void widget_collection::delete_container (void)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->delete_instance();
	}

	get_container().clear();
}

//===========================================================================
void widget_collection::set_model (model* model)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->set_model(model);
	}
}

void widget_collection::set_parent (widget* parent)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->set_parent(parent);
	}
}

void widget_collection::initialize (void)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->initialize();
	}
}

void widget_collection::move (point_t offset)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->move(offset);
	}
}

void widget_collection::draw (void)
{
	widget_pointer_container_t::iterator i;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		(*i)->draw();
	}
}

//===========================================================================
cx::bool_t widget_collection::is_in_collection (widget* w)
{
	widget_pointer_container_t::iterator i;


	i = std::find(get_container().begin(),get_container().end(),w);
	if (i==get_container().end())
	{
		return false;
	}

	return true;
}

//===========================================================================
widget* widget_collection::find (widget* x, point_t p)
{
	widget_pointer_container_t::reverse_iterator i;
	widget* w;
	widget* f;


	w = CX_NULL_POINTER;
	f = CX_NULL_POINTER;

	for (i = x->get_child()->get_container().rbegin();
		i != x->get_child()->get_container().rend();
		i++)
	{
		w = (*i);

		if (w->get_child()->get_container().size() > 0u)
		{
			f = find (w, p);
			if (CX_NULL_POINTER!=f)
			{
				return f;
			}
		}

		if (true == w->is_point_in(p))
		{
			return w;
		}
	}


	if (true == x->is_point_in(p))
	{
		return x;
	}


	return CX_NULL_POINTER;
}

widget* widget_collection::find (point_t p)
{
	widget_pointer_container_t::reverse_iterator i;
	widget* w;
	widget* f;


	w = CX_NULL_POINTER;
	f = CX_NULL_POINTER;

	for (i = get_container().rbegin();
		i != get_container().rend();
		i++)
	{
		w = (*i);


		f = find (w, p);
		if (CX_NULL_POINTER != f)
		{
			return f;
		}
	}


	return CX_NULL_POINTER;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget::widget()
{
	_model  = CX_NULL_POINTER;
	_parent = CX_NULL_POINTER;
}

widget::~widget()
{	
}

//===========================================================================
std::string widget::get_registered_name (void)
{
	return "widget";
}

//===========================================================================
model* widget::get_model (void)
{
	return _model;
}

void widget::set_model (model* m)
{
	_model = m;

	get_child()->set_model(m);
}

//===========================================================================
std::string widget::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
std::string widget::get_name (void)
{
	return _name;
}

void widget::set_name (std::string name)
{
	_name = name;
}

//===========================================================================
widget_collection* widget::get_child (void)
{
	return &_child;
}

void widget::delete_instance (void)
{
	get_child()->delete_container();

	delete this;
}

//===========================================================================
widget* widget::get_parent (void)
{
	return _parent;
}

void widget::set_parent (widget* parent)
{
	_parent = parent;
}

//===========================================================================
void widget::initialize (void)
{
	get_child()->initialize();

	get_child()->set_parent(this);
}

//===========================================================================
point_container_t& widget::get_point_container (void)
{
	return _point_container;
}
/*
point_t widget::get_point (cx::uint_t i)
{
	CX_DEBUG_ASSERT(i<get_point_container().size());

	return get_point_container()[i];
}

void widget::set_point (cx::uint_t i, point_t p)
{
	CX_DEBUG_ASSERT(i<get_point_container().size());

	get_point_container()[i] = p;
}
*/
//===========================================================================
cx::bool_t widget::is_point_in (point_t p)
{
	return get_bounds().is_point_in(p);
}

//===========================================================================
void widget::move (point_t offset)
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


	set_redraw ();
}

//===========================================================================
rectangle_t widget::get_bounds (void)
{
	return point_container_to_rectangle(get_point_container());
}

void widget::set_bounds (rectangle_t bounds)
{
	set_redraw();
}

//===========================================================================
void widget::set_redraw (void)
{
	if (CX_NULL_POINTER != get_model())
	{
		get_model()->set_redraw(this);
	}
}

void widget::draw (void)
{
	get_child()->draw();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
