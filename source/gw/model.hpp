#ifndef INCLUDED__CX__GW__MODEL__HPP
#define INCLUDED__CX__GW__MODEL__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: model.hpp
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
// Class: model
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class model
{
private:
	window_t  _window;
	graphic_t _graphic;

private:
	resource             _resource;
	view                 _view;
	window_event_handler _window_event_handler;

private:
	named_widget_event_handler_collection _widget_event_handler;
	widget_collection                     _widget;

public:
	model();
	virtual ~model();

public:
	virtual window_t get_window (void);
	virtual void     set_window (window_t window);

	virtual graphic_t get_graphic (void);
	virtual void      set_graphic (graphic_t graphic);

public:
	virtual resource*             get_resource             (void);
	virtual view*                 get_view                 (void);	
	virtual window_event_handler* get_window_event_handler (void);

public:
	virtual named_widget_event_handler_collection* get_widget_event_handler (void);
	virtual widget_collection*                     get_widget               (void);
	
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual void set_redraw (widget* widget);
	virtual void set_redraw (void);

public:
	virtual void draw (void);

public:
	virtual void on_event (event* e);

	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

	virtual void on_mouse_drag_enter (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_over  (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_leave (mouse_drag_drop_event* e);
	virtual void on_mouse_drop       (mouse_drag_drop_event* e);

	virtual void on_widget_mouse_pressed  (widget_mouse_event* e);
	virtual void on_widget_mouse_released (widget_mouse_event* e);
	virtual void on_widget_mouse_clicked  (widget_mouse_event* e);
	virtual void on_widget_mouse_dbclicked(widget_mouse_event* e);
	virtual void on_widget_mouse_hover    (widget_mouse_event* e);
	virtual void on_widget_mouse_leave    (widget_mouse_event* e);
	virtual void on_widget_mouse_dragging (widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


