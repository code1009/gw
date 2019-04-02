#ifndef INCLUDED__CX__GW__DIAGRAM__ITEM__RECTANGLE_SHAPE__HPP
#define INCLUDED__CX__GW__DIAGRAM__ITEM__RECTANGLE_SHAPE__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: rectangle_shape.hpp
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
// Class: rectangle_shape
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_shape : public diagram
{
private:
	rectangle_renderer      _renderer1;
	text_rectangle_renderer _renderer2;

private:
	std::string _text                      ;
	color_t     _text_color                ;
	cx::uint_t  _text_format_alignment     ;
	cx::uint_t  _text_format_line_alignment;
	std::string _text_font_familyname      ;
	cx::float_t _text_font_size            ;
	cx::uint_t  _text_font_style           ;
			    
	color_t     _fill_color;
	cx::uint_t  _fill_style;

	cx::float_t _line_width     ;
	color_t     _line_color     ;
	cx::uint_t  _line_dash_style;

public:
	rectangle_shape();
	virtual ~rectangle_shape();

	// widget 가상함수
public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model  (model* model);
	virtual std::string get_class  (void);
	virtual void        initialize (void);

	// diagram 가상함수
public:
	virtual void     draw_diagram (void);
	virtual diagram* clone        (void);

	// rectangle_shape 가상함수
public:
	virtual void draw_shape (void);
	virtual void draw_text  (void);

public:
	virtual std::string get_text                       (void);
	virtual color_t     get_text_color                 (void);
	virtual cx::uint_t  get_text_format_alignment      (void);
	virtual cx::uint_t  get_text_format_line_alignment (void);
	virtual std::string get_text_font_familyname       (void);
	virtual cx::float_t get_text_font_size             (void);
	virtual cx::uint_t  get_text_font_style            (void);
	virtual void        set_text                       (std::string v);
	virtual void        set_text_color                 (color_t     v);
	virtual void        set_text_format_alignment      (cx::uint_t  v);
	virtual void        set_text_format_line_alignment (cx::uint_t  v);
	virtual void        set_text_font_familyname       (std::string v);
	virtual void        set_text_font_size             (cx::float_t v);
	virtual void        set_text_font_style            (cx::uint_t  v);

	virtual color_t    get_fill_color (void);
	virtual cx::uint_t get_fill_style (void);
	virtual void       set_fill_color (color_t    v);
	virtual void       set_fill_style (cx::uint_t v);

	virtual cx::float_t get_line_width      (void);
	virtual color_t     get_line_color      (void);
	virtual cx::uint_t  get_line_dash_style (void);
	virtual void        set_line_width      (cx::float_t v);
	virtual void        set_line_color      (color_t     v);
	virtual void        set_line_dash_style (cx::uint_t  v);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: rectangle_shape_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_shape_event_handler : public diagram_event_handler
{
public:
	virtual void on_mouse_clicked (widget_mouse_event* e);
	virtual void on_mouse_hover   (widget_mouse_event* e);
	virtual void on_mouse_leave   (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: rectangle_shape_json_iostream
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_shape_json_iostream : public diagram_json_iostream
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


