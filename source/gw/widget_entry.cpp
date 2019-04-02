/////////////////////////////////////////////////////////////////////////////
//
// File: widget_entry.cpp
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
// Class: widget_entry
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_entry::widget_entry(
	std::string                   name                                 , 
	std::string                   description                          , 
	std::string                   widget_class                         , 
	widget_factory*               widget_factory_pointer               , 
	widget_event_handler_factory* widget_event_handler_factory_pointer ,
	widget_iostream_factory*      widget_iostream_factory_pointer      )
{
	set(
		name                                 , 
		description                          , 
		widget_class                         , 
		widget_factory_pointer               , 
		widget_event_handler_factory_pointer ,
		widget_iostream_factory_pointer      );
}

widget_entry::~widget_entry()
{
}


//===========================================================================
std::string                   widget_entry::get_name                         (void) { return _name                        ; }
std::string                   widget_entry::get_description                  (void) { return _description                 ; }
std::string                   widget_entry::get_widget_class                 (void) { return _widget_class                ; }
widget_factory*               widget_entry::get_widget_factory               (void) { return _widget_factory              ; }
widget_event_handler_factory* widget_entry::get_widget_event_handler_factory (void) { return _widget_event_handler_factory; }
widget_iostream_factory*      widget_entry::get_widget_iostream_factory      (void) { return _widget_iostream_factory     ; }

//===========================================================================
void widget_entry::set(
	std::string                   name                                 , 
	std::string                   description                          , 
	std::string                   widget_class                         , 
	widget_factory*               widget_factory_pointer               , 
	widget_event_handler_factory* widget_event_handler_factory_pointer ,
	widget_iostream_factory*      widget_iostream_factory_pointer      )
{
	_name                         = name                                ;
	_description                  = description                         ;
	_widget_class                 = widget_class                        ;
	_widget_factory               = widget_factory_pointer              ;
	_widget_event_handler_factory = widget_event_handler_factory_pointer;
	_widget_iostream_factory      = widget_iostream_factory_pointer     ;
}

//===========================================================================
void widget_entry::delete_instance (void)
{
	_name        .clear();
	_description .clear();
	_widget_class.clear();

	if (_widget_factory)
	{
		delete _widget_factory;
	}

	if (_widget_event_handler_factory)
	{
		delete _widget_event_handler_factory;
	}

	if (_widget_iostream_factory)
	{
		delete _widget_iostream_factory;
	}

	_widget_factory               = CX_NULL_POINTER;
	_widget_event_handler_factory = CX_NULL_POINTER;
	_widget_iostream_factory      = CX_NULL_POINTER;

	delete this;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_entry_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_entry_collection::widget_entry_collection()
{
}

widget_entry_collection::~widget_entry_collection()
{
	delete_container();
}

//===========================================================================
widget_entry_pointer_container_t& widget_entry_collection::get_container(void)
{
	return _container;
}

//===========================================================================
void widget_entry_collection::delete_container(void)
{
	widget_entry_pointer_container_t::iterator i;
	widget_entry* we;


	for (i = get_container().begin(); i != get_container().end(); i++)
	{
		we = (*i);

		if (we)
		{
			we->delete_instance();
		}
	}

	get_container().clear();
}



////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
