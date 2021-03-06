﻿/////////////////////////////////////////////////////////////////////////////
//
// File: diagram_buffer.cpp
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
// Class: diagram_buffer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_buffer::diagram_buffer()
{
}

diagram_buffer::~diagram_buffer()
{
	clear();
}

//===========================================================================
widget_collection* diagram_buffer::get_widget (void)
{
	return &_widget;
}

//===========================================================================
void diagram_buffer::clear (void)
{
	get_widget()->delete_container();
}

//===========================================================================
cx::bool_t diagram_buffer::load (design* m)
{
	//-----------------------------------------------------------------------
	m->clear();


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	diagram* wd_clone;

	
	//-----------------------------------------------------------------------
	for (i =get_widget()->get_container().begin();
	     i!=get_widget()->get_container().end();
		 i++)
	{
		w = (*i);

		wd = m->cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();

			m->get_widget()->get_container().push_back(wd_clone);
		}
	}


	return true;
}

cx::bool_t diagram_buffer::save (design* m)
{
	//-----------------------------------------------------------------------
	clear();


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	diagram* wd_clone;

	
	//-----------------------------------------------------------------------
	for (i =m->get_widget()->get_container().begin();
	     i!=m->get_widget()->get_container().end();
		 i++)
	{
		w = (*i);

		wd = m->cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();

			get_widget()->get_container().push_back(wd_clone);
		}
	}


	return false;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
