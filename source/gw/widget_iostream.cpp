/////////////////////////////////////////////////////////////////////////////
//
// File: widget_iostream.cpp
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
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_iostream::widget_iostream()
{
}

widget_iostream::~widget_iostream()
{
}

//===========================================================================
cx::bool_t widget_iostream::read(document_reader* io, widget* w, model* m)
{
	return false;
}

cx::bool_t widget_iostream::write(document_writer* io, widget* w, model* m)
{
	return false;
}


	
/////////////////////////////////////////////////////////////////////////////
//
// Class: named_widget_iostream_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
named_widget_iostream_collection::named_widget_iostream_collection()
{
}

named_widget_iostream_collection::~named_widget_iostream_collection()
{
}

//===========================================================================
named_widget_iostream_pointer_container_t& named_widget_iostream_collection::get_container(void)
{
	return _container;
}

void named_widget_iostream_collection::delete_container(void)
{
	named_widget_iostream_pointer_container_t::iterator i;

	widget_iostream* p;


	for (i  = get_container().begin();
	     i != get_container().end();
	     i++)
	{
		p = (*i).second;

		delete p;
	}

	get_container().clear();
}


widget_iostream* named_widget_iostream_collection::find(std::string name)
{
	named_widget_iostream_pointer_container_t::iterator i;
	
	widget_iostream* p;


	p = CX_NULL_POINTER;
	i = get_container().find(name);
	if (i == get_container().end())
	{
		return p;
	}


	p = (*i).second;

	return p;
}

cx::bool_t named_widget_iostream_collection::add(std::string name, widget_iostream* o)
{
	widget_iostream* p;


	p = find(name);
	if (p != CX_NULL_POINTER)
	{
		return false;
	}


	get_container()[name] = o;

	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}


