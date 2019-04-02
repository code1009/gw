#ifndef INCLUDED__CX__GW__WIDGET_EVENT__HPP
#define INCLUDED__CX__GW__WIDGET_EVENT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: widget_event.hpp
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
//===========================================================================
typedef enum _widget_event_code_t
{
	EC_WIDGET_MOUSE_PRESSED  = EC_END, 
	EC_WIDGET_MOUSE_RELEASED , 
	EC_WIDGET_MOUSE_CLICKED  ,
	EC_WIDGET_MOUSE_DBCLICKED,
	EC_WIDGET_MOUSE_HOVER    ,
	EC_WIDGET_MOUSE_LEAVE    ,
	EC_WIDGET_MOUSE_DRAGGING ,
	
	EC_WIDGET_END
} widget_event_code_t;



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_mouse_event
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_mouse_event : public mouse_event
{
public:
	widget* _widget;

public:
	widget_mouse_event();
	widget_mouse_event(widget_mouse_event& v);
	virtual ~widget_mouse_event();

public:
	widget_mouse_event& operator= (const widget_mouse_event& rhs);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


