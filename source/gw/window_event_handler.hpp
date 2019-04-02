#ifndef INCLUDED__CX__GW__WINDOW_EVENT_HANDLER__HPP
#define INCLUDED__CX__GW__WINDOW_EVENT_HANDLER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: window_event_handler.hpp
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
// Class: window_event_handler
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class window_event_handler
{
private:
	model* _model;

private:
	widget* _mouse_pressed_widget;
	widget* _mouse_released_widget;
	widget* _mouse_clicked_widget;
	widget* _mouse_dbclicked_widget;
	widget* _mouse_hover_widget;
	widget* _mouse_dragging_widget;

private:
	cx::bool_t _window_mouse_capture_enabled;
	cx::bool_t _window_mouse_captured;

private:
	cx::uint_t _widget_mouse_clicked_time;

public:
	window_event_handler();
	virtual ~window_event_handler();

public:
	virtual model* get_model (void);
	virtual void   set_model (model* model);

public:
	virtual void on_update_widget(void); // from model(diagram edit) class

public:
	virtual cx::bool_t get_window_mouse_capture_enabled (void);
	virtual void       set_window_mouse_capture_enabled (cx::bool_t enabled);

public:
	virtual void set_window_mouse_capture(HWND hwnd);
	virtual void release_window_mouse_capture(void);

public:
	virtual void on_windows_message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	virtual void on_event (event* e);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

public:
	virtual void notify_mouse_move         (mouse_event* e);
	virtual void notify_mouse_lbutton_down (mouse_event* e);
	virtual void notify_mouse_lbutton_up   (mouse_event* e);

	virtual void notify_widget_mouse_pressed  (widget* w, mouse_event* e);
	virtual void notify_widget_mouse_released (widget* w, mouse_event* e);
	virtual void notify_widget_mouse_clicked  (widget* w, mouse_event* e);
	virtual void notify_widget_mouse_dbclicked(widget* w, mouse_event* e);
	virtual void notify_widget_mouse_hover    (widget* w, mouse_event* e);
	virtual void notify_widget_mouse_leave    (widget* w, mouse_event* e);
	virtual void notify_widget_mouse_dragging (widget* w, mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


