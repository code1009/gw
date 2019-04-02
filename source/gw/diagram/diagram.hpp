#ifndef INCLUDED__CX__GW__DIAGRAM__DIAGRAM__HPP
#define INCLUDED__CX__GW__DIAGRAM__DIAGRAM__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: diagram.hpp
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
namespace dgrm
{


/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram : public widget
{
	// status
private:
	cx::bool_t _visible  ;
	cx::bool_t _enabled  ;
	cx::bool_t _pressed  ;
	cx::bool_t _selected ;

private:
	rectangle_renderer _renderer0;
	ellipse_renderer   _renderer1;

public:
	diagram();
	virtual ~diagram();

	// widget 가상함수
public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model   (model* model);
	virtual std::string get_class   (void);
	virtual void        set_name    (std::string name);
	virtual void        initialize  (void);
	virtual cx::bool_t  is_point_in (point_t p);
	virtual void        set_bounds  (rectangle_t bounds);
	virtual void        move        (point_t offset);	
	virtual void        draw        (void);

	// diagram 가상함수
public:
	virtual design* get_design (void);

public:
	virtual void draw_diagram (void);
	virtual void draw_diagram_bounds (void);

public:
	virtual cx::bool_t get_visible (void);
	virtual void       set_visible (cx::bool_t v);

	virtual cx::bool_t get_enabled (void);
	virtual void       set_enabled (cx::bool_t v);

	virtual cx::bool_t get_pressed (void);
	virtual void       set_pressed (cx::bool_t v);

	virtual cx::bool_t get_selected (void);
	virtual void       set_selected (cx::bool_t v);

public:
	virtual void on_set_anchor_point(anchor* wa, point_t& p);

public:
	virtual diagram* clone (void);

public:
	virtual void set_status_changed   (void);
	virtual void set_property_changed (void);
	virtual void set_point_changed    (void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_event_handler : public widget_event_handler
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
//
// Class: diagram_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_json_iostream : public widget_iostream
{
public:
	diagram_json_iostream();
	virtual ~diagram_json_iostream();

public:
	virtual cx::bool_t read (document_reader* io, widget* w, model* m);
	virtual cx::bool_t write(document_writer* io, widget* w, model* m);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


