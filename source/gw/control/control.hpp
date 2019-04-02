#ifndef INCLUDED__CX__GW__CONTROL__CONTROL__HPP
#define INCLUDED__CX__GW__CONTROL__CONTROL__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: control.hpp
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
// Class: control
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class control : public widget
{
private:
	cx::bool_t _visible  ;
	cx::bool_t _enabled  ;
	cx::bool_t _pressed  ;
	cx::bool_t _selected ;
	cx::bool_t _activated;
	cx::bool_t _focus    ;

private:
	rectangle_3d_renderer _renderer;

public:
	control();
	virtual ~control();

	// widget 가상함수
public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model   (model* model);
	virtual std::string get_class   (void);
	virtual void        initialize  (void);
	virtual cx::bool_t  is_point_in (point_t p);
	virtual void        set_bounds  (rectangle_t bounds);
	virtual void        draw        (void);

	// control 가상함수
public:
	virtual void draw_control (void);

public:
	virtual cx::bool_t get_visible (void);
	virtual void       set_visible (cx::bool_t v);

	virtual cx::bool_t get_enabled (void);
	virtual void       set_enabled (cx::bool_t v);

	virtual cx::bool_t get_pressed (void);
	virtual void       set_pressed (cx::bool_t v);

	virtual cx::bool_t get_selected (void);
	virtual void       set_selected (cx::bool_t v);

	virtual cx::bool_t get_activated (void);
	virtual void       set_activated (cx::bool_t v);

	virtual cx::bool_t get_focus (void);
	virtual void       set_focus (cx::bool_t v);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: control_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class control_event_handler : public widget_event_handler
{
	// widget_event_handler 가상함수
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
//===========================================================================
}
}





#endif


