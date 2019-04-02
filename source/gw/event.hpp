#ifndef INCLUDED__CX__GW__EVENT__HPP
#define INCLUDED__CX__GW__EVENT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: event.hpp
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
typedef enum _event_code_t
{
	EC_NONE,

	EC_MOUSE_MOVE ,
//	EC_MOUSE_LEAVE,
//	EC_MOUSE_HOVER,
	EC_MOUSE_LBUTTON_DOWN,
	EC_MOUSE_LBUTTON_UP  , 

	EC_MOUSE_DRAG_ENTER,
	EC_MOUSE_DRAG_LEAVE,
	EC_MOUSE_DRAG_OVER ,
	EC_MOUSE_DROP      ,
	
	EC_END
} event_code_t;



/////////////////////////////////////////////////////////////////////////////
//
// Class: event
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class event
{
public:
	cx::uint_t _code;

public:
	event();
	explicit event(cx::uint_t code);
	event(event& v);
	virtual ~event();

public:
	event& operator= (const event& rhs);

public:
	virtual cx::uint_t get_code (void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: mouse_event
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class mouse_event : public event
{
public:
	point_t _point;

	cx::bool_t _shift_key_pressed;
	cx::bool_t _ctrl_key_pressed ;

public:
	mouse_event();
	mouse_event(mouse_event& v);
	virtual ~mouse_event();

public:
	mouse_event& operator= (const mouse_event& rhs);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: mouse_drag_drop_event
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class mouse_drag_drop_event : public mouse_event
{
public:
	HGLOBAL _hglobal;

public:
	mouse_drag_drop_event();
	mouse_drag_drop_event(mouse_drag_drop_event& v);
	virtual ~mouse_drag_drop_event();

public:
	mouse_drag_drop_event& operator= (const mouse_drag_drop_event& rhs);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


