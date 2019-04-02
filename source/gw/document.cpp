/////////////////////////////////////////////////////////////////////////////
//
// File: document.cpp
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
// Class: document_reader
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
document_reader::document_reader()
{
}

document_reader::~document_reader()
{
}

//===========================================================================
named_widget_iostream_collection* document_reader::get_widget_iostream(void)
{
	return &_widget_iostream;
}

//===========================================================================
cx::bool_t document_reader::create (widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	widget_entry_pointer_container_t::iterator i;
	
	widget_entry*    we;
	std::string      wc;
	widget_iostream* wios;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);

		wc   = we->get_widget_class();
		wios = we->get_widget_iostream_factory()->create_instance();

		if (false == get_widget_iostream()->add(wc, wios))
		{
			delete wios;

			return false;
		}
	}


	return true;
}

void document_reader::destroy (void)
{
	get_widget_iostream()->delete_container();
}

//===========================================================================
cx::bool_t document_reader::read (model* m, widget_collection* collection)
{
	return false;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: document_writer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
document_writer::document_writer()
{
}

document_writer::~document_writer()
{
}

//===========================================================================
named_widget_iostream_collection* document_writer::get_widget_iostream(void)
{
	return &_widget_iostream;
}

//===========================================================================
cx::bool_t document_writer::create (widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	widget_entry_pointer_container_t::iterator i;
	
	widget_entry*    we;
	std::string      wc;
	widget_iostream* wios;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);

		wc   = we->get_widget_class();
		wios = we->get_widget_iostream_factory()->create_instance();

		if (false == get_widget_iostream()->add(wc, wios))
		{
			delete wios;

			return false;
		}
	}


	return true;
}

void document_writer::destroy (void)
{
	get_widget_iostream()->delete_container();
}

//===========================================================================
cx::bool_t document_writer::write(model* m, widget_collection* collection)
{
	return false;
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}


