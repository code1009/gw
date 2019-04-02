#ifndef INCLUDED__CX__GW__DOCUMENT__HPP
#define INCLUDED__CX__GW__DOCUMENT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: document.hpp
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
// Class: document_reader
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class document_reader
{
private:
	named_widget_iostream_collection _widget_iostream;

public:
	document_reader();
	virtual ~document_reader();

public:
	virtual named_widget_iostream_collection* get_widget_iostream(void);

public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual cx::bool_t read (model* m, widget_collection* collection);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: document_writer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class document_writer
{
private:
	named_widget_iostream_collection _widget_iostream;

public:
	document_writer();
	virtual ~document_writer();

public:
	virtual named_widget_iostream_collection* get_widget_iostream(void);

public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual cx::bool_t write (model* m, widget_collection* collection);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


