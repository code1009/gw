#ifndef INCLUDED__CX__GW__DIAGRAM__EDIT_ACTION__HPP
#define INCLUDED__CX__GW__DIAGRAM__EDIT_ACTION__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: edit_action.hpp
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
// Class: edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class edit_action
{
private:
	edit* _edit;

public:
	edit_action();
	virtual ~edit_action();

public:
	virtual edit* get_edit (void);

public:
	virtual void initialize (edit* m);
	virtual void draw       (graphic_t g);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

	virtual void on_mouse_drag_enter (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_over  (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_leave (mouse_drag_drop_event* e);
	virtual void on_mouse_drop       (mouse_drag_drop_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_select_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_select_edit_action : public edit_action
{
private:
	rectangle_t _bounds;
	cx::bool_t  _bounds_tracking_enabled;

public:
	diagram_select_edit_action();
	virtual ~diagram_select_edit_action();

	// edit_action 가상함수
public:
	virtual void initialize (edit* m);
	virtual void draw       (graphic_t g);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

private:
	void set_first_point (point_t& p);
	void set_last_point  (point_t& p);

private:
	void       set_bounds_tracking_enabled (cx::bool_t enabled);
	cx::bool_t get_bounds_tracking_enabled (void);

public:
	rectangle_t get_bounds (void);

private:
	void select_in_bounds (void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_single_select_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_single_select_edit_action : public edit_action
{
private:
	typedef enum _mode_t
	{
		MODE_NONE  ,
		MODE_TOGGLE,
		MODE_ADD   
	} modt_t;

	modt_t _mode;

public:
	diagram_single_select_edit_action();
	virtual ~diagram_single_select_edit_action();

	// edit_action 가상함수
public:
	virtual void initialize (edit* m);
	virtual void draw       (graphic_t g);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_move_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_move_edit_action : public edit_action
{
private:
	point_t _current_point;

	point_t _first_point;
	point_t _last_point;

public:
	diagram_move_edit_action();
	virtual ~diagram_move_edit_action();

	// edit_action 가상함수
public:
	virtual void initialize (edit* m);
	virtual void draw       (graphic_t g);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

private:
	void set_first_point (point_t& p);
	void set_last_point  (point_t& p);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: anchor_move_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class anchor_move_edit_action : public edit_action
{
private:
	point_t _current_point;

	point_t _first_point;
	point_t _last_point;

private:
	anchor* _anchor;

public:
	anchor_move_edit_action();
	virtual ~anchor_move_edit_action();

	// edit_action 가상함수
public:
	virtual void initialize (edit* m);
	virtual void draw       (graphic_t g);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

private:
	void set_first_point (point_t& p);
	void set_last_point  (point_t& p);

public:
	anchor* get_anchor (void);
	void    set_anchor (anchor* wa);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_add_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_add_edit_action : public edit_action
{
private:
	point_t _current_point;

private:
	widget_collection _new_diagram;

public:
	diagram_add_edit_action();
	virtual ~diagram_add_edit_action();

	// edit_action 가상함수
public:
	virtual void initialize (edit* m);
	virtual void draw (graphic_t g);

	virtual void on_mouse_drag_enter (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_over  (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_leave (mouse_drag_drop_event* e);
	virtual void on_mouse_drop       (mouse_drag_drop_event* e);

private:
	void set_first_point (point_t& p);
	void set_last_point  (point_t& p);

public:
	widget_collection* get_new_diagram(void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


