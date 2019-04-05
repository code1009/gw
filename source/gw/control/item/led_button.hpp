#ifndef INCLUDED__CX__GW__CONTROL__ITEM__LED_BUTTON__HPP
#define INCLUDED__CX__GW__CONTROL__ITEM__LED_BUTTON__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: led_button.hpp
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
// Class: led_button
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class led_button : public control
{
private:
	std::string _text;

private:
	rectangle_3d_renderer   _renderer1;
	text_rectangle_renderer _renderer2;

public:
	led_button();
	virtual ~led_button();

public:
	static std::string get_registered_name (void);

public:
	virtual void        set_model  (model* model);
	virtual std::string get_class  (void);
	virtual void        initialize (void);
	virtual void        set_bounds (rectangle_t bounds);

public:
	virtual void draw_control (void);

public:
	virtual std::string get_text(void);
	virtual void        set_text(std::string v);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: led_button_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class led_button_event_handler : public control_event_handler
{
public:
	virtual void on_mouse_clicked (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


