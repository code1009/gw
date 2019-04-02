#ifndef INCLUDED__CX__GW__CONTROL__ITEM__BUTTON__HPP
#define INCLUDED__CX__GW__CONTROL__ITEM__BUTTON__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: button.hpp
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
// Class: button
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class button : public control
{
private:
	std::string _text;

private:
	rectangle_3d_renderer   _renderer1;
	text_rectangle_renderer _renderer2;

public:
	button();
	virtual ~button();

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
// Class: button_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class button_event_handler : public control_event_handler
{
public:
	virtual void on_mouse_clicked (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


