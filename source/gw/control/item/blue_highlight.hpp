#ifndef INCLUDED__CX__GW__CONTROL__ITEM__BLUE_HIGHLIGGHT__HPP
#define INCLUDED__CX__GW__CONTROL__ITEM__BLUE_HIGHLIGGHT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: blue_highlight.hpp
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
// Class: blue_highlight
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class blue_highlight : public control
{
private:
	std::string _text;

private:
	round_rectangle_renderer _renderer1;
//	rectangle_renderer      _renderer1;
	text_rectangle_renderer _renderer2;

public:
	blue_highlight();
	virtual ~blue_highlight();

public:
	static std::string get_registered_name (void);

public:
	virtual std::string get_class (void);

public:
	virtual void draw_control (void);

public:
	virtual std::string get_text(void);
	virtual void        set_text(std::string text);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: blue_highlight_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class blue_highlight_event_handler : public control_event_handler
{
public:
	virtual void on_mouse_clicked (widget_mouse_event* e);
	virtual void on_mouse_hover   (widget_mouse_event* e);
	virtual void on_mouse_leave   (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


