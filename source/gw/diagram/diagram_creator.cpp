/////////////////////////////////////////////////////////////////////////////
//
// File: diagram_creator.cpp
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
// Class: diagram_creator
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_creator::diagram_creator()
{
}

diagram_creator::~diagram_creator()
{
	delete_container();
}

//===========================================================================
named_diagram_pointer_container_t& diagram_creator::get_container (void)
{
	return _container;
}

void diagram_creator::delete_container (void)
{
	named_diagram_pointer_container_t::iterator i;
	diagram* wd;
	

	for (i=get_container().begin(); i!=get_container().end(); i++)
	{
		wd = (*i).second;

		if (wd)
		{
			wd->delete_instance();
		}
	}

	get_container().clear();
}

//===========================================================================
diagram* diagram_creator::find(std::string name)
{
	diagram* wd;


	wd = CX_NULL_POINTER;


	named_diagram_pointer_container_t::iterator i;
	
	
	i = get_container().find(name);
	if (i!=get_container().end())
	{
		wd=(*i).second;
	}


	return wd;
}

cx::bool_t diagram_creator::register_entry(diagram* wd)
{
	diagram*    wd_factory;
	std::string name;


	name = wd->get_class();

	wd_factory = find(name);
	if (wd_factory != CX_NULL_POINTER)
	{
		return false;
	}

	get_container()[name] = wd;

	return true;
}

//===========================================================================
diagram* diagram_creator::create_diagram(std::string name)
{
	//-----------------------------------------------------------------------
	diagram* wd;


	wd = find(name);
	if (wd == CX_NULL_POINTER)
	{
		return CX_NULL_POINTER;
	}


	//-----------------------------------------------------------------------
	diagram* wd_clone;


	wd_clone = wd->clone();

	return wd_clone;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
