#ifndef INCLUDED__CX__GW__WIDGET_IOSTREAM__HPP
#define INCLUDED__CX__GW__WIDGET_IOSTREAM__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: widget_iostream.hpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





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
class widget_iostream
{
public:
	widget_iostream();
	virtual ~widget_iostream();

public:
	virtual cx::bool_t read (document_reader* io, widget* w, model* m);
	virtual cx::bool_t write(document_writer* io, widget* w, model* m);
};


	
/////////////////////////////////////////////////////////////////////////////
//
// Class: named_widget_iostream_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class named_widget_iostream_collection
{
private:
	named_widget_iostream_pointer_container_t _container;

public:
	named_widget_iostream_collection();
	virtual ~named_widget_iostream_collection();

public:
	virtual named_widget_iostream_pointer_container_t& get_container (void);

public:
	virtual void delete_container (void);

public:
	virtual widget_iostream* find(std::string name);
	virtual cx::bool_t       add (std::string name, widget_iostream* o);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


