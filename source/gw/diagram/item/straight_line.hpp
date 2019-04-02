#ifndef INCLUDED__CX__GW__DIAGRAM__ITEM__STRAIGHT_LINE__HPP
#define INCLUDED__CX__GW__DIAGRAM__ITEM__STRAIGHT_LINE__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: straight_line.hpp
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
// Class: straight_line
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class straight_line : public diagram
{
private:
	line_renderer _renderer1;

private:
	cx::float_t _line_width     ;
	color_t     _line_color     ;
	cx::uint_t  _line_dash_style;

public:
	straight_line();
	virtual ~straight_line();

	// widget 가상함수
public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model   (model* model);
	virtual std::string get_class   (void);
	virtual void        initialize  (void);
	virtual cx::bool_t  is_point_in (point_t p);

	// diagram 가상함수
public:
	virtual void     draw_diagram (void);
	virtual diagram* clone        (void);

	virtual void on_set_anchor_point(anchor* wa, point_t& p);

	// straight_line 가상함수
public:
	virtual void draw_line (void);

public:
	virtual cx::float_t get_line_width      (void);
	virtual color_t     get_line_color      (void);
	virtual cx::uint_t  get_line_dash_style (void);
	virtual void        set_line_width      (cx::float_t v);
	virtual void        set_line_color      (color_t     v);
	virtual void        set_line_dash_style (cx::uint_t  v);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: straight_line_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class straight_line_event_handler : public diagram_event_handler
{
public:
	virtual void on_mouse_clicked (widget_mouse_event* e);
	virtual void on_mouse_hover   (widget_mouse_event* e);
	virtual void on_mouse_leave   (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: straight_line_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class straight_line_json_iostream : public diagram_json_iostream
{
public:
	virtual cx::bool_t read (document_reader* io, widget* w, model* m);
	virtual cx::bool_t write(document_writer* io, widget* w, model* m);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


