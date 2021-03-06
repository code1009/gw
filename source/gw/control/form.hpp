﻿#ifndef INCLUDED__CX__GW__CONTROL__FORM__HPP
#define INCLUDED__CX__GW__CONTROL__FORM__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: form.hpp
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
namespace ctrl
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: form
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class form : public model
{
public:
	form();
	virtual ~form();

	// model 가상함수
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual void on_widget_mouse_clicked   (widget_mouse_event* e);
	virtual void on_widget_mouse_dbclicked (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


