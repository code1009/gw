#ifndef INCLUDED__CX__GW__DIAGRAM__ANCHOR__HPP
#define INCLUDED__CX__GW__DIAGRAM__ANCHOR__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: anchor.hpp
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
// Class: anchor
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class anchor : public widget
{
private:
	cx::bool_t _visible  ;
	cx::bool_t _enabled  ;
	cx::bool_t _pressed  ;
	cx::bool_t _selected ;

private:
	cx::uint_t _id;
	
public:
	typedef enum _type_t
	{
		TYPE_NONE,

		TYPE_RESIZE    ,
		TYPE_MOVE      ,
		TYPE_CONTROL   ,
		TYPE_INVISIBLE
	} type_t;

private:
	type_t _type;

private:
	ellipse_renderer   _renderer1;
	rectangle_renderer _renderer2;
	ellipse_renderer   _renderer3;

private:
	anchor();

public:
	explicit anchor(cx::uint_t id, type_t type = TYPE_RESIZE);
	virtual ~anchor();

	// widget 가상함수
public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model   (model* model);
	virtual std::string get_class   (void);
	virtual void        initialize  (void);
	virtual cx::bool_t  is_point_in (point_t p);
	virtual rectangle_t get_bounds  (void);
	virtual void        set_bounds  (rectangle_t bounds);
	virtual void        draw        (void);

	// anchor 가상함수
public:
	virtual design* get_design (void);

public:
	virtual cx::uint_t get_id(void);
	virtual type_t     get_type(void);

public:
	virtual void draw_anchor (void);

	virtual void draw_anchor_type_resize   (void);
	virtual void draw_anchor_type_move     (void);
	virtual void draw_anchor_type_control  (void);
	virtual void draw_anchor_type_invisible(void);

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
	virtual diagram* get_diagram(void);

public:
	virtual void on_set_point(point_t& p); // from anchor_move_edit_action class

public:
	virtual point_t get_point(void);
	virtual void    set_point(point_t& p);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: anchor_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class anchor_event_handler : public widget_event_handler
{
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


