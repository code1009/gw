#ifndef INCLUDED__CX__GW__WIDGET_EVENT_HANDLER__HPP
#define INCLUDED__CX__GW__WIDGET_EVENT_HANDLER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: control_event_handler.hpp
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
// Class: widget_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_event_handler
{
public:
	widget_event_handler();
	virtual ~widget_event_handler();

public:
	virtual void on_event (event* e);

public:
	virtual void on_mouse_pressed  (widget_mouse_event* e);
	virtual void on_mouse_released (widget_mouse_event* e);
	virtual void on_mouse_clicked  (widget_mouse_event* e);
	virtual void on_mouse_dbclicked(widget_mouse_event* e);
	virtual void on_mouse_hover    (widget_mouse_event* e);
	virtual void on_mouse_leave    (widget_mouse_event* e);
	virtual void on_mouse_dragging (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: named_widget_event_handler_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class named_widget_event_handler_collection
{
private:
	named_widget_event_handler_pointer_container_t _container;

public:
	named_widget_event_handler_collection();
	virtual ~named_widget_event_handler_collection();

public:
	virtual named_widget_event_handler_pointer_container_t& get_container (void);

public:
	virtual void delete_container (void);

public:
	virtual widget_event_handler* find (widget* w);
	virtual cx::bool_t            add  (std::string name, widget_event_handler* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


